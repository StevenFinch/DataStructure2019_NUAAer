/*	Compiler: Visual Studio 2019
**	UpdateTime: 2019/12/16
**	ID: 161840225   */
#include <iostream>
#include <fstream>
#include <iomanip>
#include <algorithm>
using namespace std;
const int MAX_N = 10;//max vertex in array
const int MAX_E = 11;

//Prim
struct Graph_P
{
	struct vertex
	{
		int num;
		string name;
	}v[MAX_N];
	float w[MAX_N][MAX_N];
	int n;//vertex
};
struct edge
{
	int v;
	float w;
};
void CreateGraph_P(Graph_P& G)
{
	fstream fin("Graph.txt");
	if (!fin)
	{
		cout << "file failed" << endl;
		exit(1);
	}
	int i, j;
	float k;
	fin >> G.n;//vertex number
	if (G.n > MAX_N)
		exit(OVERFLOW);
	for (i = 0; i < G.n; i++)
	{
		fin >> G.v[i].name;
		G.v[i].num = i;
	}
	for (i = 0; i < MAX_N; i++)
	{
		for (j = 0; j < MAX_N; j++)
		{
			G.w[i][j] = FLT_MAX;
		}
	}
	while (!fin.eof())
	{
		fin >> i >> j >> k;
		G.w[i][j] = G.w[j][i] = k;
	}
	fin.close();
}
void Prim(const Graph_P& G, int v0, float& c)
{//v0: beginning vertex, c: lowest cost
	edge lowcost[MAX_N];
	int vset[MAX_N];//vertex set
	int i, j;
	c = 0;
	for (i = 0; i < G.n; i++)
	{
		lowcost[i].v = v0;
		lowcost[i].w = G.w[v0][i];
		vset[i] = 0;
	}
	vset[v0] = 1;//visited

	cout << "Prim算法" << endl;
	cout << "  1.该最小生成树各边为: ";
	for (i = 0; i < G.n - 1; i++)
	{
		float min = FLT_MAX;
		int k;
		for (j = 0; j < G.n; j++)
		{
			if (vset[j] == 0 && lowcost[j].w < min)
			{
				k = j;
				min = lowcost[j].w;
			}
		}
		cout << G.v[lowcost[k].v].name << ' ' << G.v[k].name << "   ";
		vset[k] = 1;
		c += min;
		for (j = 0; j < G.n; j++)
		{
			if (vset[j] == 0 && G.w[k][j] < lowcost[j].w)
			{
				lowcost[j].w = G.w[k][j];
				lowcost[j].v = k;
			}
		}
	}
	cout << endl << "  2.该最小生成树权值为: ";
	cout << c << endl;
}

//Kruskal
struct Road
{
	int a, b;
	float w;
};
struct Graph_K
{
	struct vertex
	{
		int num;
		string name;
	}v[MAX_N];
	Road road[MAX_E];
	int n;//vertex
	int e;//edge
};
void CreateGraph_K(Graph_K& G)
{
	fstream fin("Graph.txt");
	if (!fin)
	{
		cout << "file failed" << endl;
		exit(1);
	}
	int i, j;
	float k;
	fin >> G.n;//vertex number
	G.e = 0;
	if (G.n > MAX_N)
		exit(OVERFLOW);
	for (i = 0; i < G.n; i++)
	{
		fin >> G.v[i].name;
		G.v[i].num = i;
	}
	i = 0;
	while (!fin.eof())
	{
		fin >> G.road[i].a >> G.road[i].b >> G.road[i].w;
		i++;
		G.e++;
	}
	fin.close();
}
int getRoot(int Father[], int a)
{
	while (a != Father[a])
		a = Father[a];
	return a;
}
void Kruskal(Graph_K& G, float& c)
{
	int Father[MAX_E];
	int i, j;
	int ra, rb;
	for (i = 0; i < G.n; i++)
	{//初始化并查集
		Father[i] = i;
	}
	for (i = G.e - 1; i >= 1; i--)
	{//按边数由小到大排列
		Road temp;
		for (j = 1; j <= i; j++)
		{
			if (G.road[j].w < G.road[j - 1].w)
			{
				temp = G.road[j - 1];
				G.road[j - 1] = G.road[j];
				G.road[j] = temp;
			}
		}
	}

	cout << "Kruskal算法" << endl;
	cout << "  1.该最小生成树各边为: ";
	c = 0;
	for (i = 0; i < G.e; i++)
	{
		ra = getRoot(Father, G.road[i].a);
		rb = getRoot(Father, G.road[i].b);
		if (ra != rb)
		{
			Father[ra] = rb;
			c += G.road[i].w;
			cout << G.v[G.road[i].a].name << ' ' <<G.v[G.road[i].b].name << "   ";
		}
	}
	cout << endl << "  2.该最小生成树权值为: " << c << endl;
}

int main()
{
	float c;

	char choice;
	bool flag = 1;
	cout << "请输入您将使用的算法（A.Prim   B.Kruskal）: ";
	cin >> choice;
	while (flag)
	{
		switch (choice)
		{
		case'A':
		{
			Graph_P G_P;
			CreateGraph_P(G_P);
			Prim(G_P, 0, c);
			flag = 0;
			break;
		}
		case'B':
		{
			Graph_K G_K;
			CreateGraph_K(G_K);
			Kruskal(G_K, c);
			flag = 0;
			break;
		}
		default:
			cin >> choice;
		}
	}
	return 0;
}