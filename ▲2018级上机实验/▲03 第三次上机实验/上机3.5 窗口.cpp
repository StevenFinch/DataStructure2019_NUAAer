/*	Compiler: Visual Studio 2019
**	UpdateTime: 2019/10/20
**	ID: 161840225   */
#include<iostream>
#include<list>
#include<vector>
using namespace std;

struct win
{
	int num;
	int x1;
	int y1;
	int x2;
	int y2;
};
struct point
{
	int x;
	int y;
}point;
int main()
{
	//数据读取
	int N, M;
	cin >> N >> M;
	list<struct win> listWin(N);
	vector<struct point> vecPoint(M);
	int i = 1;//窗口标号
	for (auto iter = listWin.rbegin(); iter != listWin.rend(); iter++)
	{
		iter->num = i++;
		cin >> iter->x1 >> iter->y1 >> iter->x2 >> iter->y2;
	}
	for (auto iter = vecPoint.begin(); iter != vecPoint.end(); iter++)
	{
		cin >> iter->x >> iter->y;
	}

	//核心代码
	for (auto itp = vecPoint.begin(); itp != vecPoint.end(); itp++)
	{
		int flag = 0;
		for (auto itw = listWin.begin(); itw != listWin.end(); itw++)
		{
			if (itp->x >= itw->x1 && itp->x <= itw->x2 && itp->y >= itw->y1 && itp->y <= itw->y2)
			{
				cout << itw->num << endl;
				listWin.push_front(*itw);
				listWin.erase(itw);
				flag = 1;
				break;
			}
		}
		if (0 == flag)
		{
			cout << "IGNORED" << endl;
		}
	}
	system("pause");
	return 0;
}