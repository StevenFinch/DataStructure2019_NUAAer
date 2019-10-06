/***************************************
 **   Filename： 买菜时间换空间解法.cpp
 **
 **   Compiler:  Visual Studio 2019
 **
 **   StudentID: 1618*****
 **
 **   Name:      Steven
 **
 ***************************************/
#include <iostream>
using namespace std;

int duration[1000001];
int a[2001], b[2001], c[2001], d[2001];	//存二人时间段端点值

int main()
{
	int n;	//时间段的数量
	cin >> n;

	for (int i = 1; i < 1000001; i++)
	{
		duration[i] = 0;	
	}
	for (int i = 1; i < n + 1; i++)
	{
		cin >> a[i] >> b[i];
		for (int j = a[i]; j < b[i]; j++)
		{
			duration[j]++;	//标记小H时间段
		}
	}
	for (int i = 1; i < n + 1; i++)
	{
		cin >> c[i] >> d[i];
		for (int j = c[i]; j < d[i]; j++)
		{
			duration[j]++;	//标记小W时间段
		}
	}
	int count = 0;
	for (int i = 1; i < 1000001; i++)
	{
		if (duration[i] > 1)
		{
			count++;	//找出二人公有标记
		}
	}
	cout << count << endl;

	system("pause");
	return 0;	//函数正常结束
}
