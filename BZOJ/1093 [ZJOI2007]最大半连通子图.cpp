/*
DATE : 2013-3-1 
RATING : 3
TAG : Tarjan + DP
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

const int MAXN = 100000 + 5;
const int MAXM = 1000000 + 5;
const int BASE = 1111111;

struct Edge
{
	int next,to;
} g[MAXM],G[MAXM];
int start[MAXN],Gstart[MAXN],gn;

void AddEdge(int a,int b)
{
	gn++;g[gn].to=b;g[gn].next=start[a];start[a]=gn;
}

void NewAddEdge(int a,int b)
{
	gn++;G[gn].to=b;G[gn].next=Gstart[a];Gstart[a]=gn;
}

int n,m,ind[MAXN],dp[MAXN],sum[MAXN],len,MOD,ans;
int stk[MAXN],top,topo[MAXN],topolen,dfn[MAXN],low[MAXN],cnt[MAXN];
int Index,Bcnt,Belong[MAXN];
bool vis[MAXN];
map <long long , bool> HASH;

void Tarjan(int p)
{
	stk[++top]=p;
	vis[p]=1;
	dfn[p]=low[p]=++Index;
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
			i=stk[top--];
			vis[i]=0;
			Belong[i]=Bcnt;
		}
	}
}

void BuildNewGraph()
{
	gn=0;
	for(int i=1;i<=n;i++) cnt[Belong[i]]++;
	for(int i=1;i<=n;i++)
	{
		int p=Belong[i];
		for(int j=start[i];j;j=g[j].next)
		{
			int v=Belong[g[j].to];
			if(p==v) continue;
			long long tmp1=(long long)p*BASE+v;
			if(!HASH[tmp1])
			{
				HASH[tmp1]=1;
				ind[v]++;
				NewAddEdge(p,v);
			}
		}
	}
	n=Bcnt;
}

void Solve()
{
	top=0;
	for(int i=1;i<=n;i++) if(!ind[i])
	{
		dp[i]=cnt[i];
		sum[i]=1;
		stk[++top]=i;
	}
	while(top>0)
	{
		int p=stk[top--];
		topo[++topolen]=p;
		for(int i=Gstart[p];i;i=G[i].next)
		{
			int v=G[i].to;
			ind[v]--;
			if(!ind[v]) stk[++top]=v;
		}
	}
	for(int i=1;i<=n;i++)
	{
		int p=topo[i];
		for(int j=Gstart[p];j;j=G[j].next)
		{
			int v=G[j].to;
//			cout<<p<<' '<<v<<endl;
			dp[v]=max(dp[v],dp[p]+cnt[v]);
		}
	}
	for(int i=1;i<=n;i++) len=max(len,dp[i]);

	for(int i=1;i<=n;i++)
	{
		int p=topo[i];
		for(int i=Gstart[p];i;i=G[i].next)
		{
			int v=G[i].to;
			if(dp[v]==dp[p]+cnt[v]) sum[v]=(sum[v]+sum[p])%MOD;
		}
	}
	for(int i=1;i<=n;i++) if(dp[i]==len) ans=(ans+sum[i])%MOD;
	printf("%d\n%d\n",len,ans);
}

int main()
{
	scanf("%d%d%d",&n,&m,&MOD);
	for(int a,b,i=1;i<=m;i++) 
	{
		scanf("%d%d",&a,&b);
		AddEdge(a,b);
	}
	for(int i=1;i<=n;i++) if(!dfn[i]) Tarjan(i);
	BuildNewGraph();
	Solve();
	return 0;
}
