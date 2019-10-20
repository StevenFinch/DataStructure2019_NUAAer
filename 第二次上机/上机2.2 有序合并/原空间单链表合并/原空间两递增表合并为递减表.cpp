/***************************************
 **   Filename： 空间两递增表合并为递减表.cpp
 **
 **   Compiler:  Visual Studio 2019
 **
 **   StudentID: 1618*****
 **
 **   Name:      Steven
 **
 ***************************************/
#include<iostream>
using namespace std;

const int OK = 1;
const int ERROR = 0;
typedef int Status;
typedef struct LNode {
	int data;
	struct LNode* next;
}LNode, * LinkList;
typedef struct {
	LinkList head;
	LinkList tail;
	LNode* pCurNode;
	int length;
}SListInfo;

Status InitList(SListInfo* List)
{
	List->head = NULL;
	List->head = (LNode*)malloc(sizeof(SListInfo));
	if (NULL == List->head)
		exit(OVERFLOW);
	List->head->next = NULL;

	List->tail = List->head;
	List->pCurNode = List->head;
	List->length = 0;

	return OK;
}
Status ListTraverse(SListInfo* List)
{
	LNode* p = List->head->next;
	while (p != NULL)
	{
		cout << p->data << ' ';
		p = p->next;
	}
	cout << endl;
	return OK;
}
//非头插法，改变了pCur
Status InsertElemAfterCurNode(SListInfo* List, int elem)
{
	LNode* newNode = (LNode*)malloc(sizeof(LNode));
	if (newNode == NULL)
		exit(OVERFLOW);
	newNode->data = elem;
	newNode->next = NULL;

	newNode->next = List->pCurNode->next;
	List->pCurNode->next = newNode;
	List->pCurNode = newNode;

	if (List->pCurNode->next == NULL)
		List->tail = newNode;

	List->length++;
}
Status MergeTwoList(SListInfo* L1, SListInfo* L2, SListInfo* L3)	//L3指向新表头结点
{
	if (L1->head == NULL || L2->head == NULL)//表不存在
		return ERROR;
	LNode* p1 = L1->head->next;//遍历L1进行比较
	LNode* p2 = L2->head->next;//遍历L2进行比较
	LNode* s = NULL;//前驱指针

	L3->head = L1->head;//指向L1头结点充当L3头结点
	L1->head->next = NULL;//建立新表
	L3->pCurNode = L3->head;
	L3->length = 0;

	while (p1 && p2)
	{
		if (p1->data <= p2->data)
		{
			//*头插法保证新表L3递减有序
			s = p1->next;
			p1->next = L1->head->next;
			L1->head->next = p1;
			p1 = s;
			L3->length++;
		}
		else
		{
			//*头插法保证新表L3递减有序
			s = p2->next;
			p2->next = L1->head->next;
			L1->head->next = p2;
			p2 = s;
			L3->length++;
		}
	}
	while (p1)
	{
		s = p1->next;
		p1->next = L1->head->next;
		L1->head->next = p1;
		p1 = s;
		L3->length++;
	}
	while (p2)
	{
		s = p2->next;
		p2->next = L1->head->next;
		L1->head->next = p2;
		p2 = s;
		L3->length++;
	}
	return OK;
}
int main()
{
	//建有序表
	SListInfo L1, L2, L3;
	if (InitList(&L1) && InitList(&L2) && InitList(&L3))
	{
		for (int i = 0; i < 10; i++)
		{
			InsertElemAfterCurNode(&L1, 2 * i);
			InsertElemAfterCurNode(&L2, 2 * i + 1);
		}
	}
	ListTraverse(&L1);
	ListTraverse(&L2);

	//合并
	MergeTwoList(&L1, &L2, &L3);
	ListTraverse(&L3);

	system("pause");
	return 0;
}
