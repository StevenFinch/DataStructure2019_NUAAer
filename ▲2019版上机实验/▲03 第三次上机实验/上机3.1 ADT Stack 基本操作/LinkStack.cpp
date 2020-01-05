/*	Compiler: Visual Studio 2019
**	UpdateTime: 2019/10/06
**	ID: 161840225   */
#include <iostream>

using namespace std;

typedef int ElemType;
typedef bool Status;
typedef struct LStackNode
{
	ElemType data;
	struct LStackNode* next;
}LStackNode, * LinkStack;
typedef struct LinkStackInfo
{
	LinkStack pBase;
	LinkStack pTop;
	int stacklength;
}LinkStackInfo;

//初始化、销毁、清空操作
Status InitStack(LinkStackInfo* S)
{
	S->pTop = NULL;
	S->pTop = (LStackNode*)malloc(sizeof(LStackNode));
	if (NULL == S->pTop)
		return false;
	S->pTop->data = -1;
	S->pTop->next = NULL; 
	S->pBase = S->pTop;
	S->stacklength = 0;
	return true;
}
Status DestroyStack(LinkStackInfo* S)
{
	LStackNode* p = NULL;
	while (S->pTop->next != NULL)
	{
		p = S->pTop->next;
		S->pTop->next = p->next;
		free(p);
	}
	free(S->pTop);
	S->pTop = NULL;
	S->pBase = NULL;
	S->stacklength = 0;
	return true;
}
Status ClearStack(LinkStackInfo* S)
{
	LStackNode* p = NULL;
	while (S->pTop->next != NULL)
	{
		p = S->pTop->next;
		S->pTop->next = p->next;
		free(p);
	}
	S->pTop = NULL;
	S->pBase = NULL;
	S->stacklength = 0;
	return true;
}
//访问型操作
Status StackEmpty(LinkStackInfo* S)
{
	return S->stacklength == 0 ? true : false;
}
Status StackTraverse(LinkStackInfo* S)
{
	if (!StackEmpty(S))
	{
		LStackNode* p = S->pTop->next;
		while (NULL != p)
		{
			cout << p->data << ' ';
			p = p->next;
		}
		cout << endl;
	}
	return true;
}
int StackLength(LinkStackInfo* S)
{
	if (S->pBase != NULL)
		return S->stacklength;
	return -1;
}
Status GetTop(LinkStackInfo* S, ElemType* e)
{
	if (S->pBase == S->pTop)
		return false;
	*e = S->pTop->next->data;
	return true;
}
/*
加工型操作
链栈在头结点处进行压栈和出栈操作 
*/ 
Status Push(LinkStackInfo* S, ElemType e)
{
	LStackNode* p = (LStackNode*)malloc(sizeof(LStackNode));
	if (NULL == p)
		return false;
	p->data = e;
	p->next = S->pTop->next;
	S->pTop->next = p;
	if (NULL == p->next)
	{
		S->pBase = p;
	}
	S->stacklength++;
	return true;
}
Status Pop(LinkStackInfo* S, ElemType* e)
{
	if (S->pBase == S->pTop)
		return false;
	*e = S->pTop->next->data;

	LStackNode* p = S->pTop->next;
	S->pTop->next = p->next;
	free(p);
	p = NULL;
	S->stacklength--;
	return true;
}
//测试函数，默认ElemType为int
int main()
{
	LinkStackInfo S;
	InitStack(&S);
	ElemType e;
	for (int i = 1; i < 11; i++)
	{
		Push(&S, i);
	}
	StackTraverse(&S);
	if (!StackEmpty(&S))
	{
		Pop(&S, &e);
		GetTop(&S, &e);
		cout << e << endl;
		cout << StackLength(&S) << endl;
		StackTraverse(&S);
		DestroyStack(&S);
	}

	system("pause");
	return 0;
}
