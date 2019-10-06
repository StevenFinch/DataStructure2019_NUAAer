/***************************************
 **   Filename： 约瑟夫环问题链式表解法.cpp
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

using namespace std;

const int OK = 1;
const int ERROR = 0;
typedef int Status;
typedef int ElemType;
typedef struct LNode
{
	ElemType data;
	struct LNode* next;
}LNode, * LinkList;

typedef struct {
	LinkList head;
	LinkList tail;
	LNode* pCurNode;
	int length;
}ListInfo;

Status InitList(ListInfo* List, int n)
{
	//开辟头结点并放置头指针
	List->head = NULL;
	List->head = (LNode*)malloc(sizeof(LNode));
	if (NULL == List->head)
		exit(OVERFLOW);
	List->head->next = NULL;

	List->tail = List->head;
	List->pCurNode = List->head;
	List->length = 0;

	//插入新元素
	LNode* newNode;
	for (int i = 0; i < n; i++)
	{
		//创建新节点
		newNode = NULL;
		newNode = (LNode*)malloc(sizeof(LNode));
		if (NULL == newNode)
			return ERROR;
		newNode->data = i + 1;
		newNode->next = NULL;

		//插入并重置尾指针
		List->tail->next = newNode;
		List->tail = List->tail->next;

		//!!
		List->length++;
	}
	return OK;
}
Status DeleteElem(ListInfo* List, int pos, ElemType* elem)
{
	if (pos < 1 || pos > List->length)
		return ERROR;

	int j = 1;
	LNode* p = List->head;
	LNode* q;
	while (j < pos)
	{
		p = p->next;
		j++;
	}
	if (!(p->next) || j > pos)
		return ERROR;
	//删除
	q = p->next;
	*elem = q->data;
	p->next = q->next;
	free(q);
	List->length--;
	if (NULL == p->next)
	{
		List->tail = q;
	}
	return OK;
}
Status TraverseList(ListInfo* List)
{
	LNode* p = List->head->next;
	while (NULL != p)
	{
		cout << left;
		cout << setw(3) << p->data;
		p = p->next;
	}
	cout << endl;
	return OK;
}
Status Dequeue(ListInfo* List, int n, int m)
{
	int num = 1;
	int pos = 1;
	ElemType elem;
	while (List->length != 0)
	{
		if (List->length < pos)
		{
			pos = 1;
		}
		if (num == m)
		{
			DeleteElem(List, pos, &elem);
			cout << elem << " ";
			num = 1;
		}
		else
		{
			num++;
			pos++;
		}

	}
	return OK;
}
int main()
{
	int n;//总人数
	int m;//报数数字
	int elem;
	cin >> n >> m;
	ListInfo List;
	InitList(&List, n);
	Dequeue(&List, n, m);
	system("pause");
	return 0;
}
