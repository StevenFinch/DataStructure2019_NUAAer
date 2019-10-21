/***************************************
 **   Filename£∫ œ∞Ã‚3.31 ªÿŒƒ≈–∂œ.cpp
 **
 **   Compiler:  Visual Studio 2019
 **
 **   StudentID: 1618*****
 **
 **   Name:      Steven
 **
 ***************************************/
#include <iostream>
#include <stack>
#include <string>

using namespace std;

int main()
{
	string str;
	cin >> str;
	string str_r;
	stack<char> S;
	for (int i = 0; i < str.length(); i++)
	{
		S.push(str[i]);
	}
	while (!S.empty())
	{
		char t = S.top();
		str_r.push_back(t);
		S.pop();
	}
	cout << str << endl;
	cout << str_r << endl;
	str == str_r ? cout << "MATCH" : cout << "MISMATCH";
	return 0;
}