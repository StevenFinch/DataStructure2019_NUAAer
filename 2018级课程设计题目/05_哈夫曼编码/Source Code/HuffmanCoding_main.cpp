#include"HuffmanCoding.h"
using namespace std;
int main()
{
	string s;
	cin >> s;
	HuffmanCoding huf(s);
	huf.Coding();
	return 0;
}