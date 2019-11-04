/***************************************
 **   Filename�� �ϻ�5.x Binary Tree��������.cpp
 **
 **   Compiler:  Visual Studio 2019
 **
 **   StudentID: 1618*****
 **
 **   Name:      Steven
 **
 ***************************************/
#include"�ϻ�5.1 Binary Tree��������.h"
using namespace std;
void CreateBinTree(ifstream& fin, BinTree& T)//һ����������ָ�����ָ��ָ���ָ�룡
{//�����������й���������
	ElemType e;
	fin >> e;
	if ('#' == e)
	{//Ĭ�϶�����Ԫ��Ϊchar
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
		free(T);//�ͷ��ڴ�
		T = NULL;//�ÿ�ָ��
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
			int length = Q.size();//��ǰ�еĽ�����
			if (0 == length)//����Ϊ������ѭ��
				break;
			while (length)
			{//���α������н��Ӷ�������һ�н�����
				length--;
				BinNode* p = Q.front();
				Q.pop();
				if (p->lchild)
					Q.push(p->lchild);
				if (p->rchild)
					Q.push(p->rchild);
			}//end while(length)
			maxWidth = max(maxWidth, (int)Q.size());//����һ�н������뵱ǰ�����ȡ�ϴ�
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
{//�ڶ������в���ĳһ���ݲ����ظ����ݽ��ָ��
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
			{//��֦����
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

//�������������ݹ鼰�ǵݹ飩
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
	{//���ǿ�
		stack<BinTree> S;
		BinTree t = T;
		S.push(t);//���ڵ�����ջ
		while (!S.empty())
		{
			t = S.top();
			cout << setw(3) << t->data;
			S.pop();
			if (t->rchild)
				S.push(t->rchild);//�Һ�������ջ����֤�����ȳ�ջ
			if (t->lchild)
				S.push(t->lchild);
		}
	}
}

void InOrderTraverse_nonr(BinTree T)
{
	if (T)
	{//���ǿ�
		stack<BinTree> S;
		BinTree t = T;
		while (!S.empty() || t != NULL)
		{//ջ�ղ�һ��ѭ����ֹ��������������δ����
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
{//����ջʵ�֣���һ��ջʵ�������������ڶ���ջʵ���������
	if (T)
	{
		stack<BinTree> S1;
		stack<BinTree> S2;
		BinTree t = T;
		S1.push(t);
		while (!S1.empty())
		{//��������
			t = S1.top();
			S1.pop();
			S2.push(t);
			if (t->lchild)
				S1.push(t->lchild);
			if (t->rchild)
				S1.push(t->rchild);
		}
		while (!S2.empty())
		{//ʵ���������
			t = S2.top();
			S2.pop();
			cout << setw(3) << t->data;
		}
	}
}

void LevelOrderTraverse(BinTree T)
{//ѭ������ʵ��
	BinTree Q[MAXSIZE];//�ӳ�Ϊ16�Ķ���
	int front, rear;
	front = rear = 0;//�ն���
	BinTree t = T;
	if (T)
	{
		rear = (rear + 1) % MAXSIZE;
		Q[rear] = t;//���ڵ����
		while (rear != front)
		{
			front = (front + 1) % MAXSIZE;
			t = Q[front];//���׽�����
			cout << setw(3) << t->data;
			if (t->lchild != NULL)
			{//�������ǿղ����
				rear = (rear + 1) % MAXSIZE;
				Q[rear] = t->lchild;
			}
			if (t->rchild != NULL)
			{//�������ǿ����
				rear = (rear + 1) % MAXSIZE;
				Q[rear] = t->rchild;
			}
		}
	}
}

