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
bool SelectSortList(ListInfo* List)	//核心代码
{
	LNode* p;
	LNode* q;
	LNode* small;
	int temp;
	for (p = List->head->next; p->next != NULL; p = p->next)	//注意判断条件，最后一个元素无需比较
	{
		small = p;
		for (q = p->next; q != NULL; q = q->next)
		{
			if (q->data < small->data)
			{
				small = q;
			}
		}
		if (small != p)
		{
			temp = p->data;
			p->data = small->data;
			small->data = temp;
		}
	}
	return true;
}
int main()
{
	ListInfo List;
	InitList(&List);
	SelectSortList(&List);
	TraverseList(&List);
	system("pause");
	return 0;
}
