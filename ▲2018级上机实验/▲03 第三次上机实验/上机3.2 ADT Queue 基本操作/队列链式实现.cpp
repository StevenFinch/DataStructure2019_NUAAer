/*	Compiler: Visual Studio 2019
**	UpdateTime: 2019/10/06
**	ID: 161840225   */
#include <iostream>

using namespace std;

const int OK = 1;
const int ERROR = 0;
typedef int ElemType;
typedef int Status;
typedef struct QNode
{
	ElemType data;
	struct QNode* next;
}QNode, *LinkQueue;
typedef struct LinkQueueInfo
{
	LinkQueue front;
	LinkQueue rear;
	int Queuelength;
}LinkQueueInfo;
//��ʼ�������١���ղ���
Status InitQueue(LinkQueueInfo* Q)
{
	Q->front = NULL;
	Q->front = (QNode*)malloc(sizeof(QNode));
	if (NULL == Q->front)
		exit(1);
	Q->front->next = NULL;

	Q->rear = Q->front;
	Q->Queuelength = 0;

	return OK;
}
Status DestroyQueue(LinkQueueInfo* Q)
{
	//�Ӷ���ͷ��ʼɾ������βָ��
	while (Q->front)
	{
		Q->rear = Q->front->next;
		free(Q->front);
		Q->front = Q->rear;
	}
	Q->front = NULL;
	Q->rear = NULL;
	Q->Queuelength = 0;
	return OK;
}
Status ClearQueue(LinkQueueInfo* Q)
{
	//�������׿սڵ�Ͷ�βָ��
	while (Q->front->next)
	{
		Q->rear = Q->front->next->next;
		free(Q->front->next);
		Q->front->next = Q->rear;
	}
	Q->rear = Q->front;
	Q->Queuelength = 0;
	return OK;
}

//�����Ͳ���
bool QueueEmpty(LinkQueueInfo* Q)
{
	return Q->Queuelength == 0 ? true : false;
}
int QueueLength(LinkQueueInfo* Q)
{
	return Q->Queuelength;
}
Status GetHead(LinkQueueInfo* Q, ElemType* e)
{
	if (QueueEmpty(Q))
		return ERROR;
	*e = Q->front->next->data;
	return OK;
}
Status QueueTraverse(LinkQueueInfo* Q)
{
	if (QueueEmpty(Q))
		return ERROR;
	QNode* p = Q->front->next;
	while (p != NULL)
	{
		cout << p->data << ' ';
		p = p->next;
	}
	cout << endl;
	return OK;
}

/*
�ӹ��Ͳ���
ͷ�����ӣ�βָ����� 
*/ 
Status EnQueue(LinkQueueInfo* Q, ElemType e)
{
	QNode* q = (QNode*)malloc(sizeof(QNode));
	if (NULL == q)
		return ERROR;
	q->data = e;
	q->next = NULL;
	Q->rear->next = q;
	Q->rear = q;
	Q->Queuelength++;	//!!!
}
Status DeQueue(LinkQueueInfo* Q, ElemType* e)
{
	if (QueueEmpty(Q))	//��������Ƿ�Ϊ��
		return ERROR;
	*e = Q->front->next->data;
	QNode* p = Q->front->next;
	Q->front->next = p->next;
	if (p == Q->rear)
	{
		Q->rear = Q->front;	//�����������ֻ��һ��Ԫ��
	}
	free(p);
	p = NULL;
	Q->Queuelength--;	//!!!
	return OK;
}

//���麯����ElemTypeĬ��Ϊint
int main()
{
	ElemType e;
	LinkQueueInfo Q;

	InitQueue(&Q);

	for (int i = 1; i < 6; i++)
		EnQueue(&Q, i);
	QueueTraverse(&Q);

	DeQueue(&Q, &e);
	DeQueue(&Q, &e);
	QueueTraverse(&Q);
	if (!QueueEmpty(&Q))
	{
		GetHead(&Q, &e);
		cout << e << endl;
		cout << QueueLength(&Q) << endl;
	}
	DestroyQueue(&Q);

	system("pause");
	return 0;
}
