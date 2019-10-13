/***************************************
 **   Filename�� ���ʱ�任�ռ�ⷨ.cpp
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

int duration[1000001];
int a[2001], b[2001], c[2001], d[2001];	//�����ʱ��ζ˵�ֵ

int main()
{
	int n;	//ʱ��ε�����
	cin >> n;

	for (int i = 1; i < 1000001; i++)
	{
		duration[i] = 0;	
	}
	for (int i = 1; i < n + 1; i++)
	{
		cin >> a[i] >> b[i];
		for (int j = a[i]; j < b[i]; j++)
		{
			duration[j]++;	//���СHʱ���
		}
	}
	for (int i = 1; i < n + 1; i++)
	{
		cin >> c[i] >> d[i];
		for (int j = c[i]; j < d[i]; j++)
		{
			duration[j]++;	//���СWʱ���
		}
	}
	int count = 0;
	for (int i = 1; i < 1000001; i++)
	{
		if (duration[i] > 1)
		{
			count++;	//�ҳ����˹��б��
		}
	}
	cout << count << endl;

	system("pause");
	return 0;	//������������
}
