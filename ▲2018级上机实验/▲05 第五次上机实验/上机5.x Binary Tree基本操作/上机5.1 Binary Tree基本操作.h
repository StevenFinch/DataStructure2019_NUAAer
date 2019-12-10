/*	Compiler: Visual Studio 2019
**	UpdateTime: 2019/11/07
**	ID: 161840225   */
#pragma once
#include<iostream>
#include<fstream>
#include<iomanip>
#include<algorithm>
#include<stack>
#include<queue>
#include<cmath>
using std::ifstream;

const int MAXSIZE = 8;
typedef char ElemType;//默认二叉树元素为char
typedef struct BinNode
{
	ElemType data;
	struct BinNode* lchild;
	struct BinNode* rchild;
}BinNode, *BinTree;


void CreateBinTree(ifstream& fin, BinTree& T);

void ClearBinTree(BinTree& T);

bool BinTreeEmpty(BinTree T);

bool IsCompleteBinaryTree(BinTree T);

int BinTreeDepth(BinTree T);

int BinTreeWidth(BinTree T);

ElemType Root(BinTree T);

BinNode* LocateBinNode(BinTree T, ElemType e);

ElemType Parent(BinTree T, ElemType e);

ElemType LeftChild(BinTree T, ElemType e);

ElemType RightChild(BinTree T, ElemType e);

ElemType LeftSibling(BinTree T, ElemType e);

ElemType RightSibling(BinTree T, ElemType e);

void InsertBiTree(BinTree T, ElemType e, BinTree Ti, int LR);

void DeleteBiTree(BinTree T, ElemType e, int LR);

//遍历操作
void PreOrderTraverse_r(BinTree T);

void InOrderTraverse_r(BinTree T);

void PostOrderTraverse_r(BinTree T);

void PreOrderTraverse_nonr(BinTree T);

void InOrderTraverse_nonr(BinTree T);

void PostOrderTraverse_nonr(BinTree T);

void LevelOrderTraverse(BinTree T);
