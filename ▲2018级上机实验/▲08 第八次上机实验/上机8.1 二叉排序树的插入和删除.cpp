/*	Compiler: Visual Studio 2019
**	UpdateTime: 2019/12/10
**	ID: 161840225   */
#include<iostream>
#include<ctime>
using namespace std;
typedef struct BTNode
{
	int key;
	struct BTNode* lchild;
	struct BTNode* rchild;
}BTNode;
BTNode* BSTSearch(BTNode* bt, int key)
{//���ҹؼ���
	if (bt == NULL)
		return NULL;
	else
	{
		if (bt->key == key)
			return bt;
		else if (key < bt->key)
			return BSTSearch(bt->lchild, key);
		else
			return BSTSearch(bt->rchild, key);
	}
}
int BSTInsert(BTNode*& bt, int key)//��Ҫ��ָ��bt�����޸ģ�������������ָ��
{//�Բ����㷨�����޸ģ�������ָ���ʱ�򽫹ؼ��ֲ��뼴��
	if (bt == NULL)
	{//��ָ��˵���ҵ�����λ�ã������½ڵ���в���
		bt = (BTNode*)malloc(sizeof(BTNode));
		if (NULL == bt)
			exit(OVERFLOW);
		bt->lchild = NULL;
		bt->rchild = NULL;
		bt->key = key;
		return 1;//����ɹ�
	}
	else
	{
		if (bt->key == key)
			return 0;
		else if (key < bt->key)
			return BSTInsert(bt->lchild, key);
		else
			return BSTInsert(bt->rchild, key);
	}
}
void CreatBST(BTNode*& bt, int key[], int n)
{
	int i;
	bt = NULL;
	for (i = 0; i < n; i++)
	{
		BSTInsert(bt, key[i]);
	}
}
void BSTInOrderTraverse(BTNode* bt)
{
	if (bt)
	{
		BSTInOrderTraverse(bt->lchild);
		cout << bt->key << ' ';
		BSTInOrderTraverse(bt->rchild);
	}
}
int main()
{
	srand((unsigned)time(NULL));
	const int n = 10;
	int key[n];
	int i;
	for (i = 0; i < n; i++)
	{
		key[i] = rand() % 100;
	}
	cout << "������У�";
	for (i = 0; i < n; i++)
	{
		cout << key[i] << ' ';
	}
	cout << endl;

	BTNode* bt = (BTNode*)malloc(sizeof(BTNode));
	CreatBST(bt, key, n);
	cout << "�������У�";
	BSTInOrderTraverse(bt);
	return 0;
}