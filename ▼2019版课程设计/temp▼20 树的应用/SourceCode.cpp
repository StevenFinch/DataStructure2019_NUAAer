/*	Compiler: Dev-C++
**	UpdateTime: 2019/12/12
**	ID: 161840225	*/

#include<bits/stdc++.h>
using namespace std;

map<string, string> json;

//从下标i开始，寻找键名或者键值，并去掉首尾的引号、中间的转义符号'\'
string get(int& i, string str) {
	string key;
	i++;
	while (i < str.size() && str[i] != '"') {
		//若遇到转义符号，则跳过一位
		if (str[i] == '\\')
		{
			key += str[++i];
		}
		else 
		{
			key += str[i];
		}
		i++;
	}
	return key;
}

// parent: 当前处理的json串的key
// str: 为尚未解析的字符串
// return: 本次解析的json串的长度
int parseJSON(string parent, string str)
{
	string key;
	for (int i = 0; i < str.size(); i++)
	{
		if (str[i] == '}') 
		{
			return i;
		}

		if (str[i] == ' ' || str[i] == ',') 
		{
			continue;
		}
		// 获取键名
		if (str[i] == '"')
		{
			key = get(i, str);
			continue;
		}
		// 获取键值
		if (str[i] == ':')
		{
			// 去掉可能存在的空格
			while (str[++i] == ' ');

			// 若值为字符串
			if (str[i] == '"') {
				string value = get(i, str);
				if (!parent.empty())
				{
					json[parent + '.' + key] = value;
				}
				else 
				{
					json[key] = value;
				}
				continue;
			}
			// 若值为对象
			// 去掉左花括号{后面可能存在的空格
			while (str[++i] == ' ');
			string newParent;
			if (!parent.empty()) 
			{
				newParent = parent + '.' + key;
			}
			else 
			{
				newParent = key;
			}
			// 用{}标记newParent的值为对象
			json[newParent] = "{}";
			// 解析子串
			i += parseJSON(newParent, str.substr(i));
		}
	}
	return str.size();
}

int main() 
{
	//读json
	fstream fin("text.txt");
	int n, m;
	fin >> n >> m;
	fin.get();

	string line;
	string str;
	while (n--) 
	{
		getline(fin, line);
		str += line;
	}
	parseJSON("", str);//处理json字符串

	//判断读入
	while (m--) 
	{
		fin >> line;
		if (!json.count(line)) 
		{
			cout << "NOTEXIST" << endl;
		}
		else if (json[line] == "{}") 
		{
			cout << "OBJECT" << endl;
		}
		else
		{
			cout << "STRING " << json[line] << endl;
		}
	}

	return 0;
}