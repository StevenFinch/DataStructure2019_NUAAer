/*	Compiler: Visual Studio 2019
**	UpdateTime: 2019/10/30
**	ID: 161840225   */
#include<iostream>
#include <iostream>
#include <time.h>
#include <iomanip>
#include <algorithm>
using namespace std;

const int M = 4;
const int N = 4;
void FindSaddlePoint(int a[M][N])
{
	int i, j, t;//i, j最好在循环内初始化
	int min;//某行最小元素
	int colindex[N + 1];//存储该行最小元素列标
	int colnum = 0;//该行最小元素数量

	for (i = 0; i < M; i++)
	{//遍历每行
		min = *min_element(a[i], a[i] + N - 1);//找到该行最小元素
		for (j = 0; j < N; j++)
		{//遍历每列是因为该行可能有多个相同元素都为最小值
			if (a[i][j] == min)
				colindex[colnum++] = j;//记录元素个数即所在行标
		}
		for (t = 0; t < colnum; t++)
		{//遍历该行每个最小元素，为了检查该元素是否为其所在列的最大值，若是则马鞍点数量加一。
			int flag = 1;
			for (int p = 0; p < M; p++)
			{
				if (a[p][colindex[t]] > min)
					flag = 0;
			}
			if (1 == flag)
			{
				cout << "(" << i << "," << colindex[t] << ",";
				cout << a[i][colindex[t]] << ")" << endl;
			}
		}
		colnum = 0;
	}
	return;
}
int main()
{
	int a[M][N] = {
		{4, 4, 4, 4},
		{4, 4, 4, 4},
		{4, 7, 4, 7},
		{4, 4, 4, 4}
	};
	FindSaddlePoint(a);
	return 0;
}
