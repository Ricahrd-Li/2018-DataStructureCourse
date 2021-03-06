// paintGraph.cpp: 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include<graphics.h>
#include<iostream>
#include<string>

using namespace std;

typedef int** MGraph;
#define  RADIUM 20
#define  TEXT_X 15
#define  TEXT_Y 26

typedef struct position {
	int x, y;
}position;

//生成begin--begin+x内的int
int Rand(int x, int begin = 0) {
	//srand((int)time(0));
	return begin + (rand() % x);
}

void RandomPos(position pos[], int num) {
	for (int i = 0; i<num; i++) {
		bool rightx, righty;

		do {
			rightx = 1;
			pos[i].x = Rand(600, 10);
			for (int j = 0; j<i; j++) {
				if (abs(pos[j].x - pos[i].x)<40)
					rightx = 0;
			}
		} while (rightx == 0);

		do {
			righty = 1;
			pos[i].y = Rand(600, 10);
			for (int j = 0; j<i; j++) {
				if (abs(pos[j].y - pos[i].y)<40)
					righty = 0;
			}
		} while (righty == 0);
	}
}

int main()
{
	int vexnum, edgenum;
	std::cin >> vexnum >> edgenum;
	MGraph G;
	G = (MGraph)malloc(sizeof(int*)*vexnum);
	for(int i = 0; i < vexnum; i++) {
		G[i] = (int *)malloc(sizeof(int)*vexnum);
	}
	//邻接矩阵先清零
	for(int i = 0; i < vexnum; i++) {
		for (int j = 0; j < vexnum; j++) {
			G[i][j] = 0;
		}
	}
	//边的关系
	for(int i = 0; i < edgenum; i++) {
		int a, b;
		std::cin >> a >> b;
		G[a - 1][b - 1] = G[b - 1][a - 1] = 1;
	}
	
	position* pos = new position[vexnum];
	char c='a';
	//initgraph(640, 480);   // 创建绘图窗口，大小为 640x480 像素
	while (c !='p') {
		RandomPos(pos, vexnum);
		initgraph(900, 700);   // 创建绘图窗口，大小为 640x480 像素


		for (int i = 0; i < vexnum; i++) {
			for (int j = 0; j < vexnum; j++) {
				if (G[i][j])line(pos[i].x + TEXT_X + 4, pos[i].y + TEXT_Y - 3, 
					pos[j].x + TEXT_X + 4, pos[j].y + TEXT_Y - 3);
			}
		}
		for (int i = 0; i < vexnum; i++) {
			clearcircle(pos[i].x + 15, pos[i].y + 15, RADIUM);
			circle(pos[i].x + 15, pos[i].y + 15, RADIUM);
			TCHAR s[5];
			_stprintf_s(s, _T("%d"), i);
			outtextxy(pos[i].x + 10, pos[i].y + 10, s);

		}
		c = getchar();
	}
	closegraph();          // 关闭绘图窗口
    return 0;

}

