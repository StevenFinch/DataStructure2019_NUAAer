/*	Compiler: Visual Studio 2019
**	UpdateTime: 2019/12/16
**	ID: 161840225   */

#include<bits/stdc++.h>
using namespace std;

const char opt[] = { '+', '-', '*', '/', '#' };

//运算符优先级
char table[8][8] = {
	{ ' ', '+', '-', '*', '/', '(', ')', '#' },
	{ '+', '>', '>', '<', '<', '<', '>', '<' },
	{ '-', '>', '>', '<', '<', '<', '>', '<' },
	{ '*', '>', '>', '>', '>', '<', '>', '<' },
	{ '/', '>', '>', '>', '>', '<', '>', '<' },
	{ '(', '<', '<', '<', '<', '<', '=', ' ' },
	{ ')', '>', '>', '>', '>', ' ', '>', '<' },
	{ '#', '>', '>', '>', '>', '>', ' ', '=' }
};

//清除表达式中的空白字符
string ClearSpace(string str)
{
	string tmp;

	int i = 0;
	int j = 0;

	while (i < str.length())
	{
		if (str[i] == ' ')
		{
			++i;
			continue;
		}
		tmp.push_back(str[i++]);
	}
	return tmp;
}

//分离操作符和操作数
vector<string> SeperateStr(string str)
{
	string tmp = "";
	vector<string> exp;
	vector<string> res;

	for (int i = 0; i < str.length(); ++i)
	{
		//收集数字
		if (isdigit(str[i]) || str[i] == '.')
		{
			tmp += str[i];
		}

		//遇到运算符
		else
		{
			//第一个字符就是运算符
			if (i == 0)
			{
				tmp = str[i];
				exp.push_back(tmp);
			}
			else
			{
				//把收集到的数字加入exp
				exp.push_back(tmp);

				//把当前运算符加入exp
				tmp = str[i];
				exp.push_back(tmp);//把非数字加入exp 
			}
			tmp = "";
		}
	}

	//处理最后一组数字
	if (tmp.size() > 0)
	{
		exp.push_back(tmp);
	}

	//处理'-'
	for (int i = 0; i < exp.size(); ++i)
	{
		if (exp[i] == "-")
		{
			if (i > 0 && (isdigit(exp[i - 1][0]) || exp[i - 1] == ")"))
				res.push_back(exp[i]);//减号
			else
				res.push_back("#");//负号 
		}
		else
		{
			res.push_back(exp[i]);
		}
	}

	return res;
}

//比较运算符优先级
char CompareOpt(char a, char b)
{
	int i, j;
	for (j = 0; j < 8; ++j)
	{
		if (table[0][j] == b)
			break;
	}

	for (i = 0; i < 8; ++i)
	{
		if (table[i][0] == a)
			break;
	}
	return table[i][j];
}

//判断是否为运算符
bool IsOpt(char c)
{
	for (int i = 0; i < 5; ++i)
	{
		if (c == opt[i])
			return true;
	}
	return false;
}

//运算
void Calculate(stack<double>& opdSt, char opt)
{
	double res;
	double opd, lOpd, rOpd;
	switch (opt)
	{
	case'#':
		opd = opdSt.top();
		opdSt.pop();
		res = 0 - opd;
		opdSt.push(res);
		break;

	case'+':
		rOpd = opdSt.top();
		opdSt.pop();
		lOpd = opdSt.top();
		opdSt.pop();
		res = lOpd + rOpd;
		opdSt.push(res);
		break;

	case'-':
		rOpd = opdSt.top();
		opdSt.pop();
		lOpd = opdSt.top();
		opdSt.pop();
		res = lOpd - rOpd;
		opdSt.push(res);
		break;

	case'*':
		rOpd = opdSt.top();
		opdSt.pop();
		lOpd = opdSt.top();
		opdSt.pop();
		res = lOpd * rOpd;
		opdSt.push(res);
		break;

	case'/':
		rOpd = opdSt.top();
		opdSt.pop();
		lOpd = opdSt.top();
		opdSt.pop();
		res = lOpd * (1.0) / rOpd;
		opdSt.push(res);
		break;

	default:
		break;
	}

}

//检查输入是否合法
bool CheckStr(string str)
{
	for (int i = 0; i < str.size(); ++i)
	{
		if (str[i] > 127 || str[i] < 0)
			return false;
		else if (IsOpt(str[i]) || isdigit(str[i]) || str[i] == '.' || str[i] == '(' || str[i] == ')')
			continue;
		else
			return false;
	}
}

//显示栈的变化过程
void PrintStack(stack<double> opdSt, stack<string> optSt)
{
	cout << "操作数栈为： ";
	while (opdSt.size())
	{
		cout << opdSt.top() << ' ';
		opdSt.pop();
	}
	cout << endl;

	cout << "操作符栈为： ";
	while (optSt.size())
	{
		cout << optSt.top() << ' ';
		optSt.pop();
	}
	cout << endl << endl;
}

//栈操作
double CalExpress(string str)
{
	vector<string> exp = SeperateStr(str);

	stack<double> opdSt;//运算数栈
	stack<string> optSt;//运算符栈

	string topOpt;

	for (int i = 0; i < exp.size(); ++i)
	{
		string c = exp[i];

		if (IsOpt(c[0]))
		{
			//空栈则压栈
			if (optSt.size() == 0)
			{
				optSt.push(c);
				PrintStack(opdSt, optSt);
			}

			else
			{
				string topOpt = optSt.top();

				if (CompareOpt(topOpt[0], c[0]) == '>')//栈顶优先级不小于当前优先级
				{
					while (CompareOpt(topOpt[0], c[0]) == '>')
					{
						optSt.pop();
						PrintStack(opdSt, optSt);

						Calculate(opdSt, topOpt[0]);
						PrintStack(opdSt, optSt);

						if (optSt.size() > 0)
						{
							topOpt = optSt.top();
						}
						else
						{
							break;
						}
					}
					//当前运算符入栈
					optSt.push(c);
					PrintStack(opdSt, optSt);
				}

				else//栈顶优先级大于当前优先级
				{
					optSt.push(c);
					PrintStack(opdSt, optSt);
				}
			}//end else
		}//end if
		else if (c == "(")
		{
			optSt.push(c);
			PrintStack(opdSt, optSt);
		}
		else if (c == ")")
		{
			topOpt = optSt.top();

			while (topOpt != "(")
			{
				Calculate(opdSt, topOpt[0]);
				PrintStack(opdSt, optSt);

				optSt.pop();
				PrintStack(opdSt, optSt);

				topOpt = optSt.top();
			}
			optSt.pop();//左括号出栈
			PrintStack(opdSt, optSt);
		}
		else//操作数 
		{
			opdSt.push(atof(c.c_str()));
			PrintStack(opdSt, optSt);
		}
	}

	//处理剩余
	while (!optSt.empty())
	{
		topOpt = optSt.top();

		Calculate(opdSt, topOpt[0]);
		PrintStack(opdSt, optSt);

		optSt.pop();
		PrintStack(opdSt, optSt);
	}

	return opdSt.top();
}

int main()
{
	string str;

	cout << "请输入运算表达式: ";

	while (getline(cin, str))
	{
		cout << endl;
		string res = ClearSpace(str);

		if (!CheckStr(res))
		{
			cout << "算数表达式非法，请检查是否含有中文字符等非法字符。" << endl << endl;
			cout << "请输入运算表达式: ";
			continue;
		}

		cout << "该表达式结果为：  " << str.c_str() << '=' << CalExpress(str) << endl << endl;
		cout << "请输入运算表达式: ";
	}

	return 0;
}