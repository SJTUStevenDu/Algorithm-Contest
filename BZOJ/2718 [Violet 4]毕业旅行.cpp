/*
DATE : 2013-3-18 
RATING : 2
TAG :
*/

#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <cstdlib>
#include <iomanip>
#include <cmath>
#include <vector>
#include <fstream>
#include <string>
#include <map>
#include <queue>

//Orz WJMZBMR && sevenkplus

using namespace std;

const int MAXN = 500 + 10;
const int MAXE = 100000 + 10;

struct Edge
{
	int next,to;
} G[MAXE],g[MAXE];
int gn,Gstart[MAXN],start[MAXN];

void FAddEdge(int a,int b)
{
	gn++;G[gn].to=b;G[gn].next=Gstart[a];Gstart[a]=gn;
}

void AddEdge(int a,int b)
{
	gn++;g[gn].to=b;g[gn].next=start[a];start[a]=gn;
}

int n,m,ans,Link[MAXN];
bool vis[MAXN];

void dfs(int p)
{
	vis[p]=1;
	for(int i=Gstart[p];i;i=G[i].next)
		if(!vis[G[i].to]) dfs(G[i].to);
}

bool Find(int p)
{
	for(int i=start[p];i;i=g[i].next)
	{
		int v=g[i].to;
		if(vis[v]) continue;
		vis[v]=1;
		if(!Link[v] || Find(Link[v]))
		{
			Link[v]=p;
			return true;
		}
	}
	return false;
}

int main()
{
	scanf("%d%d",&n,&m);
	while(m--)
	{
		int a,b;
		scanf("%d%d",&a,&b);
		FAddEdge(a,b);
	}
	for(int i=1;i<=n;i++) 
	{
		memset(vis,0,sizeof(vis));
		dfs(i);vis[i]=0;
		for(int j=1;j<=n;j++) 
			if(vis[j]) AddEdge(i,j);
	}
	for(int i=1;i<=n;i++)
	{
		memset(vis,0,sizeof(vis));
		if(Find(i)) ans++;
	}
	printf("%d\n",n-ans);
	
	return 0;
}
