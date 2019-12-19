/*	Compiler: Visual Studio 2019
**	UpdateTime: 2019/12/18
**	ID: 161840225   */

#include <iostream>
#include <algorithm>
#include <fstream>
using namespace std;

int main()
{
	/*
	得分和输入不同就这么处理
	*/

	int x;//本次输入
	int t = 1;//本次得分
	int sum = 0;//总分

	fstream fin("text.txt");
	while (fin >> x && x) 
	{
		if (x == 1)
		{
			t = 1;
			sum += t;
		}
		else if (x == 2) 
		{
			if (t == 1)
			{
				t = 2;
			}
			else
			{
				t += 2;
			}
			sum += t;
		}
	}
	cout << sum << endl;
	return 0;
}