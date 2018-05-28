/*
DATE : 2013-2-8 
RATING : 2
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

//Orz WJMZBMR && sevenkplus

using namespace std;

const int MAXE = 10000 + 5;
const int MAXN = 1000 + 5;

struct Edge
{
	int next,to;
} g[MAXE];
int start[MAXN],gn;

void AddEdge(int a,int b)
{
	gn++;g[gn].to=b;g[gn].next=start[a];start[a]=gn;
}

struct rEdge
{
	int next,to;
} rg[MAXE];
int rstart[MAXN],rgn;

void rAddEdge(int a,int b)
{
	rgn++;rg[rgn].to=b;rg[rgn].next=rstart[a];rstart[a]=gn;
}

int n,m,ans;
bool vis[MAXN];

void dfs(int v)
{
	vis[v]=1;
	for(int i=start[v];i;i=g[i].next) if(!vis[g[i].to]) dfs(g[i].to);
}

void rdfs(int v)
{
	vis[v]=1;
	for(int i=rstart[v];i;i=rg[i].next) if(!vis[rg[i].to]) rdfs(rg[i].to);
}

int main()
{
	scanf("%d%d",&n,&m);
	while(m--)
	{
		int a,b;
		scanf("%d%d",&a,&b);
		AddEdge(a,b);
		rAddEdge(b,a);
	}
	for(int i=1;i<=n;i++)
	{
		memset(vis,0,sizeof(vis));
		dfs(i);
		rdfs(i);
		for(int j=1;j<=n;j++) if(!vis[j]) ans++;
	}
	printf("%d\n",ans/2);
	
	return 0;
}
