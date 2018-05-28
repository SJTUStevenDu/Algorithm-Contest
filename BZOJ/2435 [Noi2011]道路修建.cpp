#include <iostream>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <cmath>

using namespace std;

const int MAXN = 1000000 + 10;

struct Edge
{
	int next,to;
}g[MAXN*2];
int gn,start[MAXN];

int dep[MAXN],n,sz[MAXN],u[MAXN],v[MAXN],w[MAXN];
long long ans;
bool vis[MAXN];

inline void AddEdge(int a,int b)
{
	gn++;g[gn].to=b;g[gn].next=start[a];start[a]=gn;
	gn++;g[gn].to=a;g[gn].next=start[b];start[b]=gn;
}

void dfs(int p)
{
	vis[p]=1;
	sz[p]=1;
	for(int i=start[p];i;i=g[i].next)
	{
		if(!vis[g[i].to]) 
		{
			dep[g[i].to]=dep[p]+1;
			dfs(g[i].to);
			sz[p]+=sz[g[i].to];
		}
	}
}

int main()
{
	scanf("%d",&n);
	for(int i=1;i<n;i++)
	{
		scanf("%d%d%d",&u[i],&v[i],&w[i]);
		AddEdge(u[i],v[i]);
	}
	dfs(1);
	for(int i=1;i<n;i++)
	{
		if(dep[u[i]]>dep[v[i]]) swap(u[i],v[i]);
		ans+=(long long)abs(sz[v[i]]-(n-sz[v[i]]))*w[i];
	}
	printf("%lld\n",ans);
	
	return 0;
}
