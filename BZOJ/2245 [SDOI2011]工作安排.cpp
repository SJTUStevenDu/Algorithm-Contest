/*
DATE : 2013-2-17 
RATING : 3
TAG : minimum cost flow
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

//Orz WJMZBMR && sevenkplus

using namespace std;

const int MAXN = 100000 + 10;
const int INF = 0x7FFFFFFF>>2;

struct Edge
{
	int to,next,w,cost,rev;
} g[MAXN*2];

int start[MAXN],gn;

void AddEdge(int a,int b,int c,int d)
{
	gn++;g[gn].to=b;g[gn].next=start[a];start[a]=gn;g[gn].w=c;g[gn].cost=d;g[gn].rev=gn+1;
	gn++;g[gn].to=a;g[gn].next=start[b];start[b]=gn;g[gn].w=0;g[gn].cost=-d;g[gn].rev=gn-1;
}

int n,m,S,T;
long long Cost;
int A[10],W[10];
int q[MAXN],head,tail;
int dist[MAXN];
bool vis[MAXN];
int path[MAXN];

bool SPFA()
{
	memset(dist,63,sizeof(dist));
	memset(vis,0,sizeof(vis));
	memset(path,0,sizeof(path));
	dist[S]=0;head=0;q[head]=S;tail=1;vis[S]=1;
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
					q[tail++]=v;
					if(tail==MAXN) tail=0;
				}
			}
		}
	}
	return dist[T]<INF;
}

int cnt;

void Aug()
{
	int now=T,delta=INF;
	while(now!=S)
	{
		int k=path[now];
		delta=min(delta,g[k].w);
		now=g[g[k].rev].to;
	}
	now=T;
	while(now!=S)
	{
		int k=path[now];
		g[k].w-=delta;
		g[g[k].rev].w+=delta;
		Cost+=(long long)delta*g[k].cost;
		now=g[g[k].rev].to;
	}
}

int main()
{
	scanf("%d%d",&m,&n);
	S=n+m+1;T=S+1;
	for(int a,i=1;i<=n;i++) 
	{
		scanf("%d",&a);
		AddEdge(S,i,a,0);
	}
	for(int i=1;i<=m;i++)
		for(int j=1;j<=n;j++) 
		{
			int a;
			scanf("%d",&a);
			if(a) AddEdge(j,i+n,INF,0);
		}
	for(int i=1;i<=m;i++)
	{
		int p;
		scanf("%d",&p);
		for(int j=1;j<=p;j++) scanf("%d",&A[j]);
		for(int j=1;j<=p+1;j++) scanf("%d",&W[j]);
		for(int j=1;j<=p;j++) AddEdge(i+n,T,A[j]-A[j-1],W[j]);
		AddEdge(i+n,T,INF,W[p+1]);
	}
	while(SPFA()) Aug();
	printf("%lld\n",Cost);
	
	return 0;
}
