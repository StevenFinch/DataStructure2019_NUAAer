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