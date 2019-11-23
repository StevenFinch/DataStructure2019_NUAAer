/***************************************
 **   Filename:  �ϻ�7.4 ������.cpp
 **
 **   Compiler:  Visual Studio 2019
 **
 **   StudentID: 1618*****
 **
 **   Name:      Steven
 **
 ***************************************/
#include <iostream>
#include <algorithm>
using namespace std;

const int MAXSIZE = 8;
typedef struct
{
	int a, b;//�����˵�
	int w;//Ȩ��
}Road;//ˮ��

int n, m;//��������ˮ����
Road road[MAXSIZE];
int DisjointSet[MAXSIZE];//���鼯
int GetRoot(int a)
{//�ڲ��鼯�в��Ҹ��ڵ�
	while (a != DisjointSet[a])
		a = DisjointSet[a];
	return a;
}
void Sort()
{//��ˮ����Ȩֵ��С��������
	for (int i = 0; i < m - 1; i++)
	{
		for (int j = i + 1; j < m; j++)
		{
			if (road[i].w > road[j].w)
				swap(road[i], road[j]);
		}
	}
}
void Kruskal(Road Road[])
{//Kruskal�㷨
	int t = 1;//counter
	for (int i = 0; i < n; i++)//���鼯��ʼ��
		DisjointSet[i] = i;
	Sort();//��ˮ����Ȩֵ��С��������
	for (int j = 0; j < m; j++)
	{
		int a = GetRoot(road[j].a);
		int b = GetRoot(road[j].b);
		if (a != b)
		{
			DisjointSet[a] = b;
			cout << "No." << t++ << ": ";
			cout << '(' << road[j].a << ',' << road[j].b << ')' << endl;
		}
	}
}
int main()
{
	cin >> n >> m;//��������ˮ����
	for (int i = 0; i < m;i++)
	{
		cin >> road[i].a >> road[i].b >> road[i].w;
	}
	Kruskal(road);
	return 0;
}