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
		{//找出较大的孩子下标
			j++;
		}
		if (temp < a[j])
		{//较大的孩子放到双亲结点的位置上，继续向下寻找
			a[i] = a[j];
			i = j;
			j = 2 * i;
		}
		else//调整完毕
			break;
	}
	a[i] = temp;
}
void HeapSort(int a[], int n)
{
	int i;
	int temp;
	for (i = n / 2; i >= 1; i--)//从第一个非叶节点开始向前调整，数组下标从1开始
	{//建立大顶堆
		Sift(a, i, n);
	}
	for (i = n; i >= 2; i--)
	{//堆排序
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
	cout << "随机序列：";
	for (i = 1; i < n + 1; i++)
	{
		cout << a[i] << ' ';
	}
	cout << endl;
	HeapSort(a, n);
	cout << "排序序列：";
	for (i = 1; i < n + 1; i++)
	{
		cout << a[i] << ' ';
	}
	return 0;
}