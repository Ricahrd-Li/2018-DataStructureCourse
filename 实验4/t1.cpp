#include<cstdlib>
#include<iostream>
using namespace std;

typedef int** MGraph;

void DFS(MGraph G, int begin_vex,int vexnum,bool* visited) {
	cout << begin_vex+ 1 << ' ';
	for (int i = 0; i < vexnum; i++) {
		if (G[begin_vex][i]&&!visited[i]) {
			visited[i] = 1;
			DFS(G, i, vexnum,visited);
		}
	}
}

//����

class Queue {
	typedef struct qnode {
		int vex;
		struct qnode* next;
	}qnode,*ptr_qnode;

	ptr_qnode rear;
	ptr_qnode front;
public:
	Queue() {    //���г�ʼ��
		//ͷ���
		ptr_qnode temp = (ptr_qnode)malloc(sizeof(qnode));  //ͷ���
		if (!temp) return;
		temp->vex=-1;  //ͷ����vex��-1
		temp->next = NULL;

		front = rear = temp;
	}

	~Queue() {
	}

	int EnQueue(int vertex) {  //���
		ptr_qnode temp = (ptr_qnode)malloc(sizeof(qnode));
		temp->vex = vertex;
		temp->next = NULL;

		rear->next = temp;
		rear = rear->next;
		return 0;
	}

	bool EmptyQueue() {
		if (front == rear)return 1;
		else return 0;

	}

	int DeQueue() {   //����,���ص���vex
		ptr_qnode temp = front->next;//��ͷ
									 //��Ϊ�ն��з���NULL��
		if (!temp) return NULL;
		//��������ֻ��һ��Ԫ�أ�Ҫ�޸�rear
		if (rear == temp)rear = front;

		front->next = temp->next;
		int p = temp->vex;
		free(temp);
		return p;
	}
};

void BFS(MGraph G, int begin_vex, int vexnum,bool*visited,Queue& que) {
	cout << begin_vex+1<< ' ';
	for (int i = 0; i < vexnum; i++) {
		if (G[begin_vex][i] && !visited[i]) {
			cout << i + 1 << ' ';
			visited[i] = 1;
			que.EnQueue(i);
		}
	}
	while (!que.EmptyQueue()) {  //�����в���ʱ
		int vex = que.DeQueue();
		for (int i = 0; i < vexnum; i++) {
			if (G[vex][i] && !visited[i]) {
				cout << i + 1 << ' ';
				visited[i] = 1;
				que.EnQueue(i);
			}
		}
	}
	
}

int main()
{
	//����ͼ
	int vexnum, edgenum;
	MGraph G;

	cin >> vexnum >> edgenum;
	G = (MGraph)malloc(sizeof(int*)*vexnum);
	for (int i = 0; i < vexnum; i++) {
		G[i] = (int *)malloc(sizeof(int)*vexnum);
	}
	//�ڽӾ���������
	for (int i = 0; i < vexnum; i++) {
		for (int j = 0; j < vexnum; j++) {
			G[i][j] = 0;
		}
	}
	//�ߵĹ�ϵ
	for (int i = 0; i < edgenum; i++) {
		int a, b;
		cin >> a>>b;
		G[a-1][b-1] = G[b-1][a-1] = 1;
	}
	
	int begin_vex;
	cin >> begin_vex;
	//DFS
	bool* visited=(bool*)malloc(sizeof(bool)*vexnum);
	for (int i = 0; i < vexnum; i++)visited[i] = 0;
	visited[begin_vex-1] = 1;  
	DFS(G, begin_vex-1, vexnum, visited);

	cout << endl;

	//BFS
	Queue que;
	for (int i = 0; i < vexnum; i++)visited[i] = 0;
	visited[begin_vex - 1] = 1;
	BFS(G, begin_vex - 1, vexnum, visited, que);

    return 0;
}

