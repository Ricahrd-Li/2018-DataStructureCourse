#include<cstdio>
#define MAX 2000000

int MGraph[10001][10001] = { 0 };

int Prim(int vexnum){
	int result = 0;         //��С�������ĳ��� 
	int i,n,min,min_vex,count;
	
	int mincost[10001] = { 0 }; 

    for (i=1;i<=vexnum;i++) mincost[i]=MAX;     //�Ƚ�mincostȫ�������ֵ��������minֵ

    mincost[1]=0;   //mincost[1]������� 
    n=1;
  
    for(count=1;count<=vexnum-1;count++){   //count���ڼ����Ѿ����������еĶ�����Ŀ 
        min_vex=0;
        min=MAX;
  
        for (i=2;i<=vexnum;i++){
            if (MGraph[n][i]!=0 && mincost[i]!=0 ){
           		 if (MGraph[n][i]<mincost[i]) 
					mincost[i]=MGraph[n][i];
			}
            if (mincost[i]<min && mincost[i]!=0) {
            	min_vex=i;
				min=mincost[i];
			}
        
		}
		n=min_vex;
        result+=mincost[min_vex];
        mincost[min_vex]=0;   
    }
    return result;
}

int main()
{
    int vexnum,edgenum,weight,x,y;
	scanf("%d%d",&vexnum,&edgenum);
	
    
    for (int i=0;i<edgenum;i++){
        scanf("%d%d%d",&x,&y,&weight);
        MGraph[x][y]=weight;
        MGraph[y][x]=weight;
    }

    printf("%d",Prim(vexnum));
}
