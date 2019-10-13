/***************************************
 **   Filename： 折点计算.cpp
 **
 **   Compiler:  Visual Studio 2019
 **
 **   StudentID: 1618*****
 **
 **   Name:      Steven
 **
 ***************************************/
#include <iostream>
#include <vector>

using namespace std;

int main()
{
	vector<int> vec;
	int n;//输入整数数量
	cin >> n;
	int temp;//临时记录输入数字
	int num = 0;//折点数量
	for (int i = 0; i < n; i++)
	{
		cin >> temp;
		vec.push_back(temp);
	}
	for (int i = 1; i < vec.size() - 1; i++)
	{
		if (vec[i] > vec[i - 1] && vec[i] > vec[i + 1])
		{
			num++;
		}
		else if (vec[i] < vec[i - 1] && vec[i] < vec[i + 1])
		{
			num++;
		}
	}
	cout << num << endl;
	system("pause");
	return 0;
}
