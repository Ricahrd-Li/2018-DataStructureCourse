#include<iostream>
using namespace std;

typedef struct ChainNode {
	int elem;
	struct ChainNode* next;
}ChainNode,*Chain;

int H(int x,int p) {
	return (x % p);
}

void BuildChainHash(int x,int p, Chain*ChainHash ,int(*H)(int, int)) {
	int num = H(x, p);
	Chain temp = new ChainNode;
	temp->elem = x;
	temp->next = NULL;
	if (!ChainHash[num])ChainHash[num] = temp;
	else {
		Chain p,q;
		q = p = ChainHash[num];
		while ((p->elem) < x) {  //��ͬ�����ͬһ���������а��ؼ�������
			q = p;
			p = p->next;
			if (p == NULL)break;
		}
		if (p == ChainHash[num]) {
			temp->next = p;
			ChainHash[num]= temp;   //p=temp ���ԣ�����
		}
		else {
			temp->next = q->next;
			q->next = temp;
		}
	}
}

int SuccessSearchChainHash(int x, Chain* ChainHash, int p, int(*H)(int, int)) {
	int num = H(x, p);
	int count=1;  //��¼�����˶��ٴ�
	for (Chain q = ChainHash[num]; q!=NULL&&q->elem != x; q = q->next)count++;
	return count;
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
	int m,p;
	cin >> p;
	m = p ;
	Chain* ChainHash = new Chain[m];  //����Ϊm����ΧΪ0--(m-1)��ͷָ������  
	for (int i = 0; i < m; i++) ChainHash[i] = NULL;
	//������������ϣ��
	for (int i = 0; i < num; i++) BuildChainHash(key[i],p,ChainHash,H);
	//��ӡ��ϣ��
	cout << "��ַ �ؼ���"<<endl;
	for (int i = 0; i < m; i++) {
		cout << " "<<i << "   ";
		Chain q = ChainHash[i];
		if (!q) {
			cout << "-";
		}
		else {
			for (; q != NULL; q = q->next) cout << q->elem << " ";
		}
		cout << endl;
	}
	cout << endl;
	//��ӡ�ɹ����Ҵ���
	float success_sum = 0;
	float fail_sum = 0;
	int success_count = 0;
	int fail_count = 1;
	for (int i = 0; i < m; i++) {
		cout << i << ":";
		Chain q = ChainHash[i];
		if (!q) {
			success_count= 0;
			cout <<"�ɹ���"<< success_count << " ";
		}
		else {
			cout << "�ɹ���";
			for (; q != NULL; q = q->next) { 
				success_count = SuccessSearchChainHash(q->elem, ChainHash, p, H);
				success_sum += success_count;
				cout << success_count << " ";
			}
		}
		fail_count = success_count + 1;
		fail_sum += fail_count;
		cout << "ʧ�ܣ�" << fail_count;
		cout << endl;
	}
	cout << endl;
	cout << "�ɹ�ƽ��:"<<(success_sum/num)<<endl;
	cout << "ʧ��ƽ��:" << (fail_sum /m) << endl;
	
	int key_word;
    cout<<"����Ҫ���ҵĹؼ��֣�";
	cin>>key_word;
	cout<<"�Ƚϴ���Ϊ��"<<SuccessSearchChainHash(key_word, ChainHash,p, H); 
    return 0;
}

