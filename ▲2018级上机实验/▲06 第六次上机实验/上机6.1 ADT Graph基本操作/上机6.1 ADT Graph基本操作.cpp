/*	Compiler: Visual Studio 2019
**	UpdateTime: 2019/11/14
**	ID: 161840225   */
#include "上机6.1 ADT Graph基本操作.h"
using namespace std;

bool Visited[MAX_V];//DFS遍历标记
Status CreateGraph(MGraph* G)
{
	G->type = GraphKind::digraph;//有向图
	cin >> G->n >> G->e;//输入顶点和边的个数；
	int i, j, k, w;
	ElemType v0, v1;
	for (i = 0; i < G->n; i++)
	{//输入顶点信息
		cin >> G->vexs[i].info;
		G->vexs[i].no = i;
	}
	for (i = 0; i < G->n; i++)
	{
		for (j = 0; j < G->n; j++)
		{
			G->arcs[i][j] = INT_MAX;//邻接矩阵初始化
		}
	}
	for (int k = 0; k < G->e; k++)
	{
		cin >> v0;//输入弧尾
		cin >> v1;//输入弧头
		cin >> w;//输入权值
		for (i = 0; i < G->n; i++)
		{//找到对应编号
			if (i == G->vexs[i].info)
				break;
		}
		for (j = 0; j < G->n; j++)
		{//找到对应编号
			if (j == G->vexs[j].info)
				break;
		}
		G->arcs[i][j] = w;//利用编号对邻接矩阵赋值
	}
	return OK;
}

Status ClearGraph(MGraph* G)
{
	int i, j;
	for (i = 0; i < G->n; i++)
	{
		G->vexs[i].info = '#';
		G->vexs[i].no = -1;
	}
	for (i = 0; i < G->n; i++)
	{
		for (j = 0; j < G->n; j++)
		{
			G->arcs[i][j] = INT_MAX;
		}
	}
	G->n = 0;
	G->e = 0;

	return OK;
}

int LocateVex(MGraph* G, Vertex v)
{
	for (int i = 0; i < G->n; i++)
	{
		if (G->vexs[i].info == v.info)
			return i;
	}
}

ElemType GetVex(MGraph* G, Vertex v)
{
	return v.info;
}

Status PutVex(MGraph* G, Vertex v, ElemType value)
{
	return v.info = value;
}

ElemType FirstAdjVex(MGraph G, ElemType v)
{
	int i, j, k;
	for (i = 0; i < G.n; i++)
	{
		if (G.vexs[i].info == v)
			break;
	}
	for (j = 0; j < G.n; j++)
	{
		if (G.arcs[i][j] < INT_MAX)
			break;
	}
	if (j < G.n)
		return G.vexs[j].info;
	else
		return '#';
}

ElemType NextAdjVex(MGraph G, ElemType v, ElemType w)
{
	int i, j, k, m;
	for (i = 0; i < G.n; i++)
	{
		if (G.vexs[i].info == v)
			break;
	}
	for (j = 0; j < G.n; j++)
	{
		if (G.vexs[j].info == w)
			break;
	}
	for (k = 0; k < G.n; k++)
	{
		if (G.arcs[i][k] <INT_MAX && k > j)
			break;
	}  //下一个邻接点 
	if (k < G.n)
		return G.vexs[k].info;
	else
		return '#';
}

void InsertVex(MGraph* G, ElemType v)
{
	int i, j;
	Vertex t = { v, G->n };//初始化新顶点
	G->vexs[G->n].info = v;//加入顶点列表中
	for (i = 0, j = 0; i < G->n + 1; i++, j++)
	{
		G->arcs[G->n][i] = INT_MAX;
		G->arcs[j][G->n] = INT_MAX;
	}
	G->n++;
}

void DeleteVex(MGraph* G, ElemType v)
{//ClearVex
	int i, j, k;
	for (i = 0; i < G->n; i++)
	{
		if (G->vexs[i].info == v)
		{
			G->vexs[i].info = '#';
			break;
		}
	}
	for (j = 0, k = 0; j < G->n; j++, k++)
	{
		G->arcs[i][j] = INT_MAX;
		G->arcs[k][i] = INT_MAX;
	}
}

void DFS(MGraph G, int i)
{
	int k;
	ElemType w, v;
	Visited[i] = 1;
	cout << G.vexs[i].info << " ";
	for (w = FirstAdjVex(G, G.vexs[i].info); w != '#'; w = NextAdjVex(G, G.vexs[i].info, w))
	{
		for (k = 0; k < G.n; k++)
		{
			if (G.vexs[k].info == w)
				break;
		}
		if (Visited[k] == 0)
			DFS(G, k);
	}
}

void DFSTraverse(MGraph G, int no)
{
	int i;
	for (i = 0; i < G.n; i++)
	{
		Visited[i] = 0;
	}
	for (i = 0; i < G.n; i++)
	{
		if (Visited[i] == 0)
			DFS(G, i);
	}
}

void BFSTraverse(MGraph G)
{
	int i, k;
	for (i = 0; i < G.n; i++)
		Visited[i] = 0;
	ElemType u, w;
	queue<ElemType> Q;
	for (i = 0; i < G.n; i++)
	{
		if (Visited[i] == 0)
		{
			Visited[i] = 1;
			cout << G.vexs[i].info << " ";
			Q.push(G.vexs[i].info);
			while (!Q.empty())·
			{
				u = Q.front();
				Q.pop();
				for (w = FirstAdjVex(G, u); w != '#'; w = NextAdjVex(G, u, w))
				{//下一层已经遍历完
					for (k = 0; k < G.n; k++)
					{
						if (G.vexs[k].info == w)
							break;
					}
					if (Visited[k] == 0)
					{
						Visited[k] = 1;
						cout << G.vexs[k].info << " ";
						Q.push(G.vexs[k].info);
					}
				}
			}
		}
	}
}