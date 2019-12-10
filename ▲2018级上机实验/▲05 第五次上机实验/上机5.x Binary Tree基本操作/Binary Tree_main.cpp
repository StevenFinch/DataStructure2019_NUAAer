/*	Compiler: Visual Studio 2019
**	UpdateTime: 2019/11/07
**	ID: 161840225   */
#include"�ϻ�5.1 Binary Tree��������.h"
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
	//�ݹ����
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

	//�ǵݹ����
	cout << setw(40) << "4.PreOrderTraverse_nonrecursion: ";
	PreOrderTraverse_nonr(T);
	cout << setw(40) << endl;

	cout << setw(40) << "5.InOrderTraverse_nonrecursion: ";
	InOrderTraverse_nonr(T);
	cout << setw(40) << endl;

	cout << setw(40) << "6.PostOrderTraverse_nonrecursion: ";
	PostOrderTraverse_nonr(T);
	cout << setw(40) << endl;

	//���������ѭ�����У�
	cout << setw(40) << "7.LevelOrderTraverse: ";
	LevelOrderTraverse(T);
	cout << setw(40) << endl;

}
int main()
{
	//����
	BinTree T = NULL;
	ifstream fin("Binary Tree.txt");
	if (!fin)
		exit(OVERFLOW);
	CreateBinTree(fin, T);
	fin.close();

	//���������
	cout << "Depth: " << BinTreeDepth(T) << endl;
	
	//�����������
	cout << "Width: " << BinTreeWidth(T) << endl;

	//p��㼰���ֵ����ֵ�
	BinNode* p = LocateBinNode(T, 'B');
	cout << "Data: " << p->data << endl;
	cout << "LeftChild: " << LeftChild(T, 'B') << endl;
	cout << "RightChild: " << RightChild(T, 'B') << endl;
	cout << "RightSibling: " << RightSibling(T, 'B') << endl;
	cout << "LeftSibling: " << LeftSibling(T, 'E') << endl;

	//����Ԫ��
	BinTree Ti = NULL;
	ifstream fin1("Binary Tree.txt");
	CreateBinTree(fin1, Ti);
	InsertBiTree(T, 'F', Ti, 0);
	TraverseBinTree(T);

	//ɾ��Ԫ��
	DeleteBiTree(T, 'F', 0);
	TraverseBinTree(T);

	if (!IsCompleteBinaryTree(T))
		cout << "Not" << endl;
	return 0;
}