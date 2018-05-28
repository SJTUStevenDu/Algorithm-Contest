/*
DATE : 2013-3-3 
RATING : 2
TAG : Tarjan
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

const int MAXN = 10000 + 5;
const int MAXM = 50000 + 5;

struct Edge
{
	int next,to;
} g[MAXM];
int gn,start[MAXN];

void AddEdge(int a,int b)
{
	gn++;g[gn].to=b;g[gn].next=start[a];start[a]=gn;
}

bool vis[MAXN];
int stk[MAXN],Top,Index,Belong[MAXN],Bcnt;
int dfn[MAXN],low[MAXN],cnt[MAXN];
int n,m,outd[MAXN];
map <long long , bool> HASH;

void Tarjan(int p)
{
	dfn[p]=low[p]=++Index;
	vis[p]=1;
	stk[++Top]=p;
	for(int i=start[p];i;i=g[i].next)
	{
		int v=g[i].to;
		if(!dfn[v]) 
		{
			Tarjan(v);
			low[p]=min(low[p],low[v]);
		}
		else if(vis[v]) low[p]=min(low[p],dfn[v]);
	}
	if(low[p]==dfn[p])
	{
		int i=-1;
		Bcnt++;
		while(i!=p)
		{
			i=stk[Top--];
			Belong[i]=Bcnt;
			vis[i]=1;
		}
	}
}

int main()
{
	scanf("%d%d",&n,&m);
	for(int a,b,i=1;i<=m;i++)
	{
		scanf("%d%d",&a,&b);
		AddEdge(a,b);
	}
	for(int i=1;i<=n;i++) if(!dfn[i]) Tarjan(i);
	int BASE = n+1;
	for(int i=1;i<=n;i++)
	{
		int p=Belong[i];
		for(int j=start[i];j;j=g[j].next)
		{
			int v=Belong[g[j].to];
			if(p==v) continue;
			long long tmp=(long long)p*BASE+v;
			if(!HASH[tmp])
			{
				HASH[tmp]=1;
				outd[p]++;
			}
		}
	}
	int ans=0;
	for(int i=1;i<=n;i++) cnt[Belong[i]]++;
	n=Bcnt;
	for(int i=1;i<=n;i++)
		if(outd[i]==0)
		{
			if(!ans) ans=i;
			else
			{
				printf("%d\n",0);
				return 0;
			}
		}
	printf("%d\n",cnt[ans]);
	
	return 0;
}
