/*	Compiler: Visual Studio 2019
**	UpdateTime: 2019/12/10
**	ID: 161840225   */
#include<iostream>
#include<ctime>
using namespace std;

void Sift(int a[], int low, int high)
{
	int i = low;
	int j = 2 * i;
	int temp = a[i];
	while (j <= high)
	{
		if (j < high && a[j] < a[j + 1])
		{//�ҳ��ϴ�ĺ����±�
			j++;
		}
		if (temp < a[j])
		{//�ϴ�ĺ��ӷŵ�˫�׽���λ���ϣ���������Ѱ��
			a[i] = a[j];
			i = j;
			j = 2 * i;
		}
		else//�������
			break;
	}
	a[i] = temp;
}
void HeapSort(int a[], int n)
{
	int i;
	int temp;
	for (i = n / 2; i >= 1; i--)//�ӵ�һ����Ҷ�ڵ㿪ʼ��ǰ�����������±��1��ʼ
	{//�����󶥶�
		Sift(a, i, n);
	}
	for (i = n; i >= 2; i--)
	{//������
		temp = a[1];
		a[1] = a[i];
		a[i] = temp;
		Sift(a, 1, i - 1);
	}
}
int main()
{
	srand((unsigned)time(NULL));
	const int n = 10;
	int a[n + 1];
	int i;
	for (i = 1; i < n + 1; i++)
	{
		a[i] = rand() % 100;
	}
	cout << "������У�";
	for (i = 1; i < n + 1; i++)
	{
		cout << a[i] << ' ';
	}
	cout << endl;
	HeapSort(a, n);
	cout << "�������У�";
	for (i = 1; i < n + 1; i++)
	{
		cout << a[i] << ' ';
	}
	return 0;
}