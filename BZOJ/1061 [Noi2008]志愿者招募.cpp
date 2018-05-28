/*
DATE : 2013-4-1 
RATING : 4
TAG : MinCost MaxFlow
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

const int MAXN = 1000 + 10;
const int MAXE = 50000 + 10;
const int INF = 0x7FFFFFFF>>2;

int n,m,S,Needed[MAXN],T,ans;

struct Edge
{
	int next,to,w,cost;
} g[MAXE];
int gn=1,start[MAXN];

inline void AddEdge(int a,int b,int c,int d)
{
	gn++;g[gn].to=b;g[gn].next=start[a];start[a]=gn;g[gn].w=c;g[gn].cost=d;
	gn++;g[gn].to=a;g[gn].next=start[b];start[b]=gn;g[gn].w=0;g[gn].cost=-d;
}

int q[MAXN],head,tail,dist[MAXN],path[MAXN];
bool vis[MAXN];

bool SPFA()
{
	q[head=0]=S;tail=1;
	memset(dist,63,sizeof(dist));
	memset(vis,0,sizeof(vis));
	dist[S]=0;vis[S]=1;
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
					vis[v]=1;
					if(dist[q[head]]<dist[v])
					{
						q[tail++]=v;
						if(tail==MAXN) tail=0;
					}
					else
					{
						--head;
						if(head==-1) head+=MAXN;
						q[head]=v;
					}
				}
			}
		}
	}
	return dist[T]<INF;
}

void Aug()
{
	int now=T,delta=INF;
	while(now!=S)
	{
		int i=path[now];
		delta=min(delta,g[i].w);
		now=g[i^1].to;
	}
	ans+=dist[T]*delta;
	now=T;
	while(now!=S)
	{
		int i=path[now];
		g[i].w-=delta;
		g[i^1].w+=delta;
		now=g[i^1].to;
	}
}

int main()
{
	scanf("%d%d",&n,&m);
	S=n+2;T=S+1;
	gn=1;
	for(int i=1;i<=n;i++) scanf("%d",&Needed[i]);
	for(int i=1;i<=n+1;i++)
	{
		int tmp=Needed[i]-Needed[i-1];
		if(tmp>0) AddEdge(S,i,tmp,0);
		else AddEdge(i,T,-tmp,0);
		if(i>1) AddEdge(i,i-1,INF,0);
	}
	for(int a,b,c,i=1;i<=m;i++) 
	{
		scanf("%d%d%d",&a,&b,&c);
		AddEdge(a,b+1,INF,c);
	}
	while(SPFA()) Aug();
	printf("%d\n",ans);
	
	return 0;
}
