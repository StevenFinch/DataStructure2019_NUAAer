/*	Compiler: Visual Studio 2019
**	UpdateTime: 2019/11/14
**	ID: 161840225   */
#include"上机6.1 ADT Graph基本操作.h"
using namespace std;

int main()
{
	MGraph G;
	CreateGraph(&G);
	cout << "DFS: " << endl;
	DFSTraverse(G, 0);
	cout << endl;
	cout << "BFS: " << endl;
	BFSTraverse(G);
	return 0;
}