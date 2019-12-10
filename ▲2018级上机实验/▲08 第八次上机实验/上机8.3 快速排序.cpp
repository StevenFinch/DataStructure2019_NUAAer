/*	Compiler: Visual Studio 2019
**	UpdateTime: 2019/12/10
**	ID: 161840225   */
#include<iostream>
#include<ctime>
using namespace std;
const int n = 10;

void QuickSort(int a[], int low, int high)
{
	int temp;
	int i = low;
	int j = high;
	if (low < high)
	{
		temp = a[low];
		while (i < j)
		{
			while (i < j && a[j] >= temp)
				j--;
			if (i < j)
				a[i++] = a[j];

			while (i < j && a[i] < temp)
				i++;
			if (i < j)
				a[j--] = a[i];
		}
		a[i] = temp;
		QuickSort(a, low, i - 1);
		QuickSort(a, i + 1, high);
	}
}
int main()
{
	//随机数生成
	srand((unsigned)time(NULL));
	int a[n];
	int i;
	for (i = 0; i < n; i++)
		a[i] = rand() % 100;
	cout << "随机序列：";
	for (i = 0; i < n; i++)
		cout << a[i] << ' ';
	cout << endl;
	QuickSort(a, 0, n - 1);
	cout << "排序序列：";
	for (i = 0; i < n; i++)
		cout << a[i] << ' ';
	return 0;
}