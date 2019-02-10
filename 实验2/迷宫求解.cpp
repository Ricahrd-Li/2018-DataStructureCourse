#include<cstdlib>
#include<iostream>
using namespace std;

//*****˼·***** �����·�����ö��н��й������������ĳ�����Ӻ�����Χ�����ߵ�λ����ӣ�
//                           �ٶ�ͷ���ӣ�ֱ����ͷλ��Ϊ�յ�λ�ã���ȷ������� 
 
//����λ�ý�㣺
typedef struct pos_node {
	struct pos_node * prior = NULL;    //����ǰ����Ŀ�ģ������ʱ�����Թ������е�ǰλ�õ�ǰ��
	int cur[2] = { 0 };    //current   ��ǰλ�ã�[0]Ϊx,[1]Ϊy
	struct pos_node * next = NULL;    //Ϊ��ʽ����
}pos, *ptr_pos;

//������ʽ����
typedef struct {
	ptr_pos rear;
	ptr_pos front;
}queue;

//����
int InitQueue(queue & que) {    //���г�ʼ��
	ptr_pos temp = (ptr_pos)malloc(sizeof(pos));  //ͷ���
	if (!temp)return 1;
	temp->next = NULL;
	temp->prior = NULL;

	que.front = que.rear = temp;
	return 0;
}

int Enter(queue & que, ptr_pos pos) {  //���
	if (!pos) {
		return 1;  //���pos ΪNULL���Ƿ����˳�
	}
	que.rear->next = pos;
	que.rear = que.rear->next;
	que.rear->next = NULL;
	return 0;
}

ptr_pos Out(queue & que) {   //����
	ptr_pos temp = que.front->next;//��ͷ
	//��Ϊ�ն��з���NULL��
	if (!temp) return NULL;
	//��������ֻ��һ��Ԫ�أ�Ҫ�޸�rear
	if (que.rear == temp)que.rear = que.front;

	que.front->next = temp->next;
	//���ӵ�Ԫ��δɾ������Ϊ���ʱ������
	return temp;
}
void print(ptr_pos p) {   //��ӡ
	if (p->prior!=NULL) print(p->prior);
	cout << "(" << p->cur[0]+1<<',' << p->cur[1]+1 << ")" << "->";
}
bool is_first = true;
void output(ptr_pos p,int* final)//����ͨ�����ñ����������� 
{
	if(p->prior!=NULL) output(p->prior,final);
	cout<<"("<<p->cur[0]+1<<","<<p->cur[1]+1<<")";
	if((p->cur[0]+1)!=(final[0]+1)||(p->cur[1]+1)!=(final[1]+1))
		cout<<"->";
}


void Moveable(ptr_pos pos, bool&up, bool&down, bool& left, bool& right, int** maze, int row, int column) {
	//�����жϵ�ǰλ�õ��������ҷ�λ�ܲ����ߵĺ���
	up = down = left = right = 0;//������
	if (pos->cur[0] + 1 < row && maze[(pos->cur[0] + 1)][pos->cur[1]] == 1)down = 1;
	if (pos->cur[0] - 1 >= 0 && maze[(pos->cur[0] - 1)][pos->cur[1]] == 1)up = 1;
	if (pos->cur[1] + 1 < column && maze[(pos->cur[0])][pos->cur[1] + 1] == 1)right = 1;
	if (pos->cur[1] - 1 >= 0 && maze[(pos->cur[0])][pos->cur[1] - 1] == 1)left = 1;
}

void Move(ptr_pos cur_pos, queue& que, int** maze, int row, int column) {
	bool left, right, up, down;
	Moveable(cur_pos, up, down, left, right, maze, row, column);
	if (up) {
		ptr_pos up_pos = (ptr_pos)malloc(sizeof(pos));
		up_pos->prior = cur_pos;
		up_pos->cur[0] = cur_pos->cur[0] - 1;
		up_pos->cur[1] = cur_pos->cur[1];
		up_pos->next = NULL;

        //��һ���޸��Թ������Ӧλ�õ�ֵ����Ϊ�˱�ʶ���λ���߹��ˣ����������ˣ�����ջ��
	  	maze[up_pos->cur[0]][up_pos->cur[1]] =-1;
		Enter(que, up_pos);  //���
	}
	if (down) {
		ptr_pos down_pos = (ptr_pos)malloc(sizeof(pos));
		down_pos->prior = cur_pos;
		down_pos->cur[0] = cur_pos->cur[0] + 1;
		down_pos->cur[1] = cur_pos->cur[1];
		down_pos->next = NULL;

		maze[down_pos->cur[0]][ down_pos->cur[1]] = -1;
		Enter(que, down_pos);

	}
	if (left) {
		ptr_pos left_pos = (ptr_pos)malloc(sizeof(pos));
		left_pos->prior = cur_pos;
		left_pos->cur[0] = cur_pos->cur[0];
		left_pos->cur[1] = cur_pos->cur[1] - 1;
		left_pos->next = NULL;

		maze[left_pos->cur[0]][left_pos->cur[1]] = -1;
		Enter(que, left_pos);
		;
	}
	if (right) {
		ptr_pos right_pos = (ptr_pos)malloc(sizeof(pos));
		right_pos->prior = cur_pos;
		right_pos->cur[0] = cur_pos->cur[0];
		right_pos->cur[1] = cur_pos->cur[1] + 1;
		right_pos->next = NULL;

		maze[right_pos->cur[0] ][ right_pos->cur[1]] =-1;

		Enter(que, right_pos);

	}

}

int main()
{
	//��ȡ�Թ�������������
	int m, n;//m �� n ��
	cin >> m >> n;

	//����������Թ�
	int** maze = (int**)malloc(m* sizeof(int*));
	for(int i=0;i<m;i++){
		maze[i]=(int*)malloc(n* sizeof(int));
	}
	
	for (int i = 0; i < m; i++) {
		for (int j = 0; j < n; j++) {
			int temp;
			cin>>temp;
			maze[i][j] = temp; 
		}
	}

	//��ȡ�����յ�
	ptr_pos start_pos = (ptr_pos)malloc(sizeof(pos));  //���
	int final[2]; //�յ�
		
	start_pos->prior= NULL;
	start_pos->next = NULL;

	cin>>start_pos->cur[0]>>start_pos->cur[1];
	start_pos->cur[0] -=1;  
	start_pos->cur[1] -=1;

	cin>>final[0]>>final[1];
	final[0] -=1; 
	final[1] -=1;

	//��ʼ��ʽ�Ĳ���
	maze[start_pos->cur[0]][start_pos->cur[1]] = -1;  

	queue que;
	InitQueue(que);   //��Ҫ��������

	Move(start_pos,que,maze,m,n);  //start_pos��Χ��pos���
	if (que.rear == que.front) {
		cout << "-1" << endl;
		return 0;
	}
	ptr_pos temp = Out(que);   

	while ((temp->cur[0] != final[0]) || (temp->cur[1] != final[1])){
		Move(temp, que, maze, m, n);
		//���п�ʱ��ȫ�����
		if (que.rear == que.front) break;
		temp = Out(que);
	}

	if ((temp->cur[0] == final[0]) && (temp->cur[1] == final[1])) {   //�ߵ����յ� ���ݹ��ӡ
		output(temp,final);
		//cout << "\b"<<" ";
		//cout << "\b\b" << " ";
	}
	else cout << "-1" << endl;
		

    return 0;
}


