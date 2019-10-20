  
/***************************************
 **   Filename�� ����ƥ�����.cpp
 **
 **   Compiler:  Visual Studio 2019
 **
 **   StudentID: 1618*****
 **
 **   Name:      Steven
 **
 ***************************************/
#include <iostream>
#include <fstream>
#include <vector>
#include <stack>

using namespace std;
const bool RET_ERROR_EXTRA = false;
const bool RET_ERROR_NOTMATCH = false;
const bool RET_OK = true;
bool CheckBracketsMatching(vector<char>& V, stack<char>& S)
{
	vector<char>::iterator it = V.begin();
	bool tag = RET_OK;//��־λ

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
			if (S.empty())//�����Ŷ��ˣ�û��ƥ��
				tag = RET_ERROR_EXTRA;
			else if (S.top() != '(')//��ƥ��
				tag = RET_ERROR_NOTMATCH;
			else
				S.pop();
			break;
		}

		case(']'):
		{
			if (S.empty())//�����Ŷ��ˣ�û��ƥ��
				tag = RET_ERROR_EXTRA;
			else if (S.top() != '[')//��ƥ��
				tag = RET_ERROR_NOTMATCH;
			else
				S.pop();
			break;
		}
		case('}'):
		{
			if (S.empty())//�����Ŷ��ˣ�û��ƥ��
				tag = RET_ERROR_EXTRA;
			else if (S.top() != '{')//��ƥ��
				tag = RET_ERROR_NOTMATCH;
			else
				S.pop();
			break;
		}
		default:
			break;//�����ַ�
		}
	}
	if (!S.empty() && RET_OK == tag)//ջ�ǿ�˵������������
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
		if (fin.fail())//�������һ���ַ�������
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