/***************************************
 **   Filename£º ÏñÕÒÖĞÎÄÊı.cpp
 **
 **   Compiler:  Visual Studio 2019
 **
 **   StudentID: 1618*****
 **
 **   Name:      Steven
 **
 ***************************************/

#include<iostream>
#include<set>
using namespace std;
int main()
{
	set<int> setNum;
	int n;
	cin >> n;
	int temp;
	for (int i = 0; i < n; i++)
	{
		cin >> temp;
		setNum.insert(temp);
	}

	if (setNum.size() % 2 == 0)
	{
		cout << -1;
	}
	else
	{
		set<int>::iterator iter = setNum.begin();
		advance(iter, (setNum.size() + 1) / 2 - 1);
		cout << *iter;
	}
	system("pause");
	return 0;
}