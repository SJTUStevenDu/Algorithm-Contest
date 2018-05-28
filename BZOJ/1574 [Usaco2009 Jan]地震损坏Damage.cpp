/*
DATE : 2012-12-28 
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

const int MAXV = 30000 + 5;
const int MAXE = 200000 + 5;

struct Edge
{
	int next,to;
} g[MAXE];
int start[MAXV],gn;

void AddEdge(int a,int b)
{
	gn++;g[gn].next=start[a];g[gn].to=b;start[a]=gn;
	gn++;g[gn].next=start[b];g[gn].to=a;start[b]=gn;
}

int n,m,ans,k;
int vis[MAXV];

void dfs(int p)
{
	for(int i=start[p];i;i=g[i].next)
	{
		if(!vis[g[i].to]) 
		{
			vis[g[i].to]=1;
			dfs(g[i].to);
		}
	}
}

int main()
{
	scanf("%d%d%d",&n,&m,&k);
	while(m--)
	{
		int a,b,c;
		scanf("%d%d",&a,&b);
		AddEdge(a,b);
	}
	while(k--)
	{
		int a;
		scanf("%d",&a);
		vis[a]=-1;
		for(int i=start[a];i;i=g[i].next) vis[g[i].to]=-1;
	}
	vis[1]=1;
	dfs(1);
	for(int i=1;i<=n;i++) if(vis[i]==1) ans++;
	ans=n-ans;
	printf("%d\n",ans);
	
	return 0;
}
