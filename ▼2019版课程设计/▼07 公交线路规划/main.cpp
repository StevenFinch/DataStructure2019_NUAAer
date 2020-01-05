/*	Compiler: Visual Studio 2019
**	UpdateTime: 2019/12/27
**	ID: 161840225   */

/*
	����������˲ŷ���TaskOne��TaskTwo�еϽ�˹�����㷨���ֿ��Լ�����������������������Ϊ������ģ�飬���������߼���������
*/
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <map>
#include <algorithm>
#include <iomanip>

using namespace std;
const int inf = 99999;
struct stop
{
	int num;
	string name;
	string bus;
	stop(int num_, string name_, string bus_)
	{
		num = num_;
		name = name_;
		bus = bus_;
	}
};

vector<vector<stop>> rt;//����·����Ϣ
map<string, int> stophash;//���������Ϣ
map<int, vector<string>> stopbus;//�ܵ���վ��Ĺ���
int M[6000][6000];//�ڽӾ���

//���ļ��ж�ȡ��·��Ϣ
void InputRoutine(fstream& fin)
{
	string s;
	stringstream ss;
	string busname, stopname;

	while (fin.peek() != EOF)
	{
		int i = 0;
		vector<stop> r;

		getline(fin, s);
		ss << s;

		ss >> busname;
		r.push_back(stop(i++, busname, busname));//0��λ�ô洢��ʿ����

		while (ss)
		{
			getline(ss, stopname, ',');

			if (isascii(stopname[0]) && isspace(stopname[0]))
				stopname.erase(stopname.begin(), stopname.begin() + 1);//����ո�

			r.push_back(stop(i++, stopname, busname));//֮��ÿ��λ�ô洢վ���ż�����
		}
		rt.push_back(r);

		ss.clear();
		ss.str("");
	}
}

void OutputRoutine()
{
	int i, j;
	for (i = 0; i < rt.size(); i++)
	{
		for (j = 0; j < rt[i].size(); j++)
		{
			cout << rt[i][j].name << ' ' << rt[i][j].num << ' ';
		}
		cout << endl;
	}
}

//����վ�����Ƶ���ŵ�ӳ�䣬����վ�����Ƶ��ܹ�����վ��Ĺ�����ӳ��
void Init()
{
	//���
	int i, j;
	int k = 1;

	for (int i = 0; i < rt.size(); i++)
	{
		for (int j = 1; j < rt[i].size(); j++)
		{
			string name = rt[i][j].name;

			//map��û�и�վ�ļ�¼������б��
			if (stophash.find(name) == stophash.end())
			{
				stophash[name] = k++;
			}
			rt[i][j].num = stophash[name];

			stopbus[rt[i][j].num].push_back(rt[i][j].bus);
		}
	}
}

//��С���� �Ͻ�˹�����㷨
void CreateM1()
{
	int i, j, k;

	for (i = 1; i < stophash.size() + 1; i++)
	{
		for (j = 1; j < stophash.size() + 1; j++)
		{
			if (i != j)
			{
				M[i][j] = inf;
			}
			else
			{
				M[i][j] = 0;
			}
		}
	}

	for (i = 0; i < rt.size(); i++)
	{
		for (j = 1; j < rt[i].size() - 1; j++)
		{
			for (k = j + 1; k < rt[i].size(); k++)
			{
				M[rt[i][j].num][rt[i][k].num] = 1;
				M[rt[i][k].num][rt[i][j].num] = 1;
			}
		}
	}

}
bool TaskOne(string s1, string s2)
{
	CreateM1();//�����ڽӾ���

	int n = stophash.size();//վ������

	int* set = new int[n + 1];//�������
	int* dist = new int[n + 1];//��¼���������·��
	int* path = new int[n + 1];//��¼��һ������

	//��Ӧ����վ��ı��
	int v = stophash[s1];
	int u = stophash[s2];

	//վ�㲻����
	if (u < 1 || u > n || v < 1 || v > n)
	{
		return false;
	}
	int min, i, j, k;

	//��ʼ��������
	for (i = 1; i < n + 1; i++)
	{
		dist[i] = M[v][i];
		set[i] = 0;
		if (M[v][i] < inf)
			path[i] = v;
		else
			path[i] = -1;

	}
	set[v] = 1;
	path[v] = -1;

	//���Ĳ�����ÿ�δ�ʣ�ඥ����ѡ��һ�����㣬ͨ����������·����ͨ������ʣ�ඥ���·�����ǳ�����̵�
	for (i = 1; i < n; i++)
	{
		min = inf;
		for (j = 1; j < n + 1; j++)
		{
			if (set[j] == 0 && dist[j] < min)
			{
				k = j;
				min = dist[j];
			}
		}
		set[k] = 1;//�������·��

		//�ٴθ��£�������ǰ��ĳ�ʼ��
		for (j = 1; j < n + 1; j++)
		{
			if (set[j] == 0 && dist[j] > dist[k] + M[k][j])
			{
				dist[j] = dist[k] + M[k][j];
				path[j] = k;
			}
		}
	}
	//���Ĳ�������

	//�������,����ջ�������
	int* stack = new int[n];
	int top = -1;
	while (path[u] != -1)
	{
		stack[++top] = u;
		u = path[u];
	}
	stack[++top] = u;

	cout << left;
	cout << setw(20) << "��С����·��Ϊ:";
	while (top - 1 != -1)
	{
		int rnum = stack[top];
		int lnum = stack[top - 1];
		string bus;
		vector<string> bt;
		for (int i = 0; i < stopbus[rnum].size(); i++)
		{
			for (int j = 0; j < stopbus[lnum].size(); j++)
			{
				if (stopbus[rnum][i] == stopbus[lnum][j])
				{
					bt.push_back(stopbus[rnum][i]);
				}
			}
		}
		sort(bt.begin(), bt.end());
		bt.erase(unique(bt.begin(), bt.end()), bt.end());

		if (rnum != v)
			cout << setw(20) << "";
		for (int i = 0; i < bt.size(); i++)
		{
			cout << bt[i];
			if (i != bt.size() - 1)
				cout << " / ";
		}
		for (auto it = stophash.begin(); it != stophash.end(); it++)
		{
			if (it->second == rnum)
				cout << " " << it->first;
		}
		cout << " ->";
		for (auto it = stophash.begin(); it != stophash.end(); it++)
		{
			if (it->second == lnum)
				cout << " " << it->first;
		}
		cout << endl << endl;
		top--;
	}
	cout << endl;

	//�ͷŶ��ڴ�
	delete[] set;
	delete[] dist;
	delete[] path;
}

//���·�� �Ͻ�˹�����㷨
void CreateM2(string* from)
{
	int i, j, k;

	for (i = 1; i < stophash.size() + 1; i++)
	{
		for (j = 1; j < stophash.size() + 1; j++)
		{
			if (i != j)
				M[i][j] = inf;
			else
				M[i][j] = 0;
		}
	}

	for (i = 0; i < rt.size(); i++)
	{
		for (j = 1; j < rt[i].size() - 1; j++)
		{
			for (k = j + 1; k < rt[i].size(); k++)
			{
				int d = k - j;
				int d0 = M[rt[i][j].num][rt[i][k].num];

				if (d < d0)
				{
					M[rt[i][j].num][rt[i][k].num] = d;
					M[rt[i][k].num][rt[i][j].num] = d;

					//��ǰ�Ĺ���
					from[rt[i][j].num] = rt[i][0].name;
					from[rt[i][k].num] = rt[i][0].name;
				}
			}
		}
	}
}
bool TaskTwo(string s1, string s2)
{
	string* from = new string[stophash.size() + 1];//�������·���µ����վ��Ĺ���
	CreateM2(from);//�����ڽӾ���

	int n = stophash.size();//վ������

	int* set = new int[n + 1];//�������
	int* dist = new int[n + 1];//��¼���������·��
	int* path = new int[n + 1];//��¼��һ������

	//��Ӧ����վ��ı��
	int v = stophash[s1];
	int u = stophash[s2];

	//վ�㲻����
	if (u < 1 || u > n || v < 1 || v > n)
	{
		return false;
	}
	int min, i, j, k;

	//��ʼ��������
	for (i = 1; i < n + 1; i++)
	{
		dist[i] = M[v][i];
		set[i] = 0;
		if (M[v][i] < inf)
			path[i] = v;
		else
			path[i] = -1;

	}
	set[v] = 1;
	path[v] = -1;

	//���Ĳ�����ÿ�δ�ʣ�ඥ����ѡ��һ�����㣬ͨ����������·����ͨ������ʣ�ඥ���·�����ǳ�����̵�
	for (i = 1; i < n; i++)
	{
		min = inf;
		for (j = 1; j < n + 1; j++)
		{
			if (set[j] == 0 && dist[j] < min)
			{
				k = j;
				min = dist[j];
			}
		}
		set[k] = 1;//�������·��

		//�ٴθ��£�������ǰ��ĳ�ʼ��
		for (j = 1; j < n + 1; j++)
		{
			if (set[j] == 0 && dist[j] > dist[k] + M[k][j])
			{
				dist[j] = dist[k] + M[k][j];
				path[j] = k;
			}
		}
	}
	//���Ĳ�������

	//�������,����ջ�������
	int* stack = new int[n];
	int top = -1;
	while (path[u] != -1)
	{
		stack[++top] = u;
		u = path[u];
	}
	stack[++top] = u;

	cout << left;
	cout << setw(20) << "��̳˳�·��Ϊ:";
	while (top - 1 != -1)
	{
		int rnum = stack[top];
		int lnum = stack[top - 1];
		string bus;
		if (rnum != v)
			cout << setw(20) << "";
		cout << from[rnum] << "  ";
		for (auto it = stophash.begin(); it != stophash.end(); it++)
		{
			if (it->second == rnum)
				cout << it->first;
		}
		cout << " ->";
		for (auto it = stophash.begin(); it != stophash.end(); it++)
		{
			if (it->second == lnum)
				cout << " " << it->first;
		}
		cout << endl << endl;
		top--;
	}
	cout << endl;

	//�ͷŶ��ڴ�
	delete[] set;
	delete[] dist;
	delete[] path;
	return true;
}

int main()
{
	fstream fin("routine.txt");

	InputRoutine(fin);
	//OutputRoutine();

	Init();

	string s1, s2;
	while (true)
	{
		cout << "���������վ��";
		cin >> s1;//������ҵ԰վ

		cout << endl;

		cout << "�������յ�վ��";
		cin >> s2; //˫��·վ

		cout << endl;

		if (!TaskOne(s1, s2) || !TaskTwo(s1, s2))
			cout << "����������ȷ��վ������" << endl << endl;
	}
}