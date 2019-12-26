/*	Compiler: Dev-C++
**	UpdateTime: 2019/12/12
**	ID: 161840225  
**	Source: https://www.hegongshan.com/2018/06/06/ccf-csp-20180303/#more	*/

#include<iostream>
#include<vector>
#include<string>
#include<regex>
#include<fstream>
using namespace std;

typedef struct Node
{
	string rule;
	string name;
	Node(string _rule, string _name) 
	{
		rule = _rule;
		name = _name;
	}
} UrlMapping;
bool match(string url, UrlMapping urlmappings)
{
	smatch result;//匹配数组
	if (!regex_match(url, result, regex(urlmappings.rule)))
		return false;

	cout << urlmappings.name;
	for (int i = 1; i < result.size(); i++)
	{
		if (regex_match(result.str(i), regex("\\d+")))
		{
			cout << ' ' << stoi(result.str(i));//去掉前导0
		}
		else
		{
			cout << ' ' << result.str(i);
		}

	}
	cout << endl;
	return true;
}
int main()
{
	fstream fin("text.txt");
	int n, m;
	fin >> n >> m;
	vector<UrlMapping> mappings;
	string rule, name;
	while (n--) 
	{
		fin >> rule >> name;
		rule = regex_replace(rule, regex("<int>"), "(\\d+)");
		rule = regex_replace(rule, regex("<str>"), "([-\\w\\.]+)");
		rule = regex_replace(rule, regex("<path>"), "(.+)");
		mappings.push_back(UrlMapping(rule, name));
	}
	string url;
	while (m--)
	{
		fin >> url;
		bool find = false;
		for (int i = 0; i < mappings.size(); i++)
		{
			if (match(url, mappings[i]))
			{
				find = true;
				break;
			}
		}
		if (!find)
		{
			cout << 404 << endl;
		}
	}
	return 0;
}
