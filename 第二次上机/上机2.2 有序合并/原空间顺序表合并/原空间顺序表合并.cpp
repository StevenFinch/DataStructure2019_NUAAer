/***************************************
 **   Filename： 原空间顺序表合并.cpp
 **
 **   Compiler:  Visual Studio 2019
 **
 **   StudentID: 1618*****
 **
 **   Name:      Steven
 **
 ***************************************/
#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>

using namespace std;

const int LIST_INIT_SIZE = 256;
const int LIST_INCREMENT = 256;
const int OK = 1;
const int ERROR = 0;
const int YES = 1;
const int NO = 0;

typedef int ElemType;
typedef int Status;
typedef struct
{
	ElemType* pElem;
	int length;
	int size;
}SeqList;

Status InitList(SeqList* List, string filename)
{
	List->pElem = NULL;	
	List->pElem = (ElemType*)malloc(LIST_INIT_SIZE * sizeof(ElemType));
	if (NULL == List->pElem)
		exit(OVERFLOW);
	for (int i = 0; i < LIST_INIT_SIZE; i++)	
	{
		List->pElem[i] = -1;
	}
	List->length = 0;
	List->size = LIST_INIT_SIZE;

	ifstream inFile(filename);
	if (!inFile)
	{
		return ERROR;
	}
	int i = 0;
	while (!inFile.eof())
	{
		inFile >> List->pElem[i++];
		List->length++;
	}
	inFile.close();
	return OK;
}
Status DestoryList(SeqList* List)
{
	if (NULL == List->pElem)
	{
		free(List->pElem);
		List->pElem = NULL;	
	}
	List->size = 0;
	List->length = 0;
	return OK;
}
Status ListTraverse(SeqList* List)
{
	if (List->length != 0)
	{
		for (int i = 0; i < List->length; i++)
		{
			cout << setw(4) << List->pElem[i];
		}
		cout << endl;
		return OK;
	}
	return ERROR;
}
Status InsertElem(SeqList* List, int logicalPos, ElemType elem)
{

	if (logicalPos > 0 && logicalPos < List->length + 1)
	{

		if (List->length >= List->size)
		{
			List->pElem = (ElemType*)realloc(List->pElem, (List->size + LIST_INCREMENT) * sizeof(ElemType));
			if (NULL == List->pElem)	
			{
				cout << "Reallocating failed";
				exit(OVERFLOW);
			}
			List->size = List->size + LIST_INCREMENT;
		}
		ElemType* q = &List->pElem[logicalPos - 1];	
		for (ElemType* p = &List->pElem[List->length - 1]; p >= q; p--)	
		{
			*(p + 1) = *p;
		}
		*q = elem;
		List->length++;
		return OK;
	}
	return ERROR;
}
void GetUnionOfTwoLists(SeqList* l1, SeqList* l2)
{
	int i = 0, j = 0;
	for (i, j; i < l1->length && j < l2->length;)
	{
		if (l2->pElem[j] < l1->pElem[i])
		{
			InsertElem(l1, i + 1, l2->pElem[j]);
			j++;
			i++;
		}
		else if (l2->pElem[j] == l1->pElem[i])	//==
		{
			i++;
			j++;
		}
		else
		{
			i++;
		}
	}
	while (j < l2->length - 1)
	{
		InsertElem(l1, i + 1, l2->pElem[j]);
		i++;
		j++;
	}
	return;
}

int main()
{
	SeqList l1;
	SeqList l2;
	InitList(&l1, "l1.txt");
	InitList(&l2, "l2.txt");

	GetUnionOfTwoLists(&l1, &l2);

	SeqList l3;
	InitList(&l3, "l1.txt");

	l3 = l1;
	ListTraverse(&l1);
	ListTraverse(&l2);
	ListTraverse(&l3);
}