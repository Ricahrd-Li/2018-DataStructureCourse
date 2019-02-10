#include<cstdlib>
#include <iostream>
using namespace std;

typedef struct {
	float money;
	int arrive_time; //�����ʱ��
	int wait_time; //�Ⱥ�ʱ��
	bool not_dealed;  //=0��ʾ�Ѿ�����ҵ��=1��ʾδ��
}client,*ptr_client;

class Queue {
	typedef struct queue_node {
		ptr_client person;  
		struct queue_node* next;
	}qnode, *ptr_qnode;

	ptr_qnode rear;
	ptr_qnode front;
public:
	Queue() {    //���г�ʼ��
		ptr_qnode temp = (ptr_qnode)malloc(sizeof(qnode));  //ͷ���
		if (!temp) return;
		temp->person = NULL;
		temp->next = NULL;

		front = rear = temp;
	}

	~Queue() {

	}
	bool EmptyQueue() {
		if (rear == front) return 1;
		else return 0;
	}

	int EnQueue(ptr_client p) {  //���
		ptr_qnode temp = (ptr_qnode)malloc(sizeof(qnode));
		temp->person = p;
		temp->next = NULL;

		rear->next = temp;
		rear = rear->next;
		return 0;
	}
	ptr_client GetFront() {   //��ȡ��ͷԪ�ص���Ϣ
		ptr_client temp = front->next->person;
		return temp;
	}

	ptr_client DeQueue() {   //����,���ص���ptr_client 
		ptr_qnode temp = front->next;//��ͷ
		//��Ϊ�ն��з���NULL��
		if (!temp) return NULL;
		//��������ֻ��һ��Ԫ�أ�Ҫ�޸�rear
		if (rear == temp)rear = front;

		front->next = temp->next;

		ptr_client p = temp->person;

		free(temp);
		return p;
	}

	int LengthQueue() {
		int count=0;
		for (ptr_qnode p = front->next; p != NULL; p = p->next) count++;
		return count;
	}

};

void CheckQue2(Queue& que2, float& total_money, int& time, int deal_time) {
	//int money_record=total_money; //��¼���иղŵ�һ�����������һ���ͻ�(�ڶ���ҵ��)���Ӵ�֮ǰ������

	if (que2.EmptyQueue()) return; //��2�գ�ֱ�ӽ���

	int len = que2.LengthQueue();
	int count = 0;
	ptr_client p = que2.DeQueue();

	while (count <= len && p != NULL) {
		if (total_money + p->money >= 0&&p->not_dealed) {   //�������Ǯ��
			p->wait_time = time - p->arrive_time;
			
			total_money += p->money;
			p->not_dealed = 0;
			
			time += deal_time;
			//�û��뿪
		}
		else que2.EnQueue(p);   //����Ǯ�������ÿͻ�δ���㣬�ٴηŵ�que2��β

		count++;//��ֹ��ѭ��

		p = que2.DeQueue();
	}
}

void CheckQue1(Queue& que1,Queue& que2,float& total_money,int& time,int deal_time){  //����ҵ��1�ĺ���
	ptr_client p = que1.DeQueue();
	if (p->money < 0) {   //��һ��ҵ��
		if (total_money + p->money >= 0&&p->not_dealed) {   //�������Ǯ��
			p->wait_time = time - p->arrive_time;
			
			total_money += p->money; //��һ��ҵ��p->moneyΪ����
			p->not_dealed = 0;
			
			time += deal_time;
			//���û��뿪
		}
		else {
			que2.EnQueue(p);   //����Ǯ�������ÿͻ�δ���㣬�ŵ�que2��β
		}
		
	}
	else {  //�ڶ���ҵ��
		if (p->not_dealed) {
			p->wait_time = time - p->arrive_time;
			
			total_money += p->money; //��һ��ҵ��p->moneyΪ����
			p->not_dealed = 0;
			
			time += deal_time;
			
			CheckQue2(que2, total_money, time, deal_time);  //����2
		}
	}
}

int main()
{
	int num, close_time, deal_time;
	float total_money;
	cin >> num >> total_money >> close_time >> deal_time;
	//�����е������������п�ʼӪҵʱӵ�еĿ�ȫ�ֱ�����������Ԥ�Ƶ�Ӫҵʱ�����ͻ�����ʱ��

	//¼��ͻ���Ϣ
	ptr_client client_array = (ptr_client)malloc(num * sizeof(client));
	for (int i = 0; i < num; i++) {   
		cin >> client_array[i].money >> client_array[i].arrive_time;
		client_array[i].not_dealed=1;
	}

	int time=0;
	Queue que1,que2;  //��1����2

	while(time <= close_time){
		//���time�Ӷ��Ǵ����⣬Ҫ����
		for (int i = 0; i < num; i++) { //ÿһʱ�̱����ͻ����飬�Ӵ�����ʱ��Ŀͻ�
			if(time >=client_array[i].arrive_time && client_array[i].not_dealed){  
			//�˴�Ϊ>= ! ��Ϊ����һ���ͻ���ҵ���ʱ��֮�У���һ���ͻ�������
			
				que1.EnQueue(client_array + i);
				 
				CheckQue1(que1, que2, total_money, time, deal_time);
				//������cout << "ok";
			}
			
			if (time > close_time) break;
		}
		//��ֹ��ѭ��
		time++;
	}

	//���
	int wait_time_sum = 0;
	for (int i = 0; i < num; i++) {
		if (client_array[i].not_dealed) {
			client_array[i].wait_time = close_time - client_array[i].arrive_time;
		}	
		wait_time_sum += client_array[i].wait_time;
		cout << client_array[i].wait_time<<endl;
	}
	cout << (wait_time_sum / num);

    return 0;
}
