/*
DATE : 2013-3-5 
RATING : 3
TAG : MinCost MaxFLow
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

const int MAXN = 2000 + 10;
const int MAXM = 30000 + 10;
const int INF = 1000000000;

int n,Ta,Tb,Fa,Fb,F,S,T;
int p[MAXN];
int delta,MinCost;

struct Edge
{
	int next,to,w,cost,rev;
} g[MAXM*2];
int gn,start[MAXN];

void AddEdge(int a,int b,int c,int d)
{
	gn++;g[gn].to=b;g[gn].next=start[a];start[a]=gn;g[gn].w=c;g[gn].cost=d;g[gn].rev=gn+1;
	gn++;g[gn].to=a;g[gn].next=start[b];start[b]=gn;g[gn].w=0;g[gn].cost=-d;g[gn].rev=gn-1;
}

int q[MAXN],head,tail;
int dist[MAXN],path[MAXN];
bool vis[MAXN];

bool SPFA()
{
	head=0;tail=1;q[head]=S;
	memset(dist,63,sizeof(dist));
	memset(vis,0,sizeof(vis));
	vis[S]=1;dist[S]=0;
	while(head!=tail)
	{
		int p=q[head++];
		if(head==MAXN) head=0;
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
					q[tail++]=v;if(tail==MAXN) tail=0;vis[v]=1;
				}
			}
		}
	}
	return dist[T]<INF;
}

inline int f(int i,int Type)
{
	return Type*n+i;
}

void Aug()
{
	int now=T;
	delta=INF;
	while(now!=S)
	{
		int i=path[now];
		delta=min(g[i].w,delta);
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

int main()
{
	scanf("%d%d%d%d%d%d",&n,&Ta,&Tb,&F,&Fa,&Fb);
	S=2*n+1;T=S+1;
	for(int i=1;i<=n;i++) 
	{
		scanf("%d",&p[i]);
		AddEdge(S,f(i,0),p[i],0);
		AddEdge(f(i,1),T,p[i],0);
		AddEdge(f(i,0),T,INF,F);
		if(i!=n) AddEdge(f(i,0),f(i+1,0),INF,0);
		if(i+Ta+1<=n) AddEdge(f(i,0),f(i+Ta+1,1),INF,Fa);
		if(i+Tb+1<=n) AddEdge(f(i,0),f(i+Tb+1,1),INF,Fb);
	}
	while(SPFA()) Aug();
	printf("%d\n",MinCost);
	
	return 0;
}
