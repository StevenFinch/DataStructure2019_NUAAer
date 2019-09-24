/***************************************
 **   Filename： 学生排队问题.cpp
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
typedef int ElemType;
typedef int Status;

typedef struct LNode {
	ElemType data;
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
	//开辟头节点
	List->head = NULL;
	List->head = (LNode*)malloc(sizeof(SListInfo));
	if (NULL == List->head)
		exit(OVERFLOW);
	List->head->next = NULL;

	//连接
	List->tail = List->head;
	List->pCurNode = List->head;
	List->length = 0;

	return OK;
}
Status ListTraverse(SListInfo* List)
{
	cout << left;
	LNode* p = List->head->next;
	while (p != NULL)
	{
		cout << setw(3) << p->data;
		p = p->next;
	}
	cout << endl;
	return OK;
}
Status GetElem(SListInfo* List, int pos)
{
	if (pos < 1 || pos > List->length)	//合法性检验
		return ERROR;
	int j = 1;	//计数器
	LNode* p = List->head->next;
	while (j < pos)	//链式存储中不存在物理存储的位序概念，链表中节点的序号可以与其逻辑描述保持一致
	{
		p = p->next;
		++j;
	}
	List->pCurNode = p;
	return OK;
}
int LocateElem(SListInfo* List, ElemType* elem)
{
	LNode* p = List->head->next;
	int j = 1;	//计数器
	while (p->data != *elem && p->next != List->tail)
	{
		p = p->next;
		j++;
	}
	if (p->data == *elem)
	{
		List->pCurNode = p;
		return j;
	}
	else if (p->next == List->tail)
	{
		return 0;	//逻辑0代表此元素不存在
	}
}
Status InsertElemAfterCurNode(SListInfo* List, ElemType* elem)		//将elem插入在pCurNode后
{
	//为新节点申请空间
	LNode* newNode = (LNode*)malloc(sizeof(LNode));
	if (newNode == NULL)
		exit(OVERFLOW);
	newNode->data = *elem;
	newNode->next = NULL;

	//插入新节点
	newNode->next = List->pCurNode->next;
	List->pCurNode->next = newNode;

	//如果是表尾节点，则表尾指针更新
	if (List->pCurNode->next == NULL)
	{
		List->tail->next = newNode;
		List->tail = List->tail->next;
	}

	List->length++;	//!!!
	return OK;
}
Status DeleteElemAfterCurNode(SListInfo* List)	//删除pCurNode后元素并在elem中返回
{
	//有效性检验(当前节点及下一节点都不可以是尾节点)
	if (List->pCurNode == List->tail && List->pCurNode->next == List->tail)
		return ERROR;

	//删除当前节点下一节点
	LNode* p;
	p = List->pCurNode->next;
	List->pCurNode->next = List->pCurNode->next->next;
	free(p);

	List->length--;	//!!!
	return OK;
}
int main()
{
	SListInfo List;
	InitList(&List);

	int n;	//学生数量
	int m;	//调整次数
	cin >> n >> m;

	//按照学号排列
	while (n)
	{
		InsertElemAfterCurNode(&List, &n);
		n--;
	}

	int p;	//待调整学生的学号
	int q;	//调整方式
	int pos;	//临时存储位置

	//进行调整
	while (m)
	{
		cin >> p >> q;
		if (q > 0)
		{
			GetElem(&List, LocateElem(&List, &p) + q);
			InsertElemAfterCurNode(&List, &p);	//该元素在新位置插入

			GetElem(&List, LocateElem(&List, &p) - 1);	
			DeleteElemAfterCurNode(&List);	//该元素在原位置删除
		}
		if (q < 0)
		{
			pos = LocateElem(&List, &p);
			GetElem(&List, LocateElem(&List, &p) - 1);
			DeleteElemAfterCurNode(&List);	//该元素在原位置删除

			GetElem(&List, pos + q);
			InsertElemAfterCurNode(&List, &p);	//该元素在新位置插入
		}
		m--;
	}
	ListTraverse(&List);
	system("pause");
	return 0;
}
