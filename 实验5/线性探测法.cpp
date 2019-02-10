#include<iostream>
using namespace std;

int H(int x, int p) {
	return (x % p);
}

int SuccessSearch(int x, int p, int m,int *HashTable, int(*H)(int, int)) {
	int success_count = 0;
	int temp_pos = H(x, p);
	int temp_new_pos = (temp_pos + 1) % m;
	if (HashTable[temp_pos] < 0)return 1;  // ֱ��û�ҵ� 
	if (HashTable[temp_pos] != x) {
		success_count += 1;
		while (HashTable[temp_new_pos] != x) {
			temp_new_pos = (temp_new_pos + 1) % m;
			++success_count;
			if (HashTable[temp_new_pos]<0) {
				break;
			}
		}
	}
	success_count += 1;
	return success_count;
}

int main()
{	
	//����ؼ��ִ���
	int num;
	cin >> num;
	//����ؼ���
	int *key = new int[num];
	for (int i = 0; i < num; i++) cin >> key[i];
	//����p
	int m, p;
	cin >> p;
	m = p;
	//����չ�ϣ����ʼ��
	int* HashTable = new int[m];
	for (int i = 0; i < m; i++)HashTable[i] = -1;

	for (int i = 0; i < num; i++) {
		int pos = H(key[i],p);
		if (HashTable[pos] < 0)HashTable[pos] = key[i];
		else {   //��ͻ
			int new_pos = (pos+1)%m;
			while (HashTable[new_pos] >= 0) {
				new_pos = (new_pos+1)% m;
			}
			HashTable[new_pos] = key[i];
		}
	}
	//��ӡ��ϣ��
	cout << "��ַ �ؼ���" << endl;
	for (int i = 0; i <m; i++) {
		cout << " " << i;
		if(i<10)cout<< "   ";
		else cout << "  ";

		if(HashTable[i]<0)cout<<'-';
		else cout << HashTable[i];
		cout << endl;
	}
	cout << endl;
	cout << "�ؼ���  �ɹ����Ҵ���" << endl;
	int success_count,fail_count;
	float success_sum=0.0, fail_sum=0.0;
	//ͳ�Ƴɹ����Ҵ���
	for (int i = 0; i < num; i++) {
		success_count = SuccessSearch(key[i], p, m, HashTable, H);

		cout << " ";
		if (key[i] < 100)cout << key[i] << "     ";
		else cout << key[i] << "    ";
		cout<<success_count << endl;
		success_sum += success_count;
	}
	cout << "�ɹ�ƽ��:" << (success_sum / num) << endl;
	cout << endl;
	cout << "��ַ" << " ʧ�ܲ��Ҵ���" << endl;
	for (int i = 0; i < m; i++) {
		fail_count = 1;
		//ͳ��ʧ�ܴ�����ʧ��ƽ��
		int j = i;
		while (HashTable[j] >= 0) {
			j+=1;
			j=j%m;
			++fail_count;
		}
		cout <<" "<<i;
		if (i<10)cout << "   ";
		else cout << "  ";
		cout<<fail_count<<endl;
		fail_sum += fail_count;
	}
	cout << endl;
	
	cout << "ʧ��ƽ��:" << (fail_sum / m) << endl;

	int key_word;
	cout << "����Ҫ���ҵĹؼ���:";
	cin >> key_word;
	cout << "���Ҵ���Ϊ:" << SuccessSearch(key_word,p,m,HashTable,H)<<endl;


    return 0;
}


