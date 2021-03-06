/*	Compiler: Visual Studio 2019
**	UpdateTime: 2019/09/27
**	ID: 161840225   */
#include <iostream>
#include <fstream>
#include <iomanip>

using namespace std;

const int LIST_INIT_SIZE = 256;
const int OK = 1;
const int ERROR = 0;

typedef int ElemType;
typedef int Status;
typedef struct 
{
	ElemType* pElem;
	int length;
	int size;
}SeqList;

Status InitList(SeqList* List)
{
	List->pElem = NULL;
	List->pElem = (ElemType*)malloc(LIST_INIT_SIZE * sizeof(ElemType));
	if (NULL == List->pElem)
	{
		exit(OVERFLOW);
	}
	for (int i = 0; i < LIST_INIT_SIZE; i++)
	{
		List->pElem[i] == -1;
	}
	List->length = 0;
	List->size = LIST_INIT_SIZE;

	ifstream inFile("SeqquenceList.txt");
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
Status ListTraverse(SeqList* List)
{
	if (List->length!=0)
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
Status ListReaverse(SeqList* List)
{
	if (List->length != 0)
	{
		ElemType temp;
		for (int i = 0; i < List->length / 2; i++)
		{
			temp = List->pElem[i];
			List->pElem[i] = List->pElem[List->length - 1 - i];
			List->pElem[List->length - 1- i] = temp;
		}
		return OK;
	}
	return ERROR;
}
int main()
{
	SeqList List;
	InitList(&List);

	ListTraverse(&List);
	ListReaverse(&List);
	ListTraverse(&List);

	system("pause");
	return 0;
}
