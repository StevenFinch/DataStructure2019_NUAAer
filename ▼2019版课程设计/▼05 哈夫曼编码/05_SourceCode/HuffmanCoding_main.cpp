/*	Compiler: Visual Studio 2019
**	UpdateTime: 2019/11/26
**	ID: 161840225   */

#include"HuffmanCoding.h"
using namespace std;
int main()
{
	string s;
	cout << "�������ѹ���ļ�������Ŀ¼�£�:  ";
	cin >> s;
	HuffmanCoding huf(s);
	huf.Coding();
	return 0;
}