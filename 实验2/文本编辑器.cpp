// �ı��༭��.cpp: �������̨Ӧ�ó������ڵ㡣
//
#include<cstdlib>
#include<iostream>
#define STACK_INIT_SIZE 100 
#define	STACK_INCREMENT_SIZE 10

using namespace std;


class Stack {
	
	int stack_size;

public:
	char* top, * base;
	int length;
	int k;//��꣬���ķ�Χ��0����һ��Ԫ��ǰ�棩��length�����һ��Ԫ�أ�

	Stack() {
		char*  temp = (char*)malloc(STACK_INIT_SIZE * sizeof(char));
		if (!temp) return;

		base = temp;
		top = base;
		k = 0;	//�������Ϊ0
		length = 0;
		stack_size = STACK_INIT_SIZE;
	}

	~Stack() {
		/*
		while (top != base) {
			char* temp = --top;
			free(temp);
		}
		free(base);
		*/
	}

	void PrintStack() {   //��ӡջ�е�����Ԫ��
		for (char* p = base; p != top; p++) {       //ջ��Ϊ�ַ���ͷ��
			cout << *p;
		}
		cout << endl;
	}

	void Push(char p) {
		if (top - base >= stack_size) {  //ջ��
			base = (char* )realloc(base, (stack_size + STACK_INCREMENT_SIZE) * sizeof(char));
			top = base + stack_size;   //���޸�topָ��
			stack_size+= STACK_INCREMENT_SIZE;
		}
		length++;
		*top = p;
		top++;
	}
	char Pop() {
		if (base == top)return NULL;
		length--;
		return (*(--top));    //topָ����һλ���� -- ��ǰ
	}

};

int main()
{
	//��ȡ�����ָ��
	int num;
	cin >> num;  //��ȡָ����Ŀ
	char temp;
	Stack stack;
	//freopen("in.txt", "r", stdin);
	freopen("myout.txt", "w", stdout);

	while (num) {
		cin >> temp;
		//cout << "temp=" << temp << endl;
		switch (temp)
		{
		case 'M':   //Move k
			cin >> temp >> temp >> temp;	//������Ե�ָ����ʣ����ĸ M ove
			int k;
			cin >> k;
			stack.k = k;
			break;

		case 'G':   //Get
			cin >> temp >> temp;
			//stack.PrintStack();
		for (char* p = stack.base; p != stack.top; p++) {     //ջ��Ϊ�ַ���ͷ��
			cout << *p;
		}
		cout << endl;
			break;

		case 'I':   //Insert
		{

			cin >> temp >> temp >> temp >> temp >> temp;
			int num;      //������ַ����ĳ���
			cin >> num;

			int need_move = 0;   //��Ҫ�ƶ�Ԫ����Ϊ1������Ϊ0
			char* char_array = NULL;
			int len = stack.length - stack.k;

			if (len) {   //stack.length == kʱ����Ҫ�ƶ�Ԫ��
				char_array = (char*)malloc(sizeof(char)* len);
				//���֮���Ԫ�ض���ջ����������������
				for (int i = 0; i <len; i++) {
					char_array[i] = stack.Pop();    //����ջβ��Ԫ�أ�װ�������е�ǰ��
				}
				need_move = 1;
			}

			getchar();   //�Ե��س�
			for (int i = 0; i <num; i++) {
				char c;
				c = getchar();
				//if(32<=c&&c<=126)
				stack.Push(c);
			}
			//stack.length += num;  Pushʱ�Ѿ�����
			if (need_move) {
				for (int i = len - 1; i >= 0; i--) {
					stack.Push(char_array[i]);
				}
				delete[]char_array;
			}
			break;
		}

		case 'D':
		{
			cin >> temp >> temp >> temp >> temp >> temp;
			int num;      //ɾ�����ַ����ĳ���
			cin >> num;

			char* char_array = NULL;

			//����cout << stack.k << " " << stack.length - stack.k;
			int len = stack.length - stack.k;
			char_array = (char*)malloc(sizeof(char)* len);
			//���֮���Ԫ�ض���ջ����������������
			
			for (int i = 0; i < len; i++) {
				char_array[i] = stack.Pop();    //����ջβ��Ԫ�أ�װ�������е�ǰ��
				//���� cout << char_array[i] << " "<<i<<endl;
			}

			for (int i = len -num - 1; i >= 0; i--) {
				stack.Push(char_array[i]);
			}

			delete[]char_array;
			break;
		}

		case 'R':
		{
			cin >> temp >> temp >> temp >> temp >> temp;
			int num;      //��ת���ַ����ĳ���
			cin >> num;

			int need_move = 0;   //��Ҫ�ƶ�Ԫ����Ϊ1������Ϊ0

			char* char_array = NULL;

			int len = (stack.length - stack.k);
			char_array = (char*)malloc(sizeof(char)*len);
			//���֮���Ԫ�ض���ջ����������������

			for (int i = 0; i <len; i++) {
				char_array[i] = stack.Pop();    //����ջβ��Ԫ�أ�װ�������е�ǰ��
			}

			for (int i =len -num ; i < len; i++) {
				stack.Push(char_array[i]);
			}
			for (int i = len-num - 1; i >= 0; i--) {
				stack.Push(char_array[i]);
			}
			delete[]char_array;
			break;
		}

		case'P': {
			cin >> temp >> temp >> temp;
			stack.k -=1;
			break;
		}
		case'N': {
			cin >> temp >> temp >> temp;
			stack.k += 1;
			break;
		}
		default: {
			cout << "�����ָ�" << endl;
			break;
		}
		}
		num--;
	}
    return 0;
}


