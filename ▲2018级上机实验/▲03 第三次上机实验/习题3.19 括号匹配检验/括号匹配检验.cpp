/*	Compiler: Visual Studio 2019
**	UpdateTime: 2019/10/07
**	ID: 161840225   */
#include <iostream>
#include <fstream>
#include <vector>
#include <stack>

using namespace std;
const bool RET_ERROR_EXTRA = false;
const bool RET_ERROR_NOTMATCH = false;
const bool RET_OK = true;
/*
不匹配情况有三种：1.正常错误即不能匹配正确的括号 2.前面已经匹配完，最终多出来了几个右括号 3.左括号多了，没有符合的右括号
*/
bool CheckBracketsMatching(vector<char>& V, stack<char>& S)
{
	vector<char>::iterator it = V.begin();
	bool tag = RET_OK;//标志位

	for (it; it != V.end(); it++)
	{
		switch (*it)
		{
		case('('):
		{
			S.push(*it);
			break;
		}
		case('['):
		{
			S.push(*it);
			break;
		}
		case('{'):
		{
			S.push(*it);
			break;
		}
		case(')'):
		{
			if (S.empty())//右括号多了，没得匹配
				tag = RET_ERROR_EXTRA;
			else if (S.top() != '(')//不匹配
				tag = RET_ERROR_NOTMATCH;
			else
				S.pop();
			break;
		}

		case(']'):
		{
			if (S.empty())//右括号多了，没得匹配
				tag = RET_ERROR_EXTRA;
			else if (S.top() != '[')//不匹配
				tag = RET_ERROR_NOTMATCH;
			else
				S.pop();
			break;
		}
		case('}'):
		{
			if (S.empty())//右括号多了，没得匹配
				tag = RET_ERROR_EXTRA;
			else if (S.top() != '{')//不匹配
				tag = RET_ERROR_NOTMATCH;
			else
				S.pop();
			break;
		}
		default:
			break;//其他字符
		}
	}
	if (!S.empty() && RET_OK == tag)//栈非空说明还有左括号
		return RET_ERROR_EXTRA;
	return tag;
}
int main()
{
	vector<char> V;//brackets
	stack<char> S;//brackets
	char b;//store bracket

	ifstream fin("brackets.txt");
	if (!fin)
		return -1;
	while (!fin.eof())
	{
		fin >> b;
		if (fin.fail())//放置最后一个字符读两遍
		{
			break;
		}
		V.push_back(b);
	}

	for (auto it = V.begin(); it != V.end(); it++)
	{
		cout << *it << ' ';
	}

	if (CheckBracketsMatching(V, S))
	{
		cout << "MATCH" << endl;
	}
	else
	{
		cout << "MISMATCH" << endl;
	}
	return 0;
}
