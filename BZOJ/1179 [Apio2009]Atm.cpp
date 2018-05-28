/*
DATE : 2013-2-26 
RATING : 3
TAG : Tarjan
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

const int MAXN = 500000 + 5;
const int MAXM = 500000 + 5;
const int MOD = 1111111;

struct Edge
{
	int next,to;
} g[MAXM],G[MAXM];
int start[MAXN],gn,Gstart[MAXN];

map <long long , bool> HASH;

void AddEdge(int a,int b)
{
	gn++;g[gn].to=b;g[gn].next=start[a];start[a]=gn;
}

void NewAddEdge(int a,int b)
{
	gn++;G[gn].to=b;G[gn].next=Gstart[a];Gstart[a]=gn;
}

int stk[MAXN],money[MAXN],Money[MAXN];
int n,m,S,T,P,top;
int Bcnt,Belong[MAXN],dfn[MAXN],low[MAXN],Index,dist[MAXN];
bool vis[MAXN];

void tarjan(int p)
{
	dfn[p]=low[p]=++Index;
	vis[p]=1;
	stk[++top]=p;
	for(int i=start[p];i;i=g[i].next)
	{
		int v=g[i].to;
		if(!dfn[v])
		{
			tarjan(v);
			low[p]=min(low[p],low[v]);
		}
		else if(vis[v]) low[p]=min(low[p],dfn[v]);
	}
	if(low[p]==dfn[p])
	{
		Bcnt++;
		int i=-1;
		while(i!=p)
		{
			i=stk[top--];
			Belong[i]=Bcnt;
			vis[i]=0;
		}
	}
}


void ReBuild()
{
	gn=0;
	for(int p=0;p<=n+1;p++)
	{
		Money[Belong[p]]+=money[p];
		for(int i=start[p];i;i=g[i].next)
		{
			int v=g[i].to;
			if(Belong[p]==Belong[v]) continue;
			long long tmp1=(long long)Belong[p]*MOD+Belong[v];
			long long tmp2=(long long)Belong[v]*MOD+Belong[p];
			if(!HASH[tmp1])
			{
				HASH[tmp1]=HASH[tmp2]=1;
				NewAddEdge(Belong[p],Belong[v]);
			}
		}
	}
	S=Belong[S];T=Belong[T];
	n=Bcnt;
}

int q[MAXN],head,tail;

void Solve()
{
	tail=1;head=0;
	q[head]=S;
	memset(vis,0,sizeof(vis));
	vis[S]=1;
	while(head!=tail)
	{
		int p=q[head++];
		if(head==MAXN) head=0;
		vis[p]=0;
		for(int i=Gstart[p];i;i=G[i].next)
		{
			int v=G[i].to;
			if(dist[p]+Money[v]>dist[v])
			{
				dist[v]=dist[p]+Money[v];
				if(!vis[v]) 
				{
					q[tail]=v,tail++,vis[v]=1;
					if(tail==MAXN) tail=0;
				}
			}
		}
	}
}

int main()
{
	scanf("%d%d",&n,&m);
	while(m--)
	{
		int a,b;
		scanf("%d%d",&a,&b);
		AddEdge(a,b);
	}
	for(int i=1;i<=n;i++) scanf("%d",&money[i]);
	int mmm;
	scanf("%d%d",&mmm,&P);
	S=0;T=n+1;
	AddEdge(S,mmm);
	while(P--) 
	{
		int a;
		scanf("%d",&a);
		AddEdge(a,T);
	}
	for(int i=0;i<=n+1;i++) if(!dfn[i]) tarjan(i);
//	tarjan();
	ReBuild();
	Solve();
	printf("%d\n",dist[T]);
	
	return 0;
}
