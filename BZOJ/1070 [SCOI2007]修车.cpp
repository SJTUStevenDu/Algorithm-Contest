/*
DATE : 2013-3-4 
RATING : 3
TAG : MinCost Maxflow
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

const int MAXN = 65;
const int MAXM = 15;
const int MAXV = MAXM * MAXN;
const int MAXE = MAXV * MAXV * 2;
const int INF = 1000000000;

struct Edge
{
	int next,to,w,cost,rev;
} g[MAXE];
int gn,start[MAXV];

void AddEdge(int a,int b,int c,int d)
{
	gn++;g[gn].to=b;g[gn].next=start[a];start[a]=gn;g[gn].w=c;g[gn].cost=d;g[gn].rev=gn+1;
	gn++;g[gn].to=a;g[gn].next=start[b];start[b]=gn;g[gn].w=0;g[gn].cost=-d;g[gn].rev=gn-1;
}

int n,m,S,T,a,MinCost;
int t[MAXM][MAXN];

inline int f(int i,int j)
{
	return i*n+j;
}

int q[MAXV],head,tail;
bool vis[MAXV];
int path[MAXV],delta,dist[MAXV];

bool SPFA()
{
	head=0;tail=1;q[head]=S;
	memset(dist,63,sizeof(dist));
	memset(vis,0,sizeof(vis));
	dist[S]=0;vis[S]=1;
	while(head!=tail)
	{
		int p=q[head++];
		if(head==MAXV) head=0;
		vis[p]=0;
		for(int i=start[p];i;i=g[i].next) if(g[i].w>0)
		{
			int v=g[i].to;
			if(dist[v]>dist[p]+g[i].cost)
			{
				dist[v]=dist[p]+g[i].cost;
				path[v]=i;
				if(!vis[v])
				{
					vis[v]=1;
					q[tail++]=v;
					if(tail==MAXV) tail=0;
				}
			}
		}
	}
	return dist[T]<INF;
}

void Aug()
{
	int now=T;
	delta=INF;
	while(now!=S)
	{
		int i=path[now];
		delta=min(delta,g[i].w);
		now=g[g[i].rev].to;
	}
	MinCost+=delta*dist[T];
	now=T;
	while(now!=S)
	{
		int i=path[now];
		g[i].w-=delta;
		g[g[i].rev].w+=delta;
		now=g[g[i].rev].to;
	}
}

void MinCost_MaxFlow()
{
	while(SPFA()) Aug();
}

int main()
{
	scanf("%d%d",&m,&n);
	S=n*(m+1)+1;T=S+1;
	for(int i=1;i<=n;i++) 
	{
		AddEdge(S,i,1,0);
		for(int j=1;j<=m;j++) scanf("%d",&t[i][j]);
	}
	for(int i=1;i<=m;i++) 
		for(int j=1;j<=n;j++)
		{
			AddEdge(f(i,j),T,1,0);
			for(int k=1;k<=n;k++) AddEdge(k,f(i,j),1,t[k][i]*j);
		}
	MinCost_MaxFlow();
	printf("%.2lf\n",(double)MinCost/n);
	return 0;
}
