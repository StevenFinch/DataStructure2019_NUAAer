/***************************************
 **   Filename£º mid number.cpp
 **
 **   Compiler:  Visual Studio 2019
 **
 **   StudentID: 1618*****
 **
 **   Name:      Steven
 **
 ***************************************/

#include<iostream>
#include<map>
using namespace std;
int main ()
{
	int n;
	cin >> n;
	map<int, int> M;//first: number, second: how many
	for(int i = 0; i < n; i++)
	{//input 
		int t;//temp
		cin >> t;
		M[t]++;
	}
	
	map<int, int>::iterator it = M.begin();
	int mid = (n + 1) / 2;//Attention, both odd and even are OK
	int counter = 0;//counter of the left and the right of the mid
	int left = 0;//total number of left side
	int right = 0;
	int ans;//answer
	for(it; it != M.end(); it++)
	{
		if(counter + it->second >= mid)
		{
			left = counter;
			counter = 0;//ready to be the right side counter 
			ans = it->first;
		} 
		else
		{
			counter += it->second;
		}
	}
	right = counter;
	if(left == right)
		cout << ans;
	else
		cout << "-1";
	return 0;	
} 
