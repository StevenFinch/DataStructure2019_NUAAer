/*	Compiler: Visual Studio 2019
**	UpdateTime: 2019/10/21
**	ID: 161840225   */
#include <iostream>

using namespace std;

const int MAXSIZE = 256;
const int OK = 1;
const int ERROR = 0;
typedef int Status;
typedef struct
{
	int data[MAXSIZE];//默认数据类型为int
	int top[2];//两个栈顶指针
	int base[2];//两个base指针
}DqStack;

Status InitStack(DqStack* S)
{
	for (int i = 0; i < MAXSIZE; i++)
	{
		S->data[i] = -1;
	}

	S->base[0] = 0;
	S->base[1] = MAXSIZE - 1;

	S->top[0] = S->base[0];//left satck
	S->top[1] = S->base[1];//right stack

	return OK;
}
Status Push(DqStack* S, int e, int stacknum)
{
	if (S->top[0] == S->top[1])
		return ERROR;//stack is full, another larger stack is needed

	switch (stacknum)
	{
	case(0):
		S->data[S->top[0]] = e;
		S->top[0]++;
		break;//break
	case(1):
		S->data[S->top[1]] = e;
		S->top[1]--;
		break;
	default:
		break;
	}
	return OK;
}
Status Pop(DqStack* S, int* e, int stacknum)
{
	if (S->top[stacknum] == S->base[stacknum])
		return ERROR;//stack is empty

	switch (stacknum)
	{
	case(0):
		*e = S->data[S->top[0] - 1];
		S->top[0]--;
		break;
	case(1):
		*e = S->data[S->top[1] + 1];
		S->top[0]++;
		break;
	default:
		break;
	}
	return OK;
}
Status TraverseStack(DqStack* S)
{
	for (int i = S->base[0]; i < S->top[0]; i++)
	{
		cout << S->data[i] << ' ';
	}
	for (int j = S->top[1] + 1; j < S->base[1] + 1; j++)
	{
		cout << S->data[j] << ' ';
	}
	return OK;
}
int main()
{
	DqStack S;
	InitStack(&S);
	for (int i = 0; i < 10; i++)
	{
		Push(&S, i, i % 2);
	}
	TraverseStack(&S);
	//DestroyStack(&S);
	return 0;
}