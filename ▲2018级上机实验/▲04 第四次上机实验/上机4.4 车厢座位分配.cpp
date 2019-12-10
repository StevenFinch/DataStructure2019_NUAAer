/*	Compiler: Visual Studio 2019
**	UpdateTime: 2019/10/30
**	ID: 161840225   */
#include <iostream>
using namespace std;

const int SEATINITNUM = 5;
const int ROWNUM = 20;
typedef struct
{
	int begin;//ÿ����ʼλ�ñ��
	int left;//ÿ��ʣ����λ����
}Row;
bool DistributeSeats(Row R[], int p)
{//��ÿ����Ʊָ�������λ����
	if (p < 1 || p > SEATINITNUM)//�Ϸ��Լ���
		return false;
	int i, j;
	for (i = 1; i < ROWNUM + 1; i++)
	{
		if (R[i].left >= p)
		{//�����ڸ����ҵ�������λ
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
	{//��������λ
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
	{//��ʼ��������λ
		R[i].begin = SEATINITNUM * (i - 1) + 1;
		R[i].left = SEATINITNUM;
	}

	//��ȡ��Ʊָ��
	int n;
	cin >> n;//��Ʊ����
	int* a = new int[n + 1];
	for (int j = 1; j < n + 1; j++)
	{//��Ʊָ��
		cin >> a[j];
	}
	for (int k = 1; k < n + 1; k++)
	{//ans
		DistributeSeats(R, a[k]);
	}
	return 0;
}