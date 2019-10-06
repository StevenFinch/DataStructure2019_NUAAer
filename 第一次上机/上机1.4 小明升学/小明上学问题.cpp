/***************************************
 **   Filename： 小明上学.cpp
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

int main()
{
	int r, y, g;
	cin >> r >> y >> g;
	int n;
	cin >> n;
	int sum = 0;
	int p, q;
	for (int i = 0; i < n; i++)
	{
		cin >> p >> q;
		switch (p)
		{
		case 0://road
			sum += q;
			break;
		case 1://red
			sum += q;
			break;
		case 2://yellow
			sum += q + r;
			break;
		default:
			break;
		}
	}
	cout << sum;
	system("pause");
	return 0;
}
