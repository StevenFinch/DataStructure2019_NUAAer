/*	Compiler: Dev-C++
**	UpdateTime: 2019/12/12
**	ID: 161840225	*/

#include<bits/stdc++.h>
using namespace std;

map<string, string> json;

//���±�i��ʼ��Ѱ�Ҽ������߼�ֵ����ȥ����β�����š��м��ת�����'\'
string get(int& i, string str) {
	string key;
	i++;
	while (i < str.size() && str[i] != '"') {
		//������ת����ţ�������һλ
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

// parent: ��ǰ�����json����key
// str: Ϊ��δ�������ַ���
// return: ���ν�����json���ĳ���
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
		// ��ȡ����
		if (str[i] == '"')
		{
			key = get(i, str);
			continue;
		}
		// ��ȡ��ֵ
		if (str[i] == ':')
		{
			// ȥ�����ܴ��ڵĿո�
			while (str[++i] == ' ');

			// ��ֵΪ�ַ���
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
			// ��ֵΪ����
			// ȥ��������{������ܴ��ڵĿո�
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
			// ��{}���newParent��ֵΪ����
			json[newParent] = "{}";
			// �����Ӵ�
			i += parseJSON(newParent, str.substr(i));
		}
	}
	return str.size();
}

int main() 
{
	//��json
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
	parseJSON("", str);//����json�ַ���

	//�ж϶���
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