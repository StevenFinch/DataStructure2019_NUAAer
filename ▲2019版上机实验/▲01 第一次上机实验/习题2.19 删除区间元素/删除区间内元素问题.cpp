/*	Compiler: Visual Studio 2019
**	UpdateTime: 2019/09/27
**	ID: 161840225   */
#include <iostream>

using namespace std;
typedef int ElemType;
typedef struct LNode
{
	ElemType data;
	LNode* next;
}LNode, * LinkList;
typedef struct
{
	LinkList head;
	LinkList tail;
	LNode* pCurNode;
	int length;
}ListInfo;
bool InitList(ListInfo* List)
{
	List->head = NULL;
	List->head = (LNode*)malloc(sizeof(ListInfo));
	if (NULL == List->head)
		exit(OVERFLOW);
	List->head->next = NULL;
	List->tail = List->head;
	List->pCurNode = List->head;
	List->length = 0;
	while (List->length < 10)
	{
		int data;
		cin >> data;
		LNode* newNode = (LNode*)malloc(sizeof(LNode));
		if (NULL == newNode)
			exit(OVERFLOW);
		newNode->data = data;
		newNode->next = NULL;

		List->tail->next = newNode;
		List->tail = newNode;
		List->length++;
	}
	return true;
}
bool TraverseList(ListInfo* List)
{
	LNode* p = List->head->next;
	while (p != NULL)
	{
		cout << p->data << ' ';
		p = p->next;
	}
	return true;
}
bool DeleteElem(ListInfo* List, int mink, int maxk)
{
	if (List->head == NULL || List->head->next == NULL)
	{
		return false;
	}
	LNode* p = List->head;
	LNode* q = List->head->next;
	LNode* r = NULL;
	while (q && q->data <= mink)
	{
		p = q;
		q = q->next;
	}
	if (q)
	{
		while (q->data < maxk)
		{
			r = q;
			p->next = q->next;
			q = q->next;
			free(r);
		}
		return true;
	}
	return false;
}
int main()
{
	ListInfo List;
	InitList(&List);
	DeleteElem(&List, 3, 8);
	TraverseList(&List);
	system("pause");
	return 0;
}
