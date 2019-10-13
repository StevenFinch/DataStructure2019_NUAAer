/***************************************
 **   Filename： 约瑟夫环问题顺序表解法.cpp
 **
 **   Compiler:  Visual Studio 2019
 **
 **   StudentID: 1618*****
 **
 **   Name:      Steven
 **
 ***************************************/
#include <iostream>

using namespace std;

const int OK = 1;
const int ERROR = 0;
typedef int Status;
typedef int ElemType;
typedef struct
{
	ElemType* pData;
	int length;
	int size;
}SeqList;

Status InitList(SeqList* List, int n)
{
	List->pData = NULL;
	List->pData = (ElemType*)malloc(sizeof(ElemType) * n);
	if (NULL == List->pData)
		return ERROR;

	for (int i = 0; i < n; i++)
	{
		List->pData[i] = i + 1;
	}
	List->length = n;
	return OK;
}
Status DeleteElem(SeqList* List, int pos, ElemType* elem)
{
	*elem = List->pData[pos - 1];
	for (int i = pos - 1; i < List->length - 1; i++)
	{
		List->pData[i] = List->pData[i + 1];
	}
	List->length--;
	return OK;
}
Status Dequeue(SeqList* List, int m)
{
	int num = 1;
	int pos = 1;
	ElemType elem;
	while (List->length != 0)
	{
		if (num == m)
		{
			DeleteElem(List, pos, &elem);
			cout << elem << ' ';
			num = 1;
		}
		else
		{
			num++;
			pos++;
		}
		if (pos > List->length)
		{
			pos = 1;
		}
	}
	return OK;
}
int main()
{
	int n;//总人数
	int m;//出队人数
	cin >> n >> m;
	SeqList List;
	InitList(&List, n);
	Dequeue(&List, m);
	system("pause");
	return 0;
}
