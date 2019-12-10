/*	Compiler: Visual Studio 2019
**	UpdateTime: 2019/11/14
**	ID: 161840225   */
#include<iostream>
#include<iomanip>
using namespace std;
const int MAXSIZE = 8;
typedef char ElemType;//Ĭ�϶�����Ԫ��Ϊchar
typedef struct CSNode
{
	ElemType data;
	int level;
	struct CSNode* firstchild;
	struct CSNode* nextsibling;
}CSNode, * CSTree;

void CreateCSTree(CSTree& T)
{//�����������й���������
	ElemType e;
	cin >> e;
	if (e == '#') 
		T = NULL;
	else
	{
		if (!(T = (CSTree)malloc(sizeof(CSNode)))) exit(0);
		T->data = e;
		T->level = 0;
		CreateCSTree(T->firstchild);
		CreateCSTree(T->nextsibling);
	}
}

void OutputNodeOfLevel(CSTree T, int i)
{
	/*
		ʡ�ԺϷ��Լ���
	*/
	CSTree p;
	//��һ��ѭ������
	CSTree Q[MAXSIZE];
	int front, rear;
	front = rear = 0;

	//��������
	T->level = 1;
	Q[rear] = T; 
	rear = (rear + 1) % MAXSIZE;

	while (front != rear)
	{
		p = Q[front];
		front = (front + 1) % MAXSIZE; 
		if (p->level == i)
			cout << p->data << " ";
		if (p->firstchild)
		{
			p->firstchild->level = p->level + 1;
			Q[rear] = p->firstchild;//����
			rear = (rear + 1) % MAXSIZE;
			p = p->firstchild;
			while (p->nextsibling)
			{//�������ֵ����
				p->nextsibling->level = p->level;
				Q[rear] = p->nextsibling;
				rear = (rear + 1) % MAXSIZE;
				p = p->nextsibling;
			}
		}
	}
}
int main()
{
	CSTree T = NULL;
	CreateCSTree(T);
	int n;
	cin >> n;
	OutputNodeOfLevel(T, n);
	return 0;
}
