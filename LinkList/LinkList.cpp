/***************************************
 **   Filename�� LinkList.cpp
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

//��ʼ�������١���ղ���
Status InitList(SListInfo* List)
{
	//����ͷ�ڵ�
	List->head = NULL;
	List->head = (LNode*)malloc(sizeof(SListInfo));
	if (NULL == List->head)
		exit(OVERFLOW);
	List->head->next = NULL;

	//����β�ڵ�
	List->tail = NULL;
	List->tail = (LNode*)malloc(sizeof(SListInfo));
	if (NULL == List->tail)
		exit(OVERFLOW);
	List->tail->next = NULL;

	//����
	List->head->next = List->tail;
	List->pCurNode = List->head;
	List->length = 0;

	return OK;
}
Status DestroyList(SListInfo* List)
{
	//�ͷ����нڵ�
	LNode* p;
	while (List->head->next != List->tail)
	{
		p = List->head->next;
		List->head->next = p->next;
		free(p);
	}
	free(List->tail);
	free(List->head);

	//ָ������ָ��
	List->head = NULL;
	List->tail = NULL;
	List->pCurNode = NULL;
	List->length = 0;

	return OK;
}
Status ClearList(SListInfo* List)	//��DestroyList��Ƚ����ǲ�����ͷ�ڵ�
{
	//�ͷ����нڵ�
	LNode* p;
	while (List->head->next != List->tail)
	{
		p = List->head->next;
		List->head->next = p->next;
		free(p);
	}
	free(List->tail);

	//ָ�ճ�ͷָ����������ָ��
	List->tail = NULL;
	List->pCurNode = NULL;
	List->length = 0;

	return OK;
}

//�����Ͳ���
Status ListEmpty(SListInfo* List)
{
	if (List->length == 0)
		return YES;
	return NO;
}
Status GetElem(SListInfo* List, int pos, ElemType* elem)
{
	if (pos < 1 || pos > List->length)	//�Ϸ��Լ���
		return ERROR;
	int j = 1;	//������
	LNode* p = List->head->next;
	while (j < pos)	//��ʽ�洢�в���������洢��λ���������нڵ����ſ��������߼���������һ��
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
	int j = 1;	//������
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
		return 0;	//�߼�0�����Ԫ�ز�����
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

//�ӹ��Ͳ���
Status SetElem(SListInfo* List, int pos, ElemType* elem)	//�ı�posλ������Ϊelem
{
	int j = 1;	//������
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
	if (List->pCurNode == List->tail)
		newNode->next = List->tail;

	List->length++;	//!!!
}
Status DeleteElemAfterCurNode(SListInfo* List, ElemType* elem)	//ɾ��pCurNode��Ԫ�ز���elem�з���
{
	//��Ч�Լ���(��ǰ�ڵ㼰��һ�ڵ㶼��������β�ڵ�)
	if (List->pCurNode == List->tail && List->pCurNode->next == List->tail)
		return ERROR;

	*elem = List->pCurNode->next->data;

	//ɾ����ǰ�ڵ���һ�ڵ�
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

	//���²����У����ҽ�ElemType����int���ͣ�
	if (InitList(&List))
	{
		//���ݶ�ȡ
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
		LocateElem(&List, &elem);	//�ƶ�pCurElem
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
