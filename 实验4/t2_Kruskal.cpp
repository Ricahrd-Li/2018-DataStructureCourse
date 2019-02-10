// Kruskal.cpp: �������̨Ӧ�ó������ڵ㡣
//
#include<cstdlib>
#include<cstdio>
typedef struct edge {
	int w;
	int a, b;   //����a��b
}edge;

//Find�������ڶԲ��鼯����·��ѹ�������ر�־
int Find(int* uset,int x){        
	if (uset[x] != x) uset[x]= Find(uset, uset[x]);
	return uset[x];
}

//Union�������ںϲ����鼯
void Union(int* uset, int x, int y){  //�Բ��鼯���кϲ�
	if (Find(uset,x)!= Find(uset,y)) uset[uset[y]]= uset[x];
}

//compare�������ڿ���
int compare(const void* x,const void* y) {
	edge* e1 = (edge*)x;
	edge* e2 = (edge*)y;
	if (e1->w > e2->w)return 1;
	else if (e1->w < e2->w)return -1;
	else return 0;
}

int Kruskal(edge* Edge,int* uset,int edgenum,int vexnum) {
	int result=0;   //���õ����������ĳ���
	
	qsort(Edge, edgenum, sizeof(edge), compare);
	///�����ã�������Ž����for (int i = 0; i < edgenum; i++) printf("%d ",Edge[i].w);
	
	result += Edge[0].w;
	Union(uset,Edge[0].a, Edge[0].b);
	int count = 1;

	for (int i = 1; i < edgenum&&count<vexnum-1; i++) {
		if (Find(uset,Edge[i].a) == Find(uset,Edge[i].b))continue;
		else {
			Union(uset, Edge[i].a, Edge[i].b); 
			result += Edge[i].w;
			count++;
		}
	}
	return result;
}

int main()
{   
	int vexnum, edgenum;
	scanf("%d%d",&vexnum,&edgenum);
	edge* Edge = (edge*)malloc(sizeof(edge)*edgenum);
	int* uset = (int *)malloc(sizeof(int)*(vexnum+1));   //���鼯���ж�ȦҪ�ö�

	for (int i = 0; i < edgenum; ++i) {
		scanf("%d%d%d",&Edge[i].a,&Edge[i].b,&Edge[i].w);
	}
	for (int i = 1; i <= vexnum; i++) {   //ע�ⶥ��1--vexnum
		uset[i] = i;     //��ʼʱ�����鼯�е�ÿ�����ĸ��ڵ㶼ָ������
	}
	printf("%d",Kruskal(Edge,uset,edgenum,vexnum));
	return 0;
}


