#include <iostream>
#include <fstream>
#include <iomanip>

using namespace std;

const int OK = 1;
const int ERROR = 0;

typedef int ElemType;
typedef int Status;
typedef struct LNode
{
	ElemType data;
	struct LNode* next;
}LNode, *LinkList;
typedef struct
{
	LinkList head;
	LinkList tail;
	LNode* pCurNode;
	int length;
}SListInfo;

Status InitLink(SListInfo* Link)
{
	Link->head = NULL;
	Link->head = (LNode*)malloc(sizeof(LNode));
	if (NULL == Link->head)
		exit(OVERFLOW);
	Link->head->next = NULL;

	Link->tail = NULL;
	Link->tail = (LNode*)malloc(sizeof(LNode));
	if (NULL == Link->tail)
		exit(OVERFLOW);
	Link->tail->next = NULL;

	Link->head->next = Link->tail;
	Link->pCurNode = Link -> head;
	Link->length = 0;

	return OK;
}
Status InsertElemAfterCurNode(SListInfo* List, ElemType* elem)
{
	LNode* newNode = (LNode*)malloc(sizeof(LNode));
	if (NULL == newNode)
		exit(OVERFLOW);
	newNode->data = *elem;
	newNode->next = NULL;

	newNode->next = List->pCurNode->next;
	List->pCurNode->next = newNode;

	if (List->pCurNode == List->tail)
		newNode->next = List->tail;

	List->length++;
	return OK;
}
Status ListTraverse(SListInfo* List)
{
	LNode* p = List->head->next;
	while (p != List->tail)
	{
		cout << setw(3) << p->data;
		p = p->next;
	}
	cout << endl;
	return OK;
}
Status LinkReverse(SListInfo* List)
{
	//需要三个指针联动，pCur负责反转前前进，pTemp负责记录当前节点，pRev负责记录当前节点前一个节点
	
	LNode* pCur = List->head->next;
	LNode* pRev = List->head;
	LNode* pTemp;
	while (pCur != NULL)
	{
		pTemp = pCur;	//pTemp归位
		pCur = pCur->next;	//pCur前进
		pTemp->next = pRev;	//链接
		pRev = pTemp;	//pRev前进
	}
	pTemp = List->head;
	List->head = List->tail;
	List->tail = pTemp;
	List->tail->next = NULL;
	return OK;
}
int main()
{
	cout << left;
	ElemType elem;
	SListInfo List;
	if (InitLink(&List))
	{
		//读数据
		ifstream inFile("LinkList.txt");
		if (!inFile)
			return ERROR;
		while (!inFile.eof())
		{
			inFile >> elem;
			InsertElemAfterCurNode(&List, &elem);
		}
		inFile.close();	

		cout << setw(20) << "LinkList: ";
		ListTraverse(&List);

		LinkReverse(&List);
		cout << setw(20) << "LinkList reversed: ";
		ListTraverse(&List);
	}
	system("pause");
	return OK;
	
}