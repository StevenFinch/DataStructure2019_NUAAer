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
	�÷ֺ����벻ͬ����ô����
	*/

	int x;//��������
	int t = 1;//���ε÷�
	int sum = 0;//�ܷ�

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