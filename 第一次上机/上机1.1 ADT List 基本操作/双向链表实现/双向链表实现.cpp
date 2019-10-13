/***************************************
 **   Filename： 双向链表实现.cpp
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
const int YES = 1;
const int NO = 0;
typedef int ElemType;
typedef int Status;
typedef struct LNode
{
	ElemType data;
	struct LNode* prior;
	struct LNode* next;
}LNode, * LinkList;
typedef struct
{
	LinkList head;
	LinkList tail;
	LNode* pCurNode;
	int length;
}ListInfo;

//初始化、销毁、清空操作
Status InitList(ListInfo* List)
{
	List->head = NULL;
	List->head = (LNode*)malloc(sizeof(LNode));
	if (NULL == List->head)
		return ERROR;
	List->head->next = NULL;
	List->head->prior = NULL;

	List->tail = List->head;
	List->pCurNode = List->head;
	List->length = 0;
	return OK;
}
Status DestroyList(ListInfo* List)
{
	//释放所有节点
	LNode* p;
	while (List->head->next != NULL)
	{
		p = List->head->next;
		List->head->next = p->next;
		free(p);
	}
	free(List->head);

	//指空所有指针
	List->head = NULL;
	List->tail = NULL;
	List->pCurNode = NULL;
	List->length = 0;

	return OK;
}
Status ClearList(ListInfo* List)	//与DestroyList相比仅仅是不销毁头节点
{
	//释放除头节点所有节点
	LNode* p;
	while (List->head->next != NULL)
	{
		p = List->head->next;
		List->head->next = p->next;
		free(p);
	}

	//指空除头指针以外所有指针
	List->tail = NULL;
	List->pCurNode = NULL;
	List->length = 0;

	return OK;
}

//访问型操作
Status ListEmpty(ListInfo* List)
{
	if (List->length == 0)
		return YES;
	return NO;
}
int LocateElem(ListInfo* List, ElemType* elem)	  //返回带查找元素的位置
{
	LNode* p = List->head->next;
	int j = 1;
	while (p->data != *elem && p != NULL)
	{
		p = p->next;
		j++;
	}
	if (NULL == p)
	{
		return 0;
	}
	else if (p->data == *elem)
	{
		List->pCurNode = p;
		return j;
	}
}
Status GetElem(ListInfo* List, int pos, ElemType* elem)	//返回某位置的元素存储在elem中
{
	if (pos < 1 || pos > List->length)	
		return ERROR;
	int j = 1;	
	LNode* p = List->head->next;
	while (j < pos)	
	{
		p = p->next;
		++j;
	}
	List->pCurNode = p;
	*elem = List->pCurNode->data;
	return OK;
}
Status PriorElem(ListInfo* List, ElemType curElem, ElemType* priorElem)
{
	if (LocateElem(List, &curElem) > 2)
	{
		*priorElem = List->pCurNode->prior->data;
		return OK;
	}
	return ERROR;
}
Status NextElem(ListInfo* List, ElemType curElem, ElemType* nextElem)
{
	if (LocateElem(List, &curElem) < List->length)
	{
		*nextElem = List->pCurNode->next->data;
		return OK;
	}
	return ERROR;
}
Status TraverseList(ListInfo* List)
{
	if (0 == List->length)
		return ERROR;
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

//加工型操作
Status SetElem(ListInfo* List, int pos, ElemType* elem)	//改变pos位置数据为elem
{
	int j = 1;	//计数器
	List->pCurNode = List->head->next;
	if (pos > 0 && pos < List->length + 1)
	{
		while (pos != j)
		{
			List->pCurNode = List->pCurNode->next;
			j++;
		}
		List->pCurNode->data = *elem;
		return OK;
	}
	return ERROR;
}
Status DeleteCurNode(ListInfo* List, ElemType* elem)
{
	List->pCurNode->next->prior = List->pCurNode->prior;
	List->pCurNode->prior->next = List->pCurNode->next;
	*elem = List->pCurNode->data;
	free(List->pCurNode);
	return OK;
}
Status InsertElemAfterCurNode(ListInfo* List, ElemType* elem)
{
	LNode* newNode = (LNode*)malloc(sizeof(LNode));
	if (NULL == newNode)
		return ERROR;
	newNode->data = *elem;
	newNode->next = List->pCurNode->next;
	newNode->prior = List->pCurNode;
	List->pCurNode->next = newNode;

	if (NULL != newNode->next)	
		newNode->next->prior = newNode;
	else//如果插入后是尾节点则重置尾指针
		List->tail = newNode;
	List->length++;
	return OK;
} 
Status InsertElemBeforeCurNode(ListInfo* List, ElemType* elem)
{
	if (List->pCurNode == List->head)//当前节点不能是头结点
		return ERROR;
	LNode* newNode = (LNode*)malloc(sizeof(LNode));
	if (NULL == newNode)
		return ERROR;
	newNode->data = *elem;
	newNode->next = List->pCurNode;
	newNode->prior = List->pCurNode->prior;
	List->pCurNode->prior = newNode;
	newNode->prior->next = newNode;
	return OK;
}

int main()
{
	//省略测试函数
	ListInfo List;
	InitList(&List);
	DestroyList(&List);

	system("pause");
	return 0;
}