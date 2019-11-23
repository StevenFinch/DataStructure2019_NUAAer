/***************************************
 **   Filename:  上机7.4 麦田灌溉.cpp
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
	int a, b;//两个端点
	int w;//权重
}Road;//水渠

int n, m;//麦田数、水渠数
Road road[MAXSIZE];
int DisjointSet[MAXSIZE];//并查集
int GetRoot(int a)
{//在并查集中查找根节点
	while (a != DisjointSet[a])
		a = DisjointSet[a];
	return a;
}
void Sort()
{//对水渠按权值从小到大排序
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
{//Kruskal算法
	int t = 1;//counter
	for (int i = 0; i < n; i++)//并查集初始化
		DisjointSet[i] = i;
	Sort();//对水渠按权值从小到大排序
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
	cin >> n >> m;//麦田数和水渠数
	for (int i = 0; i < m;i++)
	{
		cin >> road[i].a >> road[i].b >> road[i].w;
	}
	Kruskal(road);
	return 0;
}