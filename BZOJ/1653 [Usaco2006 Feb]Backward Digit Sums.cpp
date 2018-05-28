/*
DATE : 2012-11-29 
RATING : 1
TAG : DFS
*/

#include <iostream>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <cmath>
#include <fstream>
#include <string>
#include <algorithm>
#include <iomanip>

using namespace std;

int n,sum;
int a[15];
int s[15][15];
bool vis[15],flag;

bool check()
{
	for(int i=1;i<=n;i++) s[1][i]=a[i];
	for(int i=2;i<=n;i++) 
		for(int j=1;j<=n-i+1;j++) s[i][j]=s[i-1][j+1]+s[i-1][j];
	if(s[n][1]==sum) return 1;else return 0;
}

void dfs(int deep)
{
	if(flag) return;
	if(deep>n) 
	{
		if(check())
		{
			for(int i=1;i<n;i++) cout<<a[i]<<' ';
			cout<<a[n]<<endl;
			flag=1;
		}
		return;
	}
	for(int i=1;i<=n;i++) 
		if(!vis[i]) 
		{
			vis[i]=1;
			a[deep]=i;
			dfs(deep+1);
			vis[i]=0;
		}
	return;
}

int main()
{
	cin>>n>>sum;
	dfs(1);
	return 0;
}
