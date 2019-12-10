/*	Compiler: Visual Studio 2019
**	UpdateTime: 2019/09/27
**	ID: 161840225   */
#include <iostream>
#include <algorithm>

using namespace std;

int a[2001], b[2001], c[2001], d[2001];

int main()
{
	int n;
	cin >> n;//ʱ�������
	for (int i = 1; i < n + 1; i++)
	{
		cin >> a[i] >> b[i];//��Сh
	}
	for (int i = 1; i < n + 1; i++)
	{
		cin >> c[i] >> d[i];//��Сw
	}
	int sum = 0;
	//�ؼ���������ѭ���ҳ��ص�ʱ���
	for (int i = 1; i < n + 1; i++)
	{
		for (int j = 1; j < n + 1; j++)
		{
			int left = max(a[i], c[j]);
			int right = min(b[i], d[j]);
			if (left < right)
			{
				sum += right - left;//�����ص�ʱ��
			}
		}
	}
	cout << sum << endl;
	system("pause");
	return 0;
}
