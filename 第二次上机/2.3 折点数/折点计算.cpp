/***************************************
 **   Filename�� �۵����.cpp
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
	int n;//������������
	cin >> n;
	int temp;//��ʱ��¼��������
	int num = 0;//�۵�����
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
