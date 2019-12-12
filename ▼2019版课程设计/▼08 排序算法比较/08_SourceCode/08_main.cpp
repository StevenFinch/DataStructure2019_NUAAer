/*	Compiler: Visual Studio 2019
**	UpdateTime: 2019/12/12
**	ID: 161840225   */
#include<iostream>
#include<fstream>
#include<string>
#include<ctime>
#include<iomanip>
#include<queue>

using namespace std;
const int n = 20000;//ÿ�����ݼ�20000��Ԫ��
const int m = 10;//10�����ݼ�

void PutData();

void InsertSort(int a[]);
void ShellSort(int a[], int derta[], int t);

void BubbleSort(int a[]);
void QuickSort(int a[], int low, int high);

void SelectSort(int a[]);
void Sift(int a[], int low, int high);
void HeapSort(int a[]);

void Merge(int a[], int low, int mid, int high);
void MergeSort(int a[]);

void RadixSort(int a[]);

int main()
{
	PutData();//�������ݼ�
	int i;
	clock_t start, stop;
	float duration;
	string file;
	//ֱ�Ӳ�������
	cout << "��ֱ�Ӳ�������" << endl << endl;
	for (i = 1; i < 11; i++)
	{
		file = "data" + to_string(i) + ".txt";
		fstream fin(file);
		int a[n + 1];
		for (int j = 1; j < n + 1; j++)
		{//��ȡ���ݼ�
			fin >> a[j];
		}
		start = clock();
		InsertSort(a);
		stop = clock();
		duration = ((float)(stop - start) / CLK_TCK);	/* CLK_TCK�ǻ���û�뾭����tick */
		cout.fill('0');
		cout << "Time" << setw(2) << i << ": ";
		cout.fill(' ');
		cout << setw(5) << duration << endl << endl;
	}

	//ϣ������
	cout << "��ϣ������" << endl << endl;
	for (i = 1; i < 11; i++)
	{
		file = "data" + to_string(i) + ".txt";
		fstream fin(file);
		int a[n + 1];
		for (int j = 1; j < n + 1; j++)
		{//��ȡ���ݼ�
			fin >> a[j];
		}
		start = clock();
		int derta[3] = { 5, 3, 1 };
		ShellSort(a, derta, 3);
		stop = clock();
		duration = ((float)(stop - start) / CLK_TCK);	/* CLK_TCK�ǻ���û�뾭����tick */
		cout.fill('0');
		cout << "Time" << setw(2) << i << ": ";
		cout.fill(' ');
		cout << setw(5) << duration << endl << endl;
	}

	//ð������
	cout << "��ð������" << endl << endl;
	for (i = 1; i < 11; i++)
	{
		file = "data" + to_string(i) + ".txt";
		fstream fin(file);
		int a[n + 1];
		for (int j = 1; j < n + 1; j++)
		{//��ȡ���ݼ�
			fin >> a[j];
		}
		start = clock();
		BubbleSort(a);
		stop = clock();
		duration = ((float)(stop - start) / CLK_TCK);	/* CLK_TCK�ǻ���û�뾭����tick */
		cout.fill('0');
		cout << "Time" << setw(2) << i << ": ";
		cout.fill(' ');
		cout << setw(5) << duration << endl << endl;
	}

	//��������
	cout << "����������" << endl << endl;
	for (i = 1; i < 11; i++)
	{
		file = "data" + to_string(i) + ".txt";
		fstream fin(file);
		int a[n + 1];
		for (int j = 1; j < n + 1; j++)
		{//��ȡ���ݼ�
			fin >> a[j];
		}
		start = clock();
		QuickSort(a, 1, n);
		stop = clock();
		duration = ((float)(stop - start) / CLK_TCK);	/* CLK_TCK�ǻ���û�뾭����tick */
		cout.fill('0');
		cout << "Time" << setw(2) << i << ": ";
		cout.fill(' ');
		cout << setw(5) << duration << endl << endl;
	}

	//ѡ������
	cout << "��ѡ������" << endl << endl;
	for (i = 1; i < 11; i++)
	{
		file = "data" + to_string(i) + ".txt";
		fstream fin(file);
		int a[n + 1];
		for (int j = 1; j < n + 1; j++)
		{//��ȡ���ݼ�
			fin >> a[j];
		}
		start = clock();
		SelectSort(a);
		stop = clock();
		duration = ((float)(stop - start) / CLK_TCK);	/* CLK_TCK�ǻ���û�뾭����tick */
		cout.fill('0');
		cout << "Time" << setw(2) << i << ": ";
		cout.fill(' ');
		cout << setw(5) << duration << endl << endl;
	}

	//������
	cout << "��������" << endl << endl;
	for (i = 1; i < 11; i++)
	{
		file = "data" + to_string(i) + ".txt";
		fstream fin(file);
		int a[n + 1];
		for (int j = 1; j < n + 1; j++)
		{//��ȡ���ݼ�
			fin >> a[j];
		}
		start = clock();
		HeapSort(a);
		stop = clock();
		duration = ((float)(stop - start) / CLK_TCK);	/* CLK_TCK�ǻ���û�뾭����tick */
		cout.fill('0');
		cout << "Time" << setw(2) << i << ": ";
		cout.fill(' ');
		cout << setw(5) << duration << endl << endl;
	}

	//��������
	cout << "����������" << endl << endl;
	for (i = 1; i < 11; i++)
	{
		file = "data" + to_string(i) + ".txt";
		fstream fin(file);
		int a[n + 1];
		for (int j = 1; j < n + 1; j++)
		{//��ȡ���ݼ�
			fin >> a[j];
		}
		start = clock();
		RadixSort(a);
		stop = clock();
		duration = ((float)(stop - start) / CLK_TCK);	/* CLK_TCK�ǻ���û�뾭����tick */
		cout.fill('0');
		cout << "Time" << setw(2) << i << ": ";
		cout.fill(' ');
		cout << setw(5) << duration << endl << endl;
	}

	//�鲢����
	cout << "���鲢����" << endl << endl;
	for (i = 1; i < 11; i++)
	{
		file = "data" + to_string(i) + ".txt";
		fstream fin(file);
		int a[n + 1];
		for (int j = 1; j < n + 1; j++)
		{//��ȡ���ݼ�
			fin >> a[j];
		}
		start = clock();
		MergeSort(a);
		stop = clock();
		duration = ((float)(stop - start) / CLK_TCK);	/* CLK_TCK�ǻ���û�뾭����tick */
		cout.fill('0');
		cout << "Time" << setw(2) << i << ": ";
		cout.fill(' ');
		cout << setw(5) << duration << endl << endl;
	}
}
//�������ݼ�
void PutData()
{
	string str_temp;
	int i, j;
	int int_temp;//temp
	srand((unsigned)time(NULL));
	for (i = 1; i < 11; i++)
	{
		str_temp = "data" + to_string(i) + ".txt";
		fstream f(str_temp, fstream::out);
		for (j = 1; j < 20001; j++)
		{
			int_temp = rand() % 20000;
			f << int_temp << endl;
		}
		f.close();
	}
}
//����������
void InsertSort(int a[])
{
	int i, j;
	int temp;
	for (i = 2; i < n + 1; i++)
	{//core
		temp = a[i];
		j = i - 1;
		while (j >= 1 && temp < a[j])
		{
			a[j + 1] = a[j];
			j--;
		}
		a[j + 1] = temp;
	}
}
void ShellSort(int a[], int derta[], int t)
{//derta[]Ϊ�������飬tΪ����Ԫ�ظ���
	int i, j, k;
	int temp;
	for (k = 0; k < t; k++)
	{//������������
		int d = derta[k];
		for (i = 1 + d; i < n + 1; i++)
		{
			if (a[i] < a[i - d])
			{
				temp = a[i];
				for (j = i; j > d; j -= d)
				{
					if (temp < a[j - d])
						a[j] = a[j - d];
					else
						break;
				}
				a[j] = temp;
			}
		}
	}
}
//����������
void BubbleSort(int a[])
{
	int i, j;
	int temp;
	for (i = n; i >= 2; i--)
	{
		for (j = 2; j <= i; j++)
		{
			if (a[j - 1] > a[j])
			{
				temp = a[j - 1];
				a[j - 1] = a[j];
				a[j] = temp;
			}
		}
	}
}
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
//ѡ��������
void SelectSort(int a[])
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
void HeapSort(int a[])
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
//�鲢����
void Merge(int a[], int low, int mid, int high)
{
	int* b = (int*)malloc(sizeof(int) * (high - low + 1));
	int i = low;
	int j = mid + 1;
	int k = 0;
	while (i <= mid && j <= high)
	{
		if (a[i] <= a[i])
		{
			b[k++] = a[i++];
		}
		else
		{
			b[k++] = a[j++];
		}
	}
	while (i <= mid)
	{
		b[k++] = a[i++];
	}
	while (j <= high)
	{
		b[k++] = a[j++];
	}
	for (k = 0, i = low; i <= high; k++, i++)
	{
		a[i] = b[k];
	}
}
void MergeSort(int a[])
{
	int len;
	for (len = 1; len < n + 1; len *= 2)
	{
		int i = 1;
		while (i + 2 * len < n + 1)
		{//�鲢��Ϊlen������������
			Merge(a, i, i + len - 1, i + 2 * len - 1);
			i = i + 2 * len;
		}
		if (i + len <= n)
		{
			Merge(a, i, i + len - 1, n);
		}
	}
}
//��������
void RadixSort(int a[])
{
	queue<int> Q[10];
	int radix = 1;
	int i, j, k;
	int m;
	for (k = 1; k <= 5; k++)
	{
		radix *= 10;
		for (i = 1; i < n + 1; i++)
		{
			m = (a[i] % radix) / (radix / 10);
			Q[m].push(a[i]);
		}
		for (i = 1, m = 0; m < 10; m++)
		{
			while (!Q[m].empty())
			{
				a[i] = Q[m].front();
				Q[m].pop();
				i++;
			}
		}
	}
}
