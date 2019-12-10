/*	Compiler: Visual Studio 2019
**	UpdateTime: 2019/10/30
**	ID: 161840225   */

#include <iostream>
#include <cmath>
using namespace std;

int a[10001];//实间换空间
int main()
{
	for (int i = 1; i < 10001; i++)
	{//初始化
		a[i] = -1;
	}

	int n;//数字个数
	cin >> n;

	int pairnum = 0;
	for (int i = 0; i < n; i++)
	{
		int t;
		cin >> t;
		if (-1 == a[t])
		{
			a[t] = 1;
		}
	}	
	for (int i = 2; i < 10001; i++)
	{
		if (a[i - 1] == 1 && a[i] == 1)
		{
			pairnum++;
		}
	}
	cout << pairnum;
	return 0;
}
