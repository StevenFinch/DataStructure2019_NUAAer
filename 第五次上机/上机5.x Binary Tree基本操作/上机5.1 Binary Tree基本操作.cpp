/***************************************
 **   Filename： 上机5.x Binary Tree基本操作.cpp
 **
 **   Compiler:  Visual Studio 2019
 **
 **   StudentID: 1618*****
 **
 **   Name:      Steven
 **
 ***************************************/
#include"上机5.1 Binary Tree基本操作.h"
using namespace std;
void CreateBinTree(ifstream& fin, BinTree& T)//一定是引用型指针或者指向指针的指针！
{//根据先序序列构建二叉树
	ElemType e;
	fin >> e;
	if ('#' == e)
	{//默认二叉树元素为char
		T = NULL;
	}
	else
	{
		T = (BinTree)malloc(sizeof(BinNode));
		if (!T)
			exit(OVERFLOW);
		T->data = e;
		CreateBinTree(fin, T->lchild);
		CreateBinTree(fin, T->rchild);
	}
}

void ClearBinTree(BinTree& T)
{
	if (T)
	{
		if (T->lchild)
			ClearBinTree(T->lchild);
		if (T->rchild)
			ClearBinTree(T->rchild);
		free(T);//释放内存
		T = NULL;//置空指针
	}
}

bool BinTreeEmpty(BinTree T)
{
	return T == NULL ? true : false;
}

bool IsCompleteBinaryTree(BinTree T)
{
	queue<BinNode*> Q;
	Q.push(T);
	BinNode* cur = Q.front();
	while (cur)
	{
		Q.push(cur->lchild);
		Q.push(cur->rchild);
		Q.pop();
		cur = Q.front();
	}
	while (!Q.empty())
	{
		if (Q.front())
			return false;
		Q.pop();
	}
	return true;
}

int BinTreeDepth(BinTree T)
{
	int LD, RD;
	if (NULL == T)
		return 0;
	else
	{
		LD = BinTreeDepth(T->lchild);
		RD = BinTreeDepth(T->rchild);
		return max(LD, RD) + 1;
	}
}

int BinTreeWidth(BinTree T)
{
	if (T)
	{
		queue<BinNode*> Q;
		Q.push(T);
		int maxWidth = 1;
		while (true)
		{
			int length = Q.size();//当前行的结点个数
			if (0 == length)//该行为空跳出循环
				break;
			while (length)
			{//依次遍历该行结点从而计算下一行结点个数
				length--;
				BinNode* p = Q.front();
				Q.pop();
				if (p->lchild)
					Q.push(p->lchild);
				if (p->rchild)
					Q.push(p->rchild);
			}//end while(length)
			maxWidth = max(maxWidth, (int)Q.size());//将上一行结点个数与当前行相比取较大
		}
		return maxWidth;
	}
	return 0;
}

ElemType Root(BinTree T)
{
	if (T)
		return T->data;
}

BinNode* LocateBinNode(BinTree T, ElemType e)
{//在二叉树中查找某一数据并返回该数据结点指针
	BinNode* p = NULL;
	if (T)
	{
		if (e == T->data)
		{
			p = T;
		}
		else
		{
			p = LocateBinNode(T->lchild, e);
			if (NULL == p)
			{//剪枝操作
				p = LocateBinNode(T->rchild, e);
			}
		}
	}//end if(T)
	return p;
}

ElemType Parent(BinTree T, ElemType e)
{
	ElemType p = '\0';
	if (NULL == T || e == T->data)
		p = '\0';
	else if ((T->lchild && e == T->lchild->data) || (T->rchild && e == T->rchild->data))
		p = T->data;
	else
	{
		p = Parent(T->lchild, e);
		if ('\0' == p)
			p = Parent(T->rchild, e);
	}
	return p;
}

ElemType LeftChild(BinTree T, ElemType e)
{
	BinNode* p = LocateBinNode(T, e);
	if (p)
	{
		if (p->lchild)
			return p->lchild->data;
		else
			return '#';
	}
}

ElemType RightChild(BinTree T, ElemType e)
{
	BinNode* p = LocateBinNode(T, e);
	if (p)
	{
		if (p->rchild)
			return p->rchild->data;
		else
			return '#';
	}
}

ElemType LeftSibling(BinTree T, ElemType e)
{
	ElemType p = '#';
	if (T && T->data != e)
	{
		if (e == T->data)
			return p;
		if (T->rchild && e == T->rchild->data)
		{
			if (T->lchild)
				p = T->lchild->data;
		}
		if (p == '#')
			p = LeftSibling(T->lchild, e);
		if (p == '#')
			p = LeftSibling(T->rchild, e);
	}
	return p;
}

ElemType RightSibling(BinTree T, ElemType e)
{
	ElemType p = '#';
	if (T && T->data != e)
	{
		if (e == T->data)
			return p;
		if (T->lchild && e == T->lchild->data)
		{
			if (T->rchild)
				p = T->rchild->data;
		}
		if (p == '#')
			p = RightSibling(T->lchild, e);
		if (p == '#')
			p = RightSibling(T->rchild, e);
	}
	return p;
}

void InsertBiTree(BinTree T, ElemType e, BinTree Ti, int LR)
{
	BinTree p = LocateBinNode(T, e);
	if (p)
	{
		LR ? (p->rchild = Ti) : (p->lchild = Ti);
	}
}

void DeleteBiTree(BinTree T, ElemType e, int LR)
{
	BinTree p = LocateBinNode(T, e);
	if (p)
	{
		LR ? ClearBinTree((p->rchild)) : ClearBinTree(p->lchild);
	}
}

//二叉树遍历（递归及非递归）
void PreOrderTraverse_r(BinTree T)
{
	if (T)
	{
		cout << setw(3) << T->data;
		PreOrderTraverse_r(T->lchild);
		PreOrderTraverse_r(T->rchild);
	}
}

void InOrderTraverse_r(BinTree T)
{
	if (T)
	{
		InOrderTraverse_r(T->lchild);
		cout << setw(3) << T->data;
		InOrderTraverse_r(T->rchild);
	}
}

void PostOrderTraverse_r(BinTree T)
{
	if (T)
	{
		PostOrderTraverse_r(T->lchild);
		PostOrderTraverse_r(T->rchild);
		cout << setw(3) << T->data;
	}
}

void PreOrderTraverse_nonr(BinTree T)
{
	if (T)
	{//树非空
		stack<BinTree> S;
		BinTree t = T;
		S.push(t);//根节点先入栈
		while (!S.empty())
		{
			t = S.top();
			cout << setw(3) << t->data;
			S.pop();
			if (t->rchild)
				S.push(t->rchild);//右孩子先入栈，保证左孩子先出栈
			if (t->lchild)
				S.push(t->lchild);
		}
	}
}

void InOrderTraverse_nonr(BinTree T)
{
	if (T)
	{//树非空
		stack<BinTree> S;
		BinTree t = T;
		while (!S.empty() || t != NULL)
		{//栈空不一定循环中止，可能右子树尚未遍历
			while (t)
			{
				S.push(t);
				t = t->lchild;
			}
			t = S.top();
			S.pop();
			cout << setw(3) << t->data;
			t = t->rchild;
		}
	}
}

void PostOrderTraverse_nonr(BinTree T)
{//两个栈实现，第一个栈实现逆后序遍历，第二个栈实现逆序输出
	if (T)
	{
		stack<BinTree> S1;
		stack<BinTree> S2;
		BinTree t = T;
		S1.push(t);
		while (!S1.empty())
		{//逆后序遍历
			t = S1.top();
			S1.pop();
			S2.push(t);
			if (t->lchild)
				S1.push(t->lchild);
			if (t->rchild)
				S1.push(t->rchild);
		}
		while (!S2.empty())
		{//实现逆序输出
			t = S2.top();
			S2.pop();
			cout << setw(3) << t->data;
		}
	}
}

void LevelOrderTraverse(BinTree T)
{//循环队列实现
	BinTree Q[MAXSIZE];//队长为16的队列
	int front, rear;
	front = rear = 0;//空队列
	BinTree t = T;
	if (T)
	{
		rear = (rear + 1) % MAXSIZE;
		Q[rear] = t;//根节点入队
		while (rear != front)
		{
			front = (front + 1) % MAXSIZE;
			t = Q[front];//队首结点出队
			cout << setw(3) << t->data;
			if (t->lchild != NULL)
			{//左子树非空才入队
				rear = (rear + 1) % MAXSIZE;
				Q[rear] = t->lchild;
			}
			if (t->rchild != NULL)
			{//右子树非空入队
				rear = (rear + 1) % MAXSIZE;
				Q[rear] = t->rchild;
			}
		}
	}
}

