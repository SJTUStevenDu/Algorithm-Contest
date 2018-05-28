/*
DATE : 2013-3-20 
RATING : 2
TAG : Math
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

//Orz WJMZBMR && sevenkplus

using namespace std;

const int MAXN = 10000 + 10;

struct Edge
{
	int next,to;
} g[MAXN*2];
int gn,start[MAXN];

inline void AddEdge(int a,int b)
{
	gn++;g[gn].next=start[a];start[a]=gn;g[gn].to=b;
	gn++;g[gn].next=start[b];start[b]=gn;g[gn].to=a;
}

int n,m,l;
int ans;
int dep[MAXN],num[MAXN];
bool vis[MAXN];

void dfs(int p)
{
	vis[p]=1;
	for(int i=start[p];i;i=g[i].next)
	{
		int v=g[i].to;
		if(vis[v]) continue;
		dep[v]=dep[p]+1;
		dfs(v);
	}
}

int main()
{
	scanf("%d%d%d",&n,&m,&l);
	for(int i=2;i<=n;i++) 
	{
		int a;
		scanf("%d%d",&a,&num[i]);
		num[i]%=(l+1);
		AddEdge(i,a);
	}
	dfs(1);
	for(int i=1;i<=n;i++) if(dep[i]&1) ans=ans^num[i];
	while(m--)
	{
		int a,b;
		scanf("%d%d",&a,&b);
		b%=(l+1);
		if(dep[a]&1)
		{
			ans^=num[a];
			num[a]=b;
			ans^=b;
		}
		if(!ans) printf("No\n");else printf("Yes\n");
	}
	
	return 0;
}
