/*	Compiler: Visual Studio 2019
**	UpdateTime: 2019/12/10
**	ID: 161840225   */
#include<iostream>
#include<ctime>
using namespace std;
const int n = 10;
void BubbleSort(int a[], int n)
{
	int i, j, flag;
	int temp;
	for (i = n - 1; i >= 1; i--)
	{
		flag = 0;
		for (j = 1; j <= i; j++)
		{
			if (a[j - 1] > a[j])
			{
				temp = a[j - 1];
				a[j - 1] = a[j];
				a[j] = temp;
				flag = 1;
			}
		}
		if (0 == flag)
			break;
	}
}
void SelectSort(int a[], int n)
{
	int i, j, k;
	int temp;
	for (i = 0; i < n; i++)
	{
		k = i;
		for (j = i + 1; j < n; j++)
		{
			if (a[k] > a[j])
				k = j;
		}
		if (k != i)
		{
			temp = a[i];
			a[i] = a[k];
			a[k] = temp;
		}
	}
}
void Merge(int a[], int low, int mid, int high)
{
	int temp[n];
	int i = low;
	int j = mid + 1;
	int k = 0;
	while (i != mid + 1 && j != high + 1)
	{
		if (a[i] <= a[j])
			temp[k++] = a[i++];
		else
			temp[k++] = a[j++];
	}
	while (i !=mid + 1)
	{
		temp[k++] = a[i++];
	}
	while (j != high + 1)
	{
		temp[k++] = a[j++];
	}
	for (i = 0; i < k; i++)
	{
		a[low + i] = temp[i];
	}
}
void MergeSort(int a[], int low, int high)
{
	if (low < high)
	{
		int mid = (low + high) / 2;
		MergeSort(a, low, mid);
		MergeSort(a, mid + 1, high);
		Merge(a, low, mid, high);
	}
}

int main()
{
	
	srand((unsigned)time(NULL));
	int a[n];
	int i;
	for (i = 0; i < n; i++)
		a[i] = rand() % 100;
	cout << "Ëæ»úÐòÁÐ£º";
	for (i = 0; i < n; i++)
		cout << a[i] << ' ';
	cout << endl;
	MergeSort(a, 0, n - 1);
	cout << "ÅÅÐòÐòÁÐ£º";
	for (i = 0; i < n; i++)
		cout << a[i] << ' ';
	return 0;
}