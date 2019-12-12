#include "threaddialog.h"
#include "ui_threaddialog.h"
#include<iostream>
#include<fstream>
#include<string>
#include<ctime>
#include<iomanip>
#include<queue>
#include<QString>
using namespace std;
const int n = 20000;//每个数据集20000个元素
const int m = 10;//10个数据集
//生成数据集
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
//插入类排序
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
{//derta[]为增量数组，t为其中元素个数
    int i, j, k;
    int temp;
    for (k = 0; k < t; k++)
    {//遍历增量数组
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
//交换类排序
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
//选择类排序
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
void HeapSort(int a[])
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
//归并排序
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
        {//归并长为len的两个子序列
            Merge(a, i, i + len - 1, i + 2 * len - 1);
            i = i + 2 * len;
        }
        if (i + len <= n)
        {
            Merge(a, i, i + len - 1, n);
        }
    }
}
//基数排序
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

ThreadDialog::ThreadDialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::ThreadDialog)
{
    ui->setupUi(this);
    PutData();//建立数据集
}

ThreadDialog::~ThreadDialog()
{
    delete ui;
}


void ThreadDialog::on_pushButton_clicked()
{
    int i;
    clock_t start, stop;
    float duration;
    string file;
    float sum = 0.0;
    for (i = 1; i < 11; i++)
    {
        file = "data" + to_string(i) + ".txt";
        fstream fin(file);
        int a[n + 1];
        for (int j = 1; j < n + 1; j++)
        {//读取数据集
            fin >> a[j];
        }
        start = clock();
        InsertSort(a);
        stop = clock();
        duration = ((float)(stop - start) / CLK_TCK);
        sum += duration;
    }
    float average = sum / 10;
    QString str = QString::number(average);
    ui->label->setText(str);
}

void ThreadDialog::on_pushButton_2_clicked()
{
    int i;
    clock_t start, stop;
    float duration;
    string file;
    float sum = 0.0;
    for (i = 1; i < 11; i++)
    {
        file = "data" + to_string(i) + ".txt";
        fstream fin(file);
        int a[n + 1];
        for (int j = 1; j < n + 1; j++)
        {//读取数据集
            fin >> a[j];
        }
        start = clock();
        int derta[3] = { 5, 3, 1 };
        ShellSort(a, derta, 3);
        stop = clock();
        duration = ((float)(stop - start) / CLK_TCK);	/* CLK_TCK是机器没秒经过的tick */
        sum += duration;
    }
    float average = sum / 10;
    QString str = QString::number(average);
    ui->label_2->setText(str);
}

void ThreadDialog::on_pushButton_3_clicked()
{
    int i;
    clock_t start, stop;
    float duration;
    string file;
    float sum = 0.0;
    for (i = 1; i < 11; i++)
    {
        file = "data" + to_string(i) + ".txt";
        fstream fin(file);
        int a[n + 1];
        for (int j = 1; j < n + 1; j++)
        {//读取数据集
            fin >> a[j];
        }
        start = clock();
        BubbleSort(a);
        stop = clock();
        duration = ((float)(stop - start) / CLK_TCK);
        sum += duration;
    }
    float average = sum / 10;
    QString str = QString::number(average);
    ui->label_3->setText(str);
}

void ThreadDialog::on_pushButton_4_clicked()
{
    int i;
    clock_t start, stop;
    float duration;
    string file;
    float sum = 0.0;
    for (i = 1; i < 11; i++)
    {
        file = "data" + to_string(i) + ".txt";
        fstream fin(file);
        int a[n + 1];
        for (int j = 1; j < n + 1; j++)
        {//读取数据集
            fin >> a[j];
        }
        start = clock();
        QuickSort(a, 1, n);
        stop = clock();
        duration = ((float)(stop - start) / CLK_TCK);
        sum += duration;
    }
    float average = sum / 10;
    QString str = QString::number(average);
    ui->label_4->setText(str);
}

void ThreadDialog::on_pushButton_7_clicked()
{
    int i;
    clock_t start, stop;
    float duration;
    string file;
    float sum = 0.0;
    for (i = 1; i < 11; i++)
    {
        file = "data" + to_string(i) + ".txt";
        fstream fin(file);
        int a[n + 1];
        for (int j = 1; j < n + 1; j++)
        {//读取数据集
            fin >> a[j];
        }
        start = clock();
        SelectSort(a);
        stop = clock();
        duration = ((float)(stop - start) / CLK_TCK);
        sum += duration;
    }
    float average = sum / 10;
    QString str = QString::number(average);
    ui->label_7->setText(str);
}

void ThreadDialog::on_pushButton_6_clicked()
{
    int i;
    clock_t start, stop;
    float duration;
    string file;
    float sum = 0.0;
    for (i = 1; i < 11; i++)
    {
        file = "data" + to_string(i) + ".txt";
        fstream fin(file);
        int a[n + 1];
        for (int j = 1; j < n + 1; j++)
        {//读取数据集
            fin >> a[j];
        }
        start = clock();
        HeapSort(a);
        stop = clock();
        duration = ((float)(stop - start) / CLK_TCK);
        sum += duration;
    }
    float average = sum / 10;
    QString str = QString::number(average);
    ui->label_8->setText(str);
}

void ThreadDialog::on_pushButton_5_clicked()
{
    int i;
    clock_t start, stop;
    float duration;
    string file;
    float sum = 0.0;
    for (i = 1; i < 11; i++)
    {
        file = "data" + to_string(i) + ".txt";
        fstream fin(file);
        int a[n + 1];
        for (int j = 1; j < n + 1; j++)
        {//读取数据集
            fin >> a[j];
        }
        start = clock();
        RadixSort(a);
        stop = clock();
        duration = ((float)(stop - start) / CLK_TCK);
        sum += duration;
    }
    float average = sum / 10;
    QString str = QString::number(average);
    ui->label_5->setText(str);
}

void ThreadDialog::on_pushButton_9_clicked()
{
    int i;
    clock_t start, stop;
    float duration;
    string file;
    float sum = 0.0;
    for (i = 1; i < 11; i++)
    {
        file = "data" + to_string(i) + ".txt";
        fstream fin(file);
        int a[n + 1];
        for (int j = 1; j < n + 1; j++)
        {//读取数据集
            fin >> a[j];
        }
        start = clock();
        MergeSort(a);
        stop = clock();
        duration = ((float)(stop - start) / CLK_TCK);
        sum += duration;
    }
    float average = sum / 10;
    QString str = QString::number(average);
    ui->label_6->setText(str);
}
