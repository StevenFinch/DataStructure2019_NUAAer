/*	Compiler: Visual Studio 2019
**	UpdateTime: 2019/12/24
**	ID: 161840225   */

#include<bits/stdc++.h>  
using namespace std;

const int X = 10;
const int Y = 10;
const int MaxSize = 100;

int M[X][Y];//maze

struct
{
	int i;//x
	int j;//y
	int di;//direction
}S[MaxSize];

int top = -1;

void GetPath(int xi, int yi, int xe, int ye)//入口：(xi,yi)	出口：(xe,ye)    
{
	int i, j, di, k;

	//初始方块进栈
	top++;
	S[top].i = xi;
	S[top].j = yi;
	S[top].di = -1;
	M[xi][yi] = -1;//来过防止重复走

	while (top > -1)
	{
		i = S[top].i;
		j = S[top].j;
		di = S[top].di;

		//抵达出口
		if (i == xe && j == ye)
		{
			cout << "迷宫路径如下：" << endl << endl;
			for (k = 0; k <= top; k++)
			{
				cout << "(" << S[k].i << "," << S[k].j << ") ";
				if ((k + 1) % 5 == 0) cout << endl;
			}
			cout << endl << endl;
			return;
		}

		//寻找通路
		int find = 0;
		while (di < 4 && find == 0)
		{
			di++;
			switch (di)
			{
			case 0://left
				i = S[top].i - 1;
				j = S[top].j;
				break;
			case 1://up
				i = S[top].i;
				j = S[top].j + 1;
				break;
			case 2://right
				i = S[top].i + 1;
				j = S[top].j;
				break;
			case 3://down
				i = S[top].i;
				j = S[top].j - 1;
				break;
			}
			if (M[i][j] == 0)
				find = 1;
		}
		//找到通路下一个方块入栈
		if (find == 1)
		{
			S[top].di = di;//明确上一方块的di

			//下一个方块进栈
			top++;
			S[top].i = i;
			S[top].j = j;
			S[top].di = -1;
			M[i][j] = -1;//来过防止重复走
		}

		//走投无路该方块出栈
		else
		{
			M[S[top].i][S[top].j] = 0;//该位置可以走
			top--;
		}
	}
	cout << "没有可走路径！" << endl << endl;
}

int main()
{
	//读取迷宫，0：通道，1：墙
	fstream fin("maze.txt");
	for (int i = 0; i < X; i++)
	{
		for (int j = 0; j < Y; j++)
		{
			fin >> M[i][j];
		}
	}
	fin.close();

	int xi, xe, yi, ye;
	while (1)
	{
		cout << "请输入迷宫入口(1-8)，输入0结束读取：";// 1 1
		cin >> xi >> yi;
		cout << endl;

		cout << "请输入迷宫出口(1-8)，输入0结束读取：";// 8 8
		cin >> xe >> ye;
		cout << endl;

		if (xi == 0 || yi == 0 || xe == 0 || ye == 0)
		{
			cout << "程序结束！" << endl;
			return 0;
		}

		if (1 <= xi && xi <= 8 && 1 <= yi && yi <= 8 && 1 <= xe && xe <= 8 && 1 <= ye && ye <= 8)
		{
			GetPath(xi, yi, xe, ye);
		}
		else
		{
			cout << "读取失败,请重新输入!" << endl << endl;
		}
	}

}