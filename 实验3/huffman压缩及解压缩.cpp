// huffmanѹ������ѹ��.cpp: �������̨Ӧ�ó������ڵ㡣
//
#include<cstring>
#include<cstdlib>
#include<cstdio>
#include<string>
#include<iostream>

using namespace std;

typedef struct Alpha {
	unsigned char alpha;
	unsigned long long int freq;
}Alpha;

//Part 2  ����Huffman��
typedef struct {
	unsigned long long int weight;
	int parent, lchild, rchild;
}HTNode, *HuffmanTree;

typedef char** HuffmanCode;

void Select(HuffmanTree &HT, int num, int& s1, int& s2) {   //ѡȡHT[1--num]����С������ 
															//num:�Ǵ�ѡ��Ľ�����Ŀ 
	int i;
	unsigned long long int min_weight = -1;
	unsigned long long int min_record = -1;
	for (i = 1; i <= num; i++) {   //HuffmanTree[0]δ��
		if (HT[i].parent == 0 && min_weight<0)min_weight = min_record = HT[i].weight;//��¼�����ĵ�һ��Ȩֵ
		if (HT[i].parent == 0 && (HT[i].weight <= min_weight)) {
			min_weight = HT[i].weight;
			s1 = i;
		}
	}
	HT[s1].parent = -1;   //��Ϊ������HT[i].parent == 0��ͻ

	min_weight = min_record;

	for (i = 1; i <= num; i++) {   //HuffmanTree[0]δ��
		if (HT[i].parent == 0 && HT[i].weight <= min_weight) {
			min_weight = HT[i].weight;
			s2 = i;
		}
	}
};

void HuffmanCoding(HuffmanTree &HT, HuffmanCode &HC, Alpha* & Alphabet, int num_alpha) {
	if (num_alpha <= 1) return;
	int m = 2 * num_alpha - 1;    //Huffman����������
	HT = (HuffmanTree)malloc(sizeof(HTNode)*(m + 1));  //HT[0]λû��ʹ��

	int i;
	for (i = 0; i <num_alpha; i++) {   //���Ըĳ��±�һ�µģ�
		HT[i + 1] = { Alphabet[i].freq,0,0,0 };  //Alphabet�ĳ��ȼ�Ϊnum_alpha
	}

	//HT��0--num_alphaλ �� Alphabet��Ӧλ 
	for (; i <m; i++)HT[i + 1] = { 0,0,0,0 };  //��num_alpha+1--mλ��ʼ��
	for (i = num_alpha + 1; i <= m; i++) {
		int s1, s2;
		Select(HT, i - 1, s1, s2);
		HT[s1].parent = HT[s2].parent = i;
		HT[i].lchild = s1; HT[i].rchild = s2;
		HT[i].weight = HT[s1].weight + HT[s2].weight;
	}
	//����Huffman����
	HC = (HuffmanCode)malloc((num_alpha + 1) * sizeof(char*));//HC[0]û�ã� 
	char * code = (char*)malloc(num_alpha * sizeof(char));  //����볤����num_alpha-1
	code[num_alpha - 1] = '\0';
	for (i = 1; i <= num_alpha; i++) {
		int start = num_alpha - 1;
		int c, f;
		//��Ҷ�������
		for (c = i, f = HT[i].parent; f != 0; c = f, f = HT[f].parent) {
			if (HT[f].lchild == c)code[--start] = '0';
			else code[--start] = '1';
		}
		HC[i] = (char*)malloc(num_alpha - start * sizeof(char));
		strcpy(HC[i], &code[start]);
		/*
		// ��ӡhuffman���룬������
		for(int j=0;j<strlen(HC[i]);j++)cout<<HC[i][j];
		cout<<endl;
		*/
	}
}

typedef struct {
	char format[5];
	unsigned char num_alpha;
}Head;

inline void SetBit(unsigned char& value, int index) {
	value |= (1 << index);
}
inline void ClearBit(unsigned char& value, int index) {
	value &= ((1 << index) ^ 0xFF);
}
inline int GetBit(unsigned char value, int index) {
	return (value >> index) & 1;
}
void Compress(int num_alpha, HuffmanCode &HC, Alpha alphabet[], string src_file_name, string aim_file_name, unsigned long long int freq[], string format) {
	cout << "����ѹ��......" << endl;
	//ѹ���ļ���ͷ������ 
	Head head;
	head.num_alpha = num_alpha;
	for (int i = 0; i<format.length(); i++) head.format[i] = format[i];
	head.format[4] = '\0';

	//д�����ȡ 
	aim_file_name += ".huff";
	FILE* fpin = fopen(src_file_name.data(), "rb");
	FILE* fpout = fopen(aim_file_name.data(), "wb");
	fwrite(&head, sizeof(Head), 1, fpout);
	fwrite(freq, sizeof(unsigned long long int) * 256, 1, fpout);

	int j;
	unsigned char value = 0;
	int index = 7;
	unsigned char temp_alpha;
	fread(&temp_alpha, sizeof(unsigned char), 1, fpin);
	while (!feof(fpin)) {
		//�ҵ��ַ���huff���룡 
		int t;
		for (int i = 0; i<num_alpha; i++) {
			if (alphabet[i].alpha == temp_alpha) {
				t = i;
				break;
			}
		}
		
		//alphabet[i].alpha ��Ӧ�ı����� HC[t+1],����ȱ��֮��
		for (j = 0; j< strlen(HC[t + 1]); j++) {
			if (HC[t + 1][j] == '0') ClearBit(value, index);
			else SetBit(value, index);


			index--;

			if (index < 0) {
				index = 7;
				fwrite(&value, sizeof(unsigned char), 1, fpout);
				value = 0;
			}
		}
		fread(&temp_alpha, sizeof(unsigned char), 1, fpin);
	}
	fwrite(&value, sizeof(unsigned char), 1, fpout);  //ʣ��δ��8bitҲд��ȥ 

	cout << "ѹ���ɹ���" << endl;

}

void DeCompress(string file_name) {
	cout << "���ڽ�ѹ��......" << endl;
	string src_file_name = file_name + ".huff";

	FILE* fpin = fopen(src_file_name.data(), "rb");
	//�ֱ��ȡͷ����Ƶ����Ϣ 
	Head head;
	unsigned long long int freq[256];
	fread(&head, sizeof(Head), 1, fpin);
	fread(freq, sizeof(unsigned long long int) * 256, 1, fpin);

	//���� origin�ļ� 
	string aim_file_name = file_name + "_origin" + head.format;
	FILE* fpout = fopen(aim_file_name.data(), "wb");

	//ͳ�ƹ��Ƴ����˶����ֲ�ͬ���ַ���num_alpha
	int num_alpha = 0;
	for (int i = 0; i < 256; i++) {
		if (freq[i])
			num_alpha++;
	}

	//����ṹ��Alpha���飬���ڽ�����������Huffman��
	Alpha* alphabet = (Alpha*)malloc(sizeof(Alpha)*num_alpha);
	int j;
	for (int i = j = 0; i < 256; i++) {
		if (freq[i]) {
			alphabet[j].alpha = i;
			alphabet[j].freq = freq[i];
			j++;
		}
	}

	HuffmanTree HT;
	HuffmanCode HC;
	HuffmanCoding(HT, HC, alphabet, num_alpha);
	/*
	//##### ��ӡhuffman���룬������
	for (int i = 0; i<num_alpha; i++) {
		cout << alphabet[i].alpha;
		for (int j = 0; j<strlen(HC[i + 1]); j++)cout << " " << HC[i + 1][j];
		cout << endl;
	}
	*/

	int root;
	for (int i = 1; i <= 2 * num_alpha - 1; i++) {
		if (HT[i].parent == 0)root = i;  //�ҵ���
	}
	int p = root;

	int index = 7;
	unsigned char temp_alpha;
	fread(&temp_alpha, sizeof(unsigned char), 1, fpin);
	int count=0;
	for (int i = 0; i < num_alpha; i++) {
		count += alphabet[i].freq;
	}
	while (!feof(fpin)) {
		while (index >= 0) {
			if (HT[p].rchild == 0 && HT[p].lchild == 0&&count>0) {
				fwrite(&alphabet[p - 1].alpha, sizeof(unsigned char), 1, fpout);
				count--;
				p = root;
			}
			if (GetBit(temp_alpha, index)) {
				if (HT[p].rchild)   //��rchild=1ʱ������ 
					p = HT[p].rchild;
			}
			else {
				if (HT[p].lchild)
					p = HT[p].lchild;
			}
			index--;
		}
		index = 7;
		fread(&temp_alpha, sizeof(unsigned char), 1, fpin);
	}
	cout << "��ѹ���ɹ���" << endl;
}
void start(){
	
}
int main()
{
	//�û�����
	string src_file_name;
	cout << "1.ѹ��  2.��ѹ��" << endl;
	int choice;
	cin >> choice;
	cout << "�������ļ�����";
	string file_name;
	cin >> file_name;
	if (choice == 1) {    //ѹ��
		cout << "��ѹ���ļ���ʽΪ��1.txt  2.jpg  3.png  4.mp4  5.gif  6.xls  7.bmp  8.docx  9.exe---->";
		int format_num;
		cin >> format_num;
		string format;
		switch (format_num)
		{
		case 1: src_file_name = file_name + ".txt";
			format = ".txt";
			break;
		case 2: src_file_name = file_name + ".jpg";
			format = ".jpg";
			break;
		case 3: src_file_name = file_name + ".png";
			format = ".png";
			break;
		case 4: src_file_name = file_name + ".mp4";
			format = ".mp4";
			break;
		case 5:src_file_name = file_name + ".gif";
			format = ".gif";
			break;
		case 6: src_file_name = file_name + ".xls";
			format = ".xls";
			break;
		case 7: src_file_name = file_name + ".bmp";
			format = ".bmp";
			break;
		case 8: src_file_name = file_name + ".docx";
			format = ".docx";
			break;
		case 9: src_file_name = file_name + ".exe";
			format = ".exe";
			break;
		default:
			break;
		}

		FILE* fp1 = fopen(src_file_name.data(), "rb");
		unsigned long long int freq[256] = { 0 };

		//���ļ��ж�ȡ�ַ�(1byte)��ͳ��Ƶ��
		unsigned char temp;
		temp = fgetc(fp1);
		while (!feof(fp1)) {
			freq[temp]++;
			temp = fgetc(fp1);
		}
		fclose(fp1);

		//ͳ�ƹ��Ƴ����˶����ֲ�ͬ���ַ���num_alpha
		int num_alpha = 0;
		for (int i = 0; i < 256; i++) {
			if (freq[i])
				num_alpha++;
		}
		//����ṹ��Alpha���飬���ڽ�����������Huffman��
		//alphabet �ĳ�����num_alpha 
		Alpha* alphabet = (Alpha*)malloc(sizeof(Alpha)*num_alpha);
		int j;
		for (int i = j = 0; i < 256; i++) {
			if (freq[i]) {
				alphabet[j].alpha = i;
				alphabet[j].freq = freq[i];
				j++;
			}
		}
		//Part 2  ����Huffman��
		HuffmanTree HT;
		HuffmanCode HC;
		HuffmanCoding(HT, HC, alphabet, num_alpha);

		Compress(num_alpha, HC, alphabet, src_file_name, file_name, freq, format);
	}
	else {   //��ѹ��
		DeCompress(file_name);
	}

	return 0;
}



