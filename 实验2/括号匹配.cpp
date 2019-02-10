// ����ƥ��.cpp: �������̨Ӧ�ó������ڵ㡣
//
#include<cstdlib>
#include<iostream>
#define STACK_INIT_SIZE 100 
#define	STACK_INCREMENT_SIZE 10

using namespace std;

class Stack {
	char* top, *base;
	int stack_size;
	
public:
	int length;

	Stack() {
		char*  temp = (char*)malloc(STACK_INIT_SIZE * sizeof(char));
		if (!temp) return;

		base = temp;
		top = base;
		length = 0;
		stack_size = STACK_INIT_SIZE;
	}

	~Stack() {
	}

	void ClearStack() {    //ջ���;
		top = base;
		length = 0;
	}
	void Push(char p) {
		if (top - base >= stack_size) {  //ջ��
			base = (char*)realloc(base, (stack_size + STACK_INCREMENT_SIZE) * sizeof(char));
			top = base + stack_size;   //���޸�topָ��
			stack_size += STACK_INCREMENT_SIZE;
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
	Stack stack;
	int num;  //���ʽ�ĸ���
	cin >> num;
	char temp;
	bool is_right = 1;   
	while (num) {
		cin >> temp;
		while (temp != '@') {
			if (temp == '(' || temp == '[' || temp == '{') stack.Push(temp);
			if (temp == ')') {
				char bracket = stack.Pop();
				if (bracket == '(') {
					cin >> temp;
					continue;
				}
				else {
					cout << "NO" << endl;
					is_right= 0;
					while (temp != '@') cin >> temp;   //������һ�еı��ʽ�������ж���һ�����ʽ
					break;
				}
			}
			if (temp == ']') {
				char bracket = stack.Pop();
				if (bracket == '[') {
					cin >> temp;
					continue;
				}
				else {
					cout << "NO" << endl;
					is_right = 0;
					while (temp != '@') cin >> temp;   //������һ�еı��ʽ�������ж���һ�����ʽ
					break;
				}
			}
			if (temp == '}') {
				char bracket = stack.Pop();
				if (bracket == '{') {
					cin >> temp;
					continue;
				}
				else {
					cout << "NO" << endl;
					is_right = 0;
					while (temp != '@') cin >> temp; //������һ�еı��ʽ�������ж���һ�����ʽ
					break;
				}
			}
			cin >> temp;
		}
		if (is_right&&stack.length == 0)cout << "YES" << endl;
		stack.ClearStack();
		is_right = 1;
		num--;
	}
    return 0;
}


