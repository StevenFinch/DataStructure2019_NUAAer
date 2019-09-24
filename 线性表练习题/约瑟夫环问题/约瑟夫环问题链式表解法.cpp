/***************************************
 **   Filename�� Լɪ��������ʽ��ⷨ.cpp
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
	//����ͷ��㲢����ͷָ��
	List->head = NULL;
	List->head = (LNode*)malloc(sizeof(LNode));
	if (NULL == List->head)
		exit(OVERFLOW);
	List->head->next = NULL;

	List->tail = List->head;
	List->pCurNode = List->head;
	List->length = 0;

	//������Ԫ��
	LNode* newNode;
	for (int i = 0; i < n; i++)
	{
		//�����½ڵ�
		newNode = NULL;
		newNode = (LNode*)malloc(sizeof(LNode));
		if (NULL == newNode)
			return ERROR;
		newNode->data = i + 1;
		newNode->next = NULL;

		//���벢����βָ��
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
	//ɾ��
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
	int n;//������
	int m;//��������
	int elem;
	cin >> n >> m;
	ListInfo List;
	InitList(&List, n);
	Dequeue(&List, n, m);
	system("pause");
	return 0;
}
