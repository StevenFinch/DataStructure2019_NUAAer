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
	int i, j, t;//i, j�����ѭ���ڳ�ʼ��
	int min;//ĳ����СԪ��
	int colindex[N + 1];//�洢������СԪ���б�
	int colnum = 0;//������СԪ������

	for (i = 0; i < M; i++)
	{//����ÿ��
		min = *min_element(a[i], a[i] + N - 1);//�ҵ�������СԪ��
		for (j = 0; j < N; j++)
		{//����ÿ������Ϊ���п����ж����ͬԪ�ض�Ϊ��Сֵ
			if (a[i][j] == min)
				colindex[colnum++] = j;//��¼Ԫ�ظ����������б�
		}
		for (t = 0; t < colnum; t++)
		{//��������ÿ����СԪ�أ�Ϊ�˼���Ԫ���Ƿ�Ϊ�������е����ֵ������������������һ��
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
