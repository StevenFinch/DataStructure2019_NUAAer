/*	Compiler: Visual Studio 2019
**	UpdateTime: 2019/09/27
**	ID: 161840225   */
#include <iostream>
#include <algorithm>

using namespace std;

int a[2001], b[2001], c[2001], d[2001];

int main()
{
	int n;
	cin >> n;//时间段数量
	for (int i = 1; i < n + 1; i++)
	{
		cin >> a[i] >> b[i];//存小h
	}
	for (int i = 1; i < n + 1; i++)
	{
		cin >> c[i] >> d[i];//存小w
	}
	int sum = 0;
	//关键在于两层循环找出重叠时间段
	for (int i = 1; i < n + 1; i++)
	{
		for (int j = 1; j < n + 1; j++)
		{
			int left = max(a[i], c[j]);
			int right = min(b[i], d[j]);
			if (left < right)
			{
				sum += right - left;//增加重叠时间
			}
		}
	}
	cout << sum << endl;
	system("pause");
	return 0;
}
