/***************************************
 **   Filename�� ѧ���Ŷ�����.cpp
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
	{
		List->tail->next = newNode;
		List->tail = List->tail->next;
	}

	List->length++;	//!!!
	return OK;
}
Status DeleteElemAfterCurNode(SListInfo* List)	//ɾ��pCurNode��Ԫ�ز���elem�з���
{
	//��Ч�Լ���(��ǰ�ڵ㼰��һ�ڵ㶼��������β�ڵ�)
	if (List->pCurNode == List->tail && List->pCurNode->next == List->tail)
		return ERROR;

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
	InitList(&List);

	int n;	//ѧ������
	int m;	//��������
	cin >> n >> m;

	//����ѧ������
	while (n)
	{
		InsertElemAfterCurNode(&List, &n);
		n--;
	}

	int p;	//������ѧ����ѧ��
	int q;	//������ʽ
	int pos;	//��ʱ�洢λ��

	//���е���
	while (m)
	{
		cin >> p >> q;
		if (q > 0)
		{
			GetElem(&List, LocateElem(&List, &p) + q);
			InsertElemAfterCurNode(&List, &p);	//��Ԫ������λ�ò���

			GetElem(&List, LocateElem(&List, &p) - 1);	
			DeleteElemAfterCurNode(&List);	//��Ԫ����ԭλ��ɾ��
		}
		if (q < 0)
		{
			pos = LocateElem(&List, &p);
			GetElem(&List, LocateElem(&List, &p) - 1);
			DeleteElemAfterCurNode(&List);	//��Ԫ����ԭλ��ɾ��

			GetElem(&List, pos + q);
			InsertElemAfterCurNode(&List, &p);	//��Ԫ������λ�ò���
		}
		m--;
	}
	ListTraverse(&List);
	system("pause");
	return 0;
}
