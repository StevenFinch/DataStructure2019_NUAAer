/***************************************
 **   Filename�� �˻ʺ�����ǵݹ�ⷨ.cpp
 **
 **   Compiler:  Visual Studio 2019
 **
 **   StudentID: 1618*****
 **
 **   Name:      Steven
 **
 **	  Attention: ���Ĵ����Ƕ��ﺭ��ʦα����ʵ��
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
{	//�����ϵ����꣬��ȻҲ��ÿ���ʺ������
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

//ջ����
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

//�˻ʺ�������غ���
Status JudgeQueenConfliction(Point newQueen, SeqStack StkQueen)
{	//�ж��µĻʺ�λ�ú����лʺ�λ���Ƿ��ͻ����ͻ����RET_CONFLICT������ͻ����RET_OK
	ElemType* pCurQueen = StkQueen.pBase;	//��ջ�ײ���ʼ����������Ƿ���Ѿ����úõĻʺ��ͻ
	int x1 = newQueen.row;
	int y1 = newQueen.col;
	int tag = RET_OK;//��־λ�Ƿ��г�ͻ
	while (pCurQueen < StkQueen.pTop)
	{
		int x2 = pCurQueen->row;
		int y2 = pCurQueen->col;
		if (y1 == y2 || abs(y1 - y2) == x1 - x2)	//���λ��ͬһ�л������Խ������г�ͻ
		{
			tag = RET_CONFLICT;
			break;
		}
		pCurQueen++;//����
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
{	//N�ʺ�����ǵݹ�ʵ��
	SeqStack StkQueen;
	Point curQueen;	//�Ե�ǰ�ʺ����һϵ�в���

	InitStack(&StkQueen);
	int resultCount = 0;	//N�ʺ�����������

	//��������ʽ��ʼ�Żʺ�Ĺ���
	curQueen.row = 1;	//ĿǰӦ�ô���ģ���һ���ʺ󣩵�λ��
	curQueen.col = 1;
	Push(&StkQueen, curQueen);

	curQueen.row = 2;	//�ڶ����ʺ����ʼ��̽λ��
	curQueen.col = 1;
	while (curQueen.row <= N && curQueen.col <= N)
	{
		Status ret;
		while (curQueen.col <= N)
		{	//��ÿ��Ϊ�Լ�Ѱ�Һ���λ��
			ret = JudgeQueenConfliction(curQueen, StkQueen);
			if (RET_OK == ret)
				break;	//�ҵ��������Լ���λ��
			curQueen.col = curQueen.col + 1;	//���ڳ�ͻ��������һ��
		}	//ע������ֻ����Ѱ��λ�ö�û�н���ѹջ����
		if (RET_OK == ret)	//�ҵ��˺��ʵ�λ��û�к�֮ǰ�ʺ�����ͻ
		{
			Push(&StkQueen, curQueen);
			curQueen.row = curQueen.row + 1;
			curQueen.col = 1;	//׼��ִ����һ��whileѭ����Ϊ��һ�еĻʺ��������Լ���λ��
			if (curQueen.row > N)	//�Ѿ������һ���ʺ��ˣ�֤���Ѿ��ں�
			{
				resultCount++;	//��ĸ�����һ
				cout << "Solution " << resultCount << ":" << endl;
				OutputResult(StkQueen, N);	//�����ǰ���


				Pop(&StkQueen, &curQueen);	//�����������Ҫ����ǰ�ʺ�ջ��Ȼ�󿴿������ǲ��ǻ�����һ�����ʵ�λ��
				curQueen.col = curQueen.col + 1;
				while (curQueen.col > N && !StkQueen.stacklength == 0)	//������Ҫ�󣬼�������
				{
					Pop(&StkQueen, &curQueen);
					curQueen.col = curQueen.col + 1;
				}
			}
		}
		else //����ʺ�û���ڱ����ҵ������Լ���λ�ã�Ҳ����˵��Ҫ������
		{
			Pop(&StkQueen, &curQueen);	//�����������Ҫ�õ���һ�еĻʺ�Ȼ�������ƶ���
			curQueen.col = curQueen.col + 1;	//��ʱ��Ҳ�Ѿ�׼����һ��whileѭ��Ϊ����ʺ��ҵ���һ�����ʵ�λ��
			while (curQueen.col > N && !StkQueen.stacklength == 0)	//��������ʺ��Ѿ��������һ�л���ջ���ˣ�������Ҫ�����Լ�������
			{
				Pop(&StkQueen, &curQueen);
				curQueen.col = curQueen.col + 1;
			}
		}
	}
	cout << "Total number of Solutions�� " << resultCount << endl;
	DestroyStack(&StkQueen);
	return OK;
}
int main()
{
	PlaceQueen(8);
	return 0;
}
