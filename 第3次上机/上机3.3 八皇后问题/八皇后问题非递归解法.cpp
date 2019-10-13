/***************************************
 **   Filename： 八皇后问题非递归解法.cpp
 **
 **   Compiler:  Visual Studio 2019
 **
 **   StudentID: 1618*****
 **
 **   Name:      Steven
 **
 **   Attention: 核心代码是对孙涵老师伪代码实现
 **
 ***************************************/
#include<iostream>
#include<cmath>

using namespace std;

const int STACKINITSIZE = 256;
const int STACKINCREMENT = 128;
const int RET_OK = 1;
const int RET_CONFLICT = 0;
const int OK = 1;
const int ERROR = 0;
typedef int Status;
typedef struct
{	//棋盘上的坐标，当然也是每个皇后的坐标
	int row;
	int col;
}Point;
typedef Point ElemType;
typedef struct
{	//Info of Stack
	ElemType* pBase;
	ElemType* pTop;
	int stacklength;
	int stacksize;
}SeqStack;

//栈操作
Status InitStack(SeqStack* S)
{
	S->pBase = NULL;
	S->pBase = (ElemType*)malloc(STACKINITSIZE * sizeof(ElemType));
	if (NULL == S->pBase)
		exit(1);

	S->pTop = S->pBase;
	S->stacklength = 0;
	S->stacksize = STACKINITSIZE;

	return OK;
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
	return OK;
}
Status Push(SeqStack* S, ElemType e)
{
	if (S->stacklength >= S->stacksize)
	{
		S->pBase = (ElemType*)realloc(S->pBase, (S->stacksize + STACKINCREMENT) * sizeof(ElemType));
		if (NULL == S->pBase)
			return ERROR;
		S->stacksize += STACKINCREMENT;
	}
	*S->pTop = e;
	S->pTop++;
	S->stacklength++;
	return OK;
}
Status Pop(SeqStack* S, ElemType* e)
{
	if (S->pBase == S->pTop)
		return ERROR;
	*e = *(S->pTop - 1);
	S->pTop--;
	S->stacklength--;
	return OK;
}

//八皇后问题相关函数
Status JudgeQueenConfliction(Point newQueen, SeqStack StkQueen)
{	//判断新的皇后位置和已有皇后位置是否冲突，冲突返回RET_CONFLICT，不冲突返回RET_OK
	ElemType* pCurQueen = StkQueen.pBase;	//从栈底部开始遍历来检测是否和已经放置好的皇后冲突
	int x1 = newQueen.row;
	int y1 = newQueen.col;
	int tag = RET_OK;//标志位是否有冲突
	while (pCurQueen < StkQueen.pTop)
	{
		int x2 = pCurQueen->row;
		int y2 = pCurQueen->col;
		if (y1 == y2 || abs(y1 - y2) == x1 - x2)	//如果位于同一列或主副对角线则有冲突
		{
			tag = RET_CONFLICT;
			break;
		}
		pCurQueen++;//遍历
	}
	return tag;
}
Status OutputResult(SeqStack StkQueen, int N)
{
	Point* pCurQueen = StkQueen.pBase;
	for (pCurQueen; pCurQueen < StkQueen.pTop; pCurQueen++)
	{
		for (int j = 1; j < N + 1; j++)
		{
			if (pCurQueen->col != j)
				cout << " -";
			else
				cout << " Q";
		}
		cout << endl;
	}
	cout << endl;
	return OK;
}
Status PlaceQueen(int N)
{	//N皇后问题非递归实现
	SeqStack StkQueen;
	Point curQueen;	//对当前皇后进行一系列操作

	InitStack(&StkQueen);
	int resultCount = 0;	//N皇后问题解的数量

	//接下来正式开始放皇后的过程
	curQueen.row = 1;	//目前应该处理的（第一个皇后）的位置
	curQueen.col = 1;
	Push(&StkQueen, curQueen);

	curQueen.row = 2;	//第二个皇后的起始试探位置
	curQueen.col = 1;
	while (curQueen.row <= N && curQueen.col <= N)
	{
		Status ret;
		while (curQueen.col <= N)
		{	//在每行为自己寻找合适位置
			ret = JudgeQueenConfliction(curQueen, StkQueen);
			if (RET_OK == ret)
				break;	//找到了属于自己的位置
			curQueen.col = curQueen.col + 1;	//存在冲突继续找下一列
		}	//注意这里只是先寻找位置而没有进行压栈操作
		if (RET_OK == ret)	//找到了合适的位置没有和之前皇后发生冲突
		{
			Push(&StkQueen, curQueen);
			curQueen.row = curQueen.row + 1;
			curQueen.col = 1;	//准备执行下一次while循环来为下一行的皇后找属于自己的位置
			if (curQueen.row > N)	//已经是最后一个皇后了，证明已经摆好
			{
				resultCount++;	//解的个数加一
				cout << "Solution " << resultCount << ":" << endl;
				OutputResult(StkQueen, N);	//输出当前结果


				Pop(&StkQueen, &curQueen);	//这两行语句是要将当前皇后弹栈，然后看看本行是不是还有下一个合适的位置
				curQueen.col = curQueen.col + 1;
				while (curQueen.col > N && !StkQueen.stacklength == 0)	//不满足要求，继续回退
				{
					Pop(&StkQueen, &curQueen);
					curQueen.col = curQueen.col + 1;
				}
			}
		}
		else //这个皇后没有在本行找到属于自己的位置，也就是说需要回溯了
		{
			Pop(&StkQueen, &curQueen);	//这两行语句是要得到上一行的皇后然后向右移动她
			curQueen.col = curQueen.col + 1;	//这时候也已经准备下一次while循环为这个皇后找到下一个合适的位置
			while (curQueen.col > N && !StkQueen.stacklength == 0)	//但是这个皇后已经到了最后一列或者栈空了，不满足要求，所以继续回退
			{
				Pop(&StkQueen, &curQueen);
				curQueen.col = curQueen.col + 1;
			}
		}
	}
	cout << "Total number of Solutions： " << resultCount << endl;
	DestroyStack(&StkQueen);
	return OK;
}
int main()
{
	PlaceQueen(8);
	return 0;
}
