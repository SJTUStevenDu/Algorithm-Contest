/*
DATE : 2013-7-23 
RATING : 2
TAG : Cut Vertex
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
#include <map>

//Orz WJMZBMR && sevenkplus

using namespace std;

const int MAXN = 500 + 10;

struct Edge
{
	int next,to;
} g[MAXN*2];
int gn,start[MAXN];

inline void AddEdge(int a,int b)
{
	gn++;g[gn].next=start[a];start[a]=gn;g[gn].to=b;
}

int n,dfn[MAXN],low[MAXN],Index,color,col[MAXN],num[MAXN],sum[MAXN],CaseNum,cnt;
long long ans;
bool iscut[MAXN],vis[MAXN];

void dfs_1(int p,int fa)
{
	dfn[p]=low[p]=++Index;
	int child=0;
	for(int i=start[p];i;i=g[i].next)
	{
		int v=g[i].to;
		if(!dfn[v])
		{
			child++;
			dfs_1(v,p);
			low[p]=min(low[p],low[v]);
			if(low[v]>=dfn[p]) iscut[p]=1;
		}
		else if(v!=fa) low[p]=min(dfn[v],low[p]);
	}
	if(fa<0 && child==1) iscut[p]=0;
}

void dfs_2(int p)
{
	vis[p]=1;
	col[p]=color;
	sum[color]++;
	for(int i=start[p];i;i=g[i].next)
	{
		int v=g[i].to;
		if(vis[v]) continue;
		if(!iscut[v]) dfs_2(v);
		else if(col[v]!=color)
		{
			++num[color];
			col[v]=color;
		}
	}
}

map <int , int> HASH;
int k;

void Readdata()
{
	gn=0;
	memset(low,0,sizeof(low));
	memset(iscut,0,sizeof(iscut));
	memset(dfn,0,sizeof(dfn));
	memset(vis,0,sizeof(vis));
	memset(start,0,sizeof(start));
	color=0;
	memset(col,0,sizeof(col));
	memset(sum,0,sizeof(sum));
	memset(num,0,sizeof(num));
	k=0;HASH.clear();
	for(int a,b,i=1;i<=n;i++)
	{
		scanf("%d%d",&a,&b);
		if(!HASH.count(a)) HASH[a]=++k;
		if(!HASH.count(b)) HASH[b]=++k;
		a=HASH[a];b=HASH[b];
		AddEdge(a,b);
		AddEdge(b,a);
	}
	n=k;
}

void Work()
{
	ans=1;cnt=0;
	for(int i=1;i<=n;i++) if(!dfn[i]) dfs_1(i,-1);
	for(int i=1;i<=n;i++) if(!vis[i] && !iscut[i])
	{
		color++;
		dfs_2(i);
		if(num[color]==1) ans*=sum[color],++cnt;
	}
	if(color==1) cnt=2,ans=n*(n-1)/2;
	printf("Case %d: %d %lld\n",++CaseNum,cnt,ans);
}

int main()
{
	while(~scanf("%d",&n))
	{
		if(n==0) break;
		Readdata();
		Work();
	}
	
	return 0;
}
