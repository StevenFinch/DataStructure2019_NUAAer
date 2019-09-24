/***************************************
 **   Filename�� ����͵�����.cpp
 **
 **	  Compiler:   Visual Studio 2019
 **
 **   StudentID: 1618*****
 **
 **   Name:      Steven
 **
 ***************************************/
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
	//����ͷ�ڵ�
	List->head = NULL;
	List->head = (LNode*)malloc(sizeof(SListInfo));
	if (NULL == List->head)
		exit(OVERFLOW);
	List->head->next = NULL;

	//����
	List->tail = List->head;
	List->pCurNode = List->head;
	List->length = 0;

	return OK;
}
Status InsertElemAfterCurNode(SListInfo* List, ElemType* elem)		//��elem������pCurNode��
{
	//Ϊ�½ڵ�����ռ�
	LNode* newNode = (LNode*)malloc(sizeof(LNode));
	if (newNode == NULL)
		exit(OVERFLOW);
	newNode->data = *elem;
	newNode->next = NULL;

	//�����½ڵ�
	newNode->next = List->pCurNode->next;
	List->pCurNode->next = newNode;

	//����Ǳ�β�ڵ㣬���βָ�����
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
	//��Ҫ����ָ��������pCur����ǰ����pTemp�����¼��ǰ�ڵ㣬pRev�����¼ǰһ���ڵ�
	
	LNode* pCur = List->head->next;
	LNode* pRev = List->head;
	LNode* pTemp = pCur;
	while (pCur != NULL)
	{
		pTemp = pCur;	//pTemp��λ
		pCur = pCur->next;	//pCurǰ��
		pTemp->next = pRev;	//����
		pRev = pTemp;	//pRevǰ��
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
		//������
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