/*	Compiler: Visual Studio 2019
**	UpdateTime: 2019/12/16
**	ID: 161840225   */

#include<bits/stdc++.h>
using namespace std;

const char opt[] = { '+', '-', '*', '/', '#' };

//��������ȼ�
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

//������ʽ�еĿհ��ַ�
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

//����������Ͳ�����
vector<string> SeperateStr(string str)
{
	string tmp = "";
	vector<string> exp;
	vector<string> res;

	for (int i = 0; i < str.length(); ++i)
	{
		//�ռ�����
		if (isdigit(str[i]) || str[i] == '.')
		{
			tmp += str[i];
		}

		//���������
		else
		{
			//��һ���ַ����������
			if (i == 0)
			{
				tmp = str[i];
				exp.push_back(tmp);
			}
			else
			{
				//���ռ��������ּ���exp
				exp.push_back(tmp);

				//�ѵ�ǰ���������exp
				tmp = str[i];
				exp.push_back(tmp);//�ѷ����ּ���exp 
			}
			tmp = "";
		}
	}

	//�������һ������
	if (tmp.size() > 0)
	{
		exp.push_back(tmp);
	}

	//����'-'
	for (int i = 0; i < exp.size(); ++i)
	{
		if (exp[i] == "-")
		{
			if (i > 0 && (isdigit(exp[i - 1][0]) || exp[i - 1] == ")"))
				res.push_back(exp[i]);//����
			else
				res.push_back("#");//���� 
		}
		else
		{
			res.push_back(exp[i]);
		}
	}

	return res;
}

//�Ƚ���������ȼ�
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

//�ж��Ƿ�Ϊ�����
bool IsOpt(char c)
{
	for (int i = 0; i < 5; ++i)
	{
		if (c == opt[i])
			return true;
	}
	return false;
}

//����
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

//��������Ƿ�Ϸ�
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

//��ʾջ�ı仯����
void PrintStack(stack<double> opdSt, stack<string> optSt)
{
	cout << "������ջΪ�� ";
	while (opdSt.size())
	{
		cout << opdSt.top() << ' ';
		opdSt.pop();
	}
	cout << endl;

	cout << "������ջΪ�� ";
	while (optSt.size())
	{
		cout << optSt.top() << ' ';
		optSt.pop();
	}
	cout << endl << endl;
}

//ջ����
double CalExpress(string str)
{
	vector<string> exp = SeperateStr(str);

	stack<double> opdSt;//������ջ
	stack<string> optSt;//�����ջ

	string topOpt;

	for (int i = 0; i < exp.size(); ++i)
	{
		string c = exp[i];

		if (IsOpt(c[0]))
		{
			//��ջ��ѹջ
			if (optSt.size() == 0)
			{
				optSt.push(c);
				PrintStack(opdSt, optSt);
			}

			else
			{
				string topOpt = optSt.top();

				if (CompareOpt(topOpt[0], c[0]) == '>')//ջ�����ȼ���С�ڵ�ǰ���ȼ�
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
					//��ǰ�������ջ
					optSt.push(c);
					PrintStack(opdSt, optSt);
				}

				else//ջ�����ȼ����ڵ�ǰ���ȼ�
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
			optSt.pop();//�����ų�ջ
			PrintStack(opdSt, optSt);
		}
		else//������ 
		{
			opdSt.push(atof(c.c_str()));
			PrintStack(opdSt, optSt);
		}
	}

	//����ʣ��
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

	cout << "������������ʽ: ";

	while (getline(cin, str))
	{
		cout << endl;
		string res = ClearSpace(str);

		if (!CheckStr(res))
		{
			cout << "�������ʽ�Ƿ��������Ƿ��������ַ��ȷǷ��ַ���" << endl << endl;
			cout << "������������ʽ: ";
			continue;
		}

		cout << "�ñ��ʽ���Ϊ��  " << str.c_str() << '=' << CalExpress(str) << endl << endl;
		cout << "������������ʽ: ";
	}

	return 0;
}