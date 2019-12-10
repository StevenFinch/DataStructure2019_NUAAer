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
{//查找关键字
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
int BSTInsert(BTNode*& bt, int key)//需要对指针bt进行修改，所以用引用型指针
{//对查找算法进行修改，来到空指针的时候将关键字插入即可
	if (bt == NULL)
	{//空指针说明找到插入位置，创建新节点进行插入
		bt = (BTNode*)malloc(sizeof(BTNode));
		if (NULL == bt)
			exit(OVERFLOW);
		bt->lchild = NULL;
		bt->rchild = NULL;
		bt->key = key;
		return 1;//插入成功
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
	cout << "随机序列：";
	for (i = 0; i < n; i++)
	{
		cout << key[i] << ' ';
	}
	cout << endl;

	BTNode* bt = (BTNode*)malloc(sizeof(BTNode));
	CreatBST(bt, key, n);
	cout << "排序序列：";
	BSTInOrderTraverse(bt);
	return 0;
}