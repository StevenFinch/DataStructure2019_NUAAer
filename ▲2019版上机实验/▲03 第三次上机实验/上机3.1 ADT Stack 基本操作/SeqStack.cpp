/*	Compiler: Visual Studio 2019
**	UpdateTime: 2019/10/06
**	ID: 161840225   */
#include <iostream>

using namespace std;

const int STACKINITSIZE = 256;
const int STACKINCREMENT = 128;
typedef bool Status;
typedef int ElemType;
typedef struct SeqStack
{
	ElemType* pBase;
	ElemType* pTop;
	int stacklength;//S.pTop - S.pBase
	int stacksize;
}SeqStack;

//初始化、销毁、清空操作
Status InitStack(SeqStack* S)
{
	S->pBase = NULL;
	S->pBase = (ElemType*)malloc(STACKINITSIZE * sizeof(ElemType));
	if (NULL == S->pBase)
		return false;
	S->pTop = S->pBase;
	S->stacklength = 0;
	S->stacksize = STACKINITSIZE;
	return true;
}
Status DestroyStack(SeqStack* S)
{
	if (S->pBase != NULL)
	{
		free(S->pBase);
		S->pBase = NULL;
	}
	S->pTop = NULL;
	S->stacklength = 0;
	S->stacksize = 0;
	return true;
}
Status ClearStack(SeqStack S)
{
	S.pTop = S.pBase;
	S.stacklength = 0;
	return true;
}
//访问型操作
Status StackEmpty(SeqStack* S)
{
	if (S->pBase != NULL)
		return S->pBase == S->pTop ? true : false;
	return false;
}
Status StackTraverse(SeqStack* S)
{
	if (!StackEmpty(S))
	{
		for (int i = 0; i < S->stacklength; i++)
		{
			cout << S->pBase[i] << ' ';
		}
	}
	return true;
}
int StackLength(SeqStack* S)
{
	if(S->pBase != NULL)
		return S->stacklength;
	return -1;
}
Status GetTop(SeqStack* S, ElemType* e)
{
	if (S->pBase == S->pTop)
		return false;
	*e = *(S->pTop - 1);
	return true;
}
//加工型操作
Status Push(SeqStack* S, ElemType e)
{
	if (S->stacklength >= S->stacksize)
	{
		S->pBase = (ElemType*)realloc(S->pBase, (S->stacksize + STACKINCREMENT) * sizeof(ElemType));
		if (NULL == S->pBase)
			return false;
		S->stacksize += STACKINCREMENT;
	}
	*S->pTop = e;
	S->pTop++;
	S->stacklength++;
	return true;
}
Status Pop(SeqStack* S, ElemType* e)
{
	if (S->pBase == S->pTop)
		return false;
	*e = *(S->pTop - 1);
	S->pTop--;
	S->stacklength--;
	return true;
}
//测试函数，默认ElemType为int
int main()
{
	SeqStack S;
	InitStack(&S);
	ElemType e;
	for (int i = 1; i < 11; i++)
	{
		Push(&S, i);
	}
	if (!StackEmpty(&S))
	{
		Pop(&S, &e);
		Pop(&S, &e);
		GetTop(&S, &e);
		StackTraverse(&S);
		StackLength(&S);
		DestroyStack(&S);
	}
	system("pause");
	return 0;
}
