/*	Compiler: Visual Studio 2019
**	UpdateTime: 2019/09/24
**	ID: 161840225   */
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
		List->tail = newNode;

	List->length++;	//!!!
}
Status ListTraverse(SListInfo* List)
{
	LNode* p = List->head->next;
	while (p != NULL)
	{
		cout << setw(3) << p->data;
		p = p->next;
	}
	cout << endl;
	return OK;
}
Status LinkReverse(SListInfo* List)
{
	//需要三个指针联动，pCur负责前进，pTemp负责记录当前节点，pRev负责记录前一个节点
	
	LNode* pCur = List->head->next;
	LNode* pRev = List->head;
	LNode* pTemp = pCur;
	while (pCur != NULL)
	{
		pTemp = pCur;	//pTemp归位
		pCur = pCur->next;	//pCur前进
		pTemp->next = pRev;	//链接
		pRev = pTemp;	//pRev前进
	}
	List->head->next->next = NULL;
	List->tail = List->head->next;
	List->head->next = pTemp;

	return OK;
}
int main()
{
	cout << left;
	ElemType elem;
	SListInfo List;
	if (InitList(&List))
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
