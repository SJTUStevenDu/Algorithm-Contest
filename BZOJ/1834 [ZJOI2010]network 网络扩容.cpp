/*
DATE : 2013-2-18 
RATING : 3
TAG : Mincost flow
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

const int MAXN = 1000 + 10;
const int MAXM = 5000 + 10;
const int INF = 1000000000;

struct Edge
{
	int to,next,w,cost,rev;
} g[MAXM*4];
int gn,start[MAXN];

void AddEdge(int a,int b,int c,int d)
{
	gn++;g[gn].to=b;g[gn].next=start[a];start[a]=gn;g[gn].w=c;g[gn].cost=d;g[gn].rev=gn+1;
	gn++;g[gn].to=a;g[gn].next=start[b];start[b]=gn;g[gn].w=0;g[gn].cost=-d;g[gn].rev=gn-1;
}

int n,m,K,S,T;
int A[MAXM],B[MAXM],C[MAXM],D[MAXM];
int dist[MAXN],path[MAXN],q[MAXN],head,tail;
int h[MAXN],vh[MAXN];
bool vis[MAXN],found;
int MaxFlow,MinCost,delta;

void Aug_MaxFlow(int p)
{
	if(p==T)
	{
		MaxFlow+=delta;
		found=true;
		return;
	}
	int i,tmp=delta,minh=n-1;
	for(i=start[p];i;i=g[i].next) if(g[i].w>0)
	{
		int v=g[i].to;
		if(h[v]+1==h[p])
		{
			delta=min(delta,g[i].w);
			Aug_MaxFlow(v);
			if(h[S]>=n) return;
			if(found) break;
			delta=tmp;
		}
		minh=min(minh,h[v]);
	}
	if(found)
	{
		g[i].w-=delta;
		g[g[i].rev].w+=delta;
	}
	else 
	{
		vh[h[p]]--;
		if(vh[h[p]]==0) h[S]=n;
		h[p]=minh+1;
		vh[h[p]]++;
	}
}

bool SPFA()
{
	memset(vis,0,sizeof(vis));
	memset(dist,63,sizeof(dist));
	head=0;tail=1;
	q[head]=S;vis[S]=1;dist[S]=0;
	while(head!=tail)
	{
		int p=q[head++];
		if(head>n) head=0;
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
					vis[v]=1;q[tail++]=v;if(tail>n) tail=0;
				}
			}
		}
	}
	return dist[T]<INF;
}

void Aug_Mincost()
{
	int now=T;
	delta=INF;
	while(now!=S)
	{
		int i=path[now];
		delta=min(delta,g[i].w);
		now=g[g[i].rev].to;
	}
	now=T;
	while(now!=S)
	{
		int i=path[now];
		MinCost+=g[i].cost*delta;
		g[i].w-=delta;
		g[g[i].rev].w+=delta;
		now=g[g[i].rev].to;
	}
}

int main()
{
	scanf("%d%d%d",&n,&m,&K);
	for(int i=1;i<=m;i++) 
	{
		scanf("%d%d%d%d",&A[i],&B[i],&C[i],&D[i]);
		AddEdge(A[i],B[i],C[i],0);
	}
	S=1;T=n;vh[0]=n;
	while(h[S]<n)
	{
		found=false;
		delta=INF;
		Aug_MaxFlow(S);
	}
	printf("%d ",MaxFlow);
	for(int i=1;i<=m;i++) AddEdge(A[i],B[i],INF,D[i]);
	T++;AddEdge(n,T,K,0);n=T;
	while(SPFA()) Aug_Mincost();
	printf("%d\n",MinCost);
	
	return 0;
}
