/*	Compiler: Visual Studio 2019
**	UpdateTime: 2019/12/10
**	ID: 161840225   */
#include<iostream>
#include<map>	
#include<vector>
#include<algorithm>
using namespace std;

typedef pair<int, int> PAIR;
typedef map<int, int> MAP;

bool compare(const PAIR& a, const PAIR& b)
{
	if (a.second == b.second)
		return a.first < b.first;
	else
		return a.second > b.second;
}

int main()
{
	MAP m;
	int n;
	cin >> n;
	int temp;
	for (int i = 0; i < n; i++)
	{
		cin >> temp;
		m[temp]++;
	}
	vector<PAIR> v(m.begin(), m.end());
	sort(v.begin(), v.end(), compare);
	for (auto it = v.begin(); it != v.end(); it++)
	{
		cout << it->first << ' ' << it->second <<endl;
	}
	return 0;
}