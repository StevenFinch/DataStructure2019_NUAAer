/*	Compiler: Visual Studio 2019
**	UpdateTime: 2019/11/07
**	ID: 161840225   */
#include"上机5.1 Binary Tree基本操作.h"
using namespace std;
/*
            A
		  /   \
		B      C
	  /  \    /  \
	 D    E  F    G
	/ \      \
   H   I      J

*/
void TraverseBinTree(BinTree T)
{
	//递归遍历
	cout << left;
	cout << setw(40) << "1.PreOrderTraverse_recursion: ";
	PreOrderTraverse_r(T);
	cout << setw(40) << endl;

	cout << setw(40) << "2.InOrderTraverse_recursion: ";
	InOrderTraverse_r(T);
	cout << setw(40) << endl;

	cout << setw(40) << "3.PostOrderTraverse_recursion: ";
	PostOrderTraverse_r(T);
	cout << setw(40) << endl;

	//非递归遍历
	cout << setw(40) << "4.PreOrderTraverse_nonrecursion: ";
	PreOrderTraverse_nonr(T);
	cout << setw(40) << endl;

	cout << setw(40) << "5.InOrderTraverse_nonrecursion: ";
	InOrderTraverse_nonr(T);
	cout << setw(40) << endl;

	cout << setw(40) << "6.PostOrderTraverse_nonrecursion: ";
	PostOrderTraverse_nonr(T);
	cout << setw(40) << endl;

	//中序遍历（循环队列）
	cout << setw(40) << "7.LevelOrderTraverse: ";
	LevelOrderTraverse(T);
	cout << setw(40) << endl;

}
int main()
{
	//建树
	BinTree T = NULL;
	ifstream fin("Binary Tree.txt");
	if (!fin)
		exit(OVERFLOW);
	CreateBinTree(fin, T);
	fin.close();

	//二叉树深度
	cout << "Depth: " << BinTreeDepth(T) << endl;
	
	//二叉树最大宽度
	cout << "Width: " << BinTreeWidth(T) << endl;

	//p结点及左兄弟右兄弟
	BinNode* p = LocateBinNode(T, 'B');
	cout << "Data: " << p->data << endl;
	cout << "LeftChild: " << LeftChild(T, 'B') << endl;
	cout << "RightChild: " << RightChild(T, 'B') << endl;
	cout << "RightSibling: " << RightSibling(T, 'B') << endl;
	cout << "LeftSibling: " << LeftSibling(T, 'E') << endl;

	//插入元素
	BinTree Ti = NULL;
	ifstream fin1("Binary Tree.txt");
	CreateBinTree(fin1, Ti);
	InsertBiTree(T, 'F', Ti, 0);
	TraverseBinTree(T);

	//删除元素
	DeleteBiTree(T, 'F', 0);
	TraverseBinTree(T);

	if (!IsCompleteBinaryTree(T))
		cout << "Not" << endl;
	return 0;
}