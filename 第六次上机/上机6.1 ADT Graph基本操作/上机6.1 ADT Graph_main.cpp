/***************************************
 **   Filename： 上机6.1 ADT Graph_main.cpp
 **
 **   Compiler:  Visual Studio 2019
 **
 **   StudentID: 1618*****
 **
 **   Name:      Steven
 **
 ***************************************/

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