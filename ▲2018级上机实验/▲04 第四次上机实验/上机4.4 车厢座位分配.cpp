/*	Compiler: Visual Studio 2019
**	UpdateTime: 2019/10/30
**	ID: 161840225   */
#include <iostream>
using namespace std;

const int SEATINITNUM = 5;
const int ROWNUM = 20;
typedef struct
{
	int begin;//每行起始位置编号
	int left;//每行剩余座位个数
}Row;
bool DistributeSeats(Row R[], int p)
{//对每个购票指令进行座位分配
	if (p < 1 || p > SEATINITNUM)//合法性检验
		return false;
	int i, j;
	for (i = 1; i < ROWNUM + 1; i++)
	{
		if (R[i].left >= p)
		{//可以在该行找到相邻座位
			for (j = 0; j < p; j++)
			{
				cout << R[i].begin << ' ';
				R[i].begin++;
				R[i].left--;
			}
			cout << endl;
			break;
		}
	}
	if (i > ROWNUM)
	{//无相邻座位
		int j = 1;
		while (j < ROWNUM + 1 && p > 0)
		{
			if (R[j].left > 0)
			{
				cout << R[j].begin << ' ';
				R[j].left--;
				p--;
			}
			else
			{
				j++;
			}
		}
		cout << endl;
	}
	return true;
}
int main()
{
	Row R[21];
	for (int i = 1; i < ROWNUM + 1; i++)
	{//初始化所有座位
		R[i].begin = SEATINITNUM * (i - 1) + 1;
		R[i].left = SEATINITNUM;
	}

	//读取购票指令
	int n;
	cin >> n;//购票数量
	int* a = new int[n + 1];
	for (int j = 1; j < n + 1; j++)
	{//购票指令
		cin >> a[j];
	}
	for (int k = 1; k < n + 1; k++)
	{//ans
		DistributeSeats(R, a[k]);
	}
	return 0;
}