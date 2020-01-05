/*	Compiler: Visual Studio 2019
**	UpdateTime: 2019/12/27
**	ID: 161840225   */

/*
	这道题做完了才发现TaskOne和TaskTwo中迪杰斯特拉算法部分可以继续抽象出来，将输出部分作为第三个模块，这样代码逻辑会更清楚。
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

vector<vector<stop>> rt;//公交路线信息
map<string, int> stophash;//公交编号信息
map<int, vector<string>> stopbus;//能到该站点的公交
int M[6000][6000];//邻接矩阵

//从文件中读取线路信息
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
		r.push_back(stop(i++, busname, busname));//0号位置存储巴士名称

		while (ss)
		{
			getline(ss, stopname, ',');

			if (isascii(stopname[0]) && isspace(stopname[0]))
				stopname.erase(stopname.begin(), stopname.begin() + 1);//清除空格

			r.push_back(stop(i++, stopname, busname));//之后每个位置存储站点编号及名称
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

//建立站点名称到编号的映射，建立站点名称到能够到该站点的公交的映射
void Init()
{
	//编号
	int i, j;
	int k = 1;

	for (int i = 0; i < rt.size(); i++)
	{
		for (int j = 1; j < rt[i].size(); j++)
		{
			string name = rt[i][j].name;

			//map中没有该站的记录，则进行编号
			if (stophash.find(name) == stophash.end())
			{
				stophash[name] = k++;
			}
			rt[i][j].num = stophash[name];

			stopbus[rt[i][j].num].push_back(rt[i][j].bus);
		}
	}
}

//最小换乘 迪杰斯特拉算法
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
	CreateM1();//建立邻接矩阵

	int n = stophash.size();//站点总数

	int* set = new int[n + 1];//标记数组
	int* dist = new int[n + 1];//记录到各点最短路径
	int* path = new int[n + 1];//记录上一个顶点

	//对应两个站点的编号
	int v = stophash[s1];
	int u = stophash[s2];

	//站点不存在
	if (u < 1 || u > n || v < 1 || v > n)
	{
		return false;
	}
	int min, i, j, k;

	//初始化各数组
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

	//核心操作：每次从剩余顶点中选出一个顶点，通往这个顶点的路径在通往所有剩余顶点的路径中是长度最短的
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
		set[k] = 1;//并入最短路径

		//再次更新，类似于前面的初始化
		for (j = 1; j < n + 1; j++)
		{
			if (set[j] == 0 && dist[j] > dist[k] + M[k][j])
			{
				dist[j] = dist[k] + M[k][j];
				path[j] = k;
			}
		}
	}
	//核心操作结束

	//输出操作,利用栈逆序输出
	int* stack = new int[n];
	int top = -1;
	while (path[u] != -1)
	{
		stack[++top] = u;
		u = path[u];
	}
	stack[++top] = u;

	cout << left;
	cout << setw(20) << "最小换乘路线为:";
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

	//释放堆内存
	delete[] set;
	delete[] dist;
	delete[] path;
}

//最短路径 迪杰斯特拉算法
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

					//当前的公交
					from[rt[i][j].num] = rt[i][0].name;
					from[rt[i][k].num] = rt[i][0].name;
				}
			}
		}
	}
}
bool TaskTwo(string s1, string s2)
{
	string* from = new string[stophash.size() + 1];//保存最短路径下到达该站点的公交
	CreateM2(from);//建立邻接矩阵

	int n = stophash.size();//站点总数

	int* set = new int[n + 1];//标记数组
	int* dist = new int[n + 1];//记录到各点最短路径
	int* path = new int[n + 1];//记录上一个顶点

	//对应两个站点的编号
	int v = stophash[s1];
	int u = stophash[s2];

	//站点不存在
	if (u < 1 || u > n || v < 1 || v > n)
	{
		return false;
	}
	int min, i, j, k;

	//初始化各数组
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

	//核心操作：每次从剩余顶点中选出一个顶点，通往这个顶点的路径在通往所有剩余顶点的路径中是长度最短的
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
		set[k] = 1;//并入最短路径

		//再次更新，类似于前面的初始化
		for (j = 1; j < n + 1; j++)
		{
			if (set[j] == 0 && dist[j] > dist[k] + M[k][j])
			{
				dist[j] = dist[k] + M[k][j];
				path[j] = k;
			}
		}
	}
	//核心操作结束

	//输出操作,利用栈逆序输出
	int* stack = new int[n];
	int top = -1;
	while (path[u] != -1)
	{
		stack[++top] = u;
		u = path[u];
	}
	stack[++top] = u;

	cout << left;
	cout << setw(20) << "最短乘车路线为:";
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

	//释放堆内存
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
		cout << "请输入起点站：";
		cin >> s1;//定坊工业园站

		cout << endl;

		cout << "请输入终点站：";
		cin >> s2; //双龙路站

		cout << endl;

		if (!TaskOne(s1, s2) || !TaskTwo(s1, s2))
			cout << "输入有误，请确认站点名称" << endl << endl;
	}
}