/***************************************
 **   Filename： LinkList.cpp
 **
 **   StudentID: 1618*****
 **
 **   Name:      Steven
 **
 ***************************************/
#include <iostream>
#include <iomanip>
#include <fstream>

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
	struct LNode* next;
}LNode, * LinkList;

typedef struct 
{
	LinkList head;
	LinkList tail;
	LNode* pCurNode;
	int length;
}SListInfo;

//初始化、销毁、清空操作
Status InitList(SListInfo* List)
{
	//开辟头节点
	List->head = NULL;
	List->head = (LNode*)malloc(sizeof(SListInfo));
	if (NULL == List->head)
		exit(OVERFLOW);
	List->head->next = NULL;

	//开辟尾节点
	List->tail = NULL;
	List->tail = (LNode*)malloc(sizeof(SListInfo));
	if (NULL == List->tail)
		exit(OVERFLOW);
	List->tail->next = NULL;

	//连接
	List->head->next = List->tail;
	List->pCurNode = List->head;
	List->length = 0;

	return OK;
}
Status DestroyList(SListInfo* List)
{
	//释放所有节点
	LNode* p;
	while (List->head->next != List->tail)
	{
		p = List->head->next;
		List->head->next = p->next;
		free(p);
	}
	free(List->tail);
	free(List->head);

	//指空所有指针
	List->head = NULL;
	List->tail = NULL;
	List->pCurNode = NULL;
	List->length = 0;

	return OK;
}
Status ClearList(SListInfo* List)	//与DestroyList相比仅仅是不销毁头节点
{
	//释放所有节点
	LNode* p;
	while (List->head->next != List->tail)
	{
		p = List->head->next;
		List->head->next = p->next;
		free(p);
	}
	free(List->tail);

	//指空除头指针以外所有指针
	List->tail = NULL;
	List->pCurNode = NULL;
	List->length = 0;

	return OK;
}

//访问型操作
Status ListEmpty(SListInfo* List)
{
	if (List->length == 0)
		return YES;
	return NO;
}
Status GetElem(SListInfo* List, int pos, ElemType* elem)
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
	*elem = List->pCurNode->data;
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
Status PriorElem(SListInfo* List, ElemType curElem, ElemType* priorElem)
{
	int pos = LocateElem(List, &curElem);
	if (pos > 1)
	{
		GetElem(List, pos - 1, priorElem);
		return OK;
	}
	return ERROR;
}
Status NextElem(SListInfo* List, ElemType curElem, ElemType* nextElem)
{
	int pos = LocateElem(List, &curElem);
	if (pos > 0 && pos < List->length)
	{
		GetElem(List, pos + 1, nextElem);
		return OK;
	}
	return ERROR;
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

//加工型操作
Status SetElem(SListInfo* List, int pos, ElemType* elem)	//改变pos位置数据为elem
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
	if (List->pCurNode == List->tail)
		newNode->next = List->tail;

	List->length++;	//!!!
}
Status DeleteElemAfterCurNode(SListInfo* List, ElemType* elem)	//删除pCurNode后元素并在elem中返回
{
	//有效性检验(当前节点及下一节点都不可以是尾节点)
	if (List->pCurNode == List->tail && List->pCurNode->next == List->tail)
		return ERROR;

	*elem = List->pCurNode->next->data;

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
	ElemType elem;
	cout << left;

	//以下测试中，暂且将ElemType当作int类型：
	if (InitList(&List))
	{
		//数据读取
		ifstream inFile("LinkList.txt");
		if (!inFile)
			return ERROR;
		while (!inFile.eof())
		{
			inFile >> elem;
			InsertElemAfterCurNode(&List, &elem);
		}
		inFile.close();

		cout << setw(50) << "LinkList: ";
		ListTraverse(&List);

		//SetElem:
		elem = 25;
		if (SetElem(&List, 3, &elem))
		{
			cout << setw(50) << "After SetElem, LinkList: ";
			ListTraverse(&List);
		}

		//LocateElem, InsertElemAfterCurNode:
		elem = 6;
		LocateElem(&List, &elem);	//移动pCurElem
		if (InsertElemAfterCurNode(&List, &elem))
		{
			cout << setw(50) << "After InsertElemAfterCurNode, LinkList: ";
			ListTraverse(&List);
		}

		//DeleteElemAfterCurNode
		if (DeleteElemAfterCurNode(&List, &elem))
		{
			cout << setw(50) << "After DeleteElemAfterCurNode, LinkList: ";
			ListTraverse(&List);
		}

		//GetElem
		if (GetElem(&List, 6, &elem))
		{
			cout << setw(50) << "GetElem: " << elem << endl;
		}

		//PriorElem
		if (PriorElem(&List, elem, &elem))
		{
			cout << setw(50) << "PriorElem: " << elem << endl;
		}

		//NextElem
		if (NextElem(&List, elem, &elem))
		{
			cout << setw(50) << "NextElem: " << elem << endl;
		}

		//DestroyList
		if (DestroyList(&List))
		{
			if (ListEmpty(&List))
				cout << "DestroyList and ListEmpty" << endl;
		}

	}
	system("pause");
	return 0;
}
