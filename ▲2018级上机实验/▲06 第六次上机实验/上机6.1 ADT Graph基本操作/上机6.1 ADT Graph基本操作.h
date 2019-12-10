#pragma once
/*	Compiler: Visual Studio 2019
**	UpdateTime: 2019/11/14
**	ID: 161840225   */
#include <climits>
#include <queue>
#include <iostream>

typedef char ElemType;
typedef int Status;
const int MAX_V = 20;
const int OK = 1;
const int ERROR = 0;
enum class GraphKind { undigraph, digraph };//无向图和有向图
typedef struct
{
	int no;	//顶点编号
	ElemType info;//顶点信息
}Vertex;//顶 点类型
typedef struct
{
	int n;//顶点的个数
	int e;//边的个数
	Vertex vexs[MAX_V];//存放顶点信息
	int arcs[MAX_V][MAX_V];//邻接矩阵
	GraphKind type;//图的类型
}MGraph;

Status CreateGraph(MGraph* G);
Status ClearGraph(MGraph* G);
Status LocateVex(MGraph* G, Vertex v);
ElemType GetVex(MGraph* G, Vertex v);
Status PutVex(MGraph* G, Vertex v, ElemType value);
ElemType FirstAdjVex(MGraph G, ElemType v);
ElemType NextAdjVex(MGraph G, ElemType v, ElemType w);
void InsertVex(MGraph* G, ElemType v);
void DeleteVex(MGraph* G, ElemType v);
void DFS(MGraph G, int i);
void DFSTraverse(MGraph G, int no);
void BFSTraverse(MGraph G);