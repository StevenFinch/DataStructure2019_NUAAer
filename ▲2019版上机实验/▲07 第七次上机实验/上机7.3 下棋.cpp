/*	Compiler: Visual Studio 2019
**	UpdateTime: 2019/11/21
**	ID: 161840225   */
#include <iostream>
#include <algorithm>
using namespace std;

int a[6][4][4];//����������������룬����0��λ
bool row(int k, int player)
{
	for (int i = 1; i < 4; i++)
	{
		if (a[k][i][1] == player && a[k][i][2] == player && a[k][i][3] == player)
			return true;//game over
	}
	return false;
}
bool col(int k, int player)
{
	for (int i = 1; i < 4; i++)
	{
		if (a[k][1][i] == player && a[k][2][i] == player && a[k][3][i] == player)
			return true;//game over
	}
	return false;
}
bool dia(int k, int player)
{
	if ((a[k][1][1] == player && a[k][2][2] == player && a[k][3][3] == player) ||
		(a[k][1][3] == player && a[k][2][2] == player && a[k][3][1] == player))
		return true;//game over
	return false;
}
int space(int k)
{
	int total = 0;
	for (int i = 1; i < 4; i++)
	{
		for (int j = 1; j < 4; j++)
		{
			if (0 == a[k][i][j])
				total++;
		}
	}
	return total;
}
int Situation(int k, int player)//1��ʾAlice 2��ʾBob
{//�ж�player����һ����֮��ľ���
	int w = row(k, player) || col(k, player) || dia(k, player);
	if (0 == w)//�Ծֽ���
			return 0;
	else
	{//�Ծֽ��������������÷�
		w = space(k) + 1;
		return player == 1 ? w : -w;
	}
}
int DFS(int k, int player)
{//�ò�����player�£�����player����ò���֮��þ������������÷�
	if (0 == space(k))//ƽ��
		return 0;
	int Max = -10;
	int Min = 10;
	for (int i = 1; i < 4; i++)
	{
		for (int j = 1; j < 4; j++)
		{
			if (0 == a[k][i][j])
			{
				a[k][i][j] = player;
				int s = Situation(k, player);
				if (s)//�Ծֽ��������ظþ����������÷�
				{
					a[k][i][j] = 0;
					return s > 0 ? max(Max, s) : min(Min, s);
				}
				if (1 == player)//��һ������Bob�µģ�����������п��ܾ������Сֵ
					Max = max(Max, DFS(k, 2));
				else//��һ������Alice�µģ�����������п��ܾ�������ֵ
					Min = min(Min, DFS(k, 1));
				a[k][i][j] = 0;//!
			}
		}
	}
	return 1 == player ? Max : Min;
}
int main()
{
	int n;
	cin >> n;
	for (int k = 1; k < n + 1; k++)
	{
		for (int i = 1; i < 4; i++)
		{
			for (int j = 1; j < 4; j++)
			{
				cin >> a[k][i][j];
			}
		}
	}
	for (int k = 1; k < n + 1; k++)
	{
		//����֮ǰ���ж�һ�¶Ծ��Ƿ��Ѿ�����
		int y = Situation(k, 2);//���Bob������֮����Ӯ��
		
		if (y)//ֱ����������÷�
			cout << y << endl;
		else
			cout << DFS(k, 1) << endl;
	}
	return 0;
}