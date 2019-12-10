/*	Compiler: Visual Studio 2019
**	UpdateTime: 2019/11/21
**	ID: 161840225   */
#include <iostream>
#include <algorithm>
using namespace std;

int a[6][4][4];//最大有五组棋盘输入，闲置0号位
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
int Situation(int k, int player)//1表示Alice 2表示Bob
{//判断player下完一步棋之后的局势
	int w = row(k, player) || col(k, player) || dia(k, player);
	if (0 == w)//对局结束
			return 0;
	else
	{//对局结束，返回评估得分
		w = space(k) + 1;
		return player == 1 ? w : -w;
	}
}
int DFS(int k, int player)
{//该步棋由player下，返回player下完该步棋之后该局面最大的评估得分
	if (0 == space(k))//平局
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
				if (s)//对局结束，返回该局面下评估得分
				{
					a[k][i][j] = 0;
					return s > 0 ? max(Max, s) : min(Min, s);
				}
				if (1 == player)//上一步棋是Bob下的，求接下来所有可能局面的最小值
					Max = max(Max, DFS(k, 2));
				else//上一步棋是Alice下的，求接下来所有可能局面的最大值
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
		//下棋之前先判断一下对局是否已经结束
		int y = Situation(k, 2);//如果Bob下完棋之后他赢了
		
		if (y)//直接输出评估得分
			cout << y << endl;
		else
			cout << DFS(k, 1) << endl;
	}
	return 0;
}