/*
DATE : 2013-3-16 
RATING : 3
TAG : MinCut 最大权封闭子图 
*/

#include <iostream>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <cmath>
#include <string>
#include <algorithm>
#include <iomanip>
#include <map>
#include <vector>

//Orz WJMZBMR && sevenkplus

using namespace std;

const int MAXN = 600 + 10;
const int MAXE = 1000000 + 10;
const int INF = 0x7FFFFFFF>>2;

struct Edge
{
	int to,next,w,rev;
} G[MAXE],g[MAXE];
int gn,start[MAXN],Gstart[MAXN];

inline void AddEdge(int a,int b,int c)
{
	gn++;g[gn].to=b;g[gn].next=start[a];start[a]=gn;g[gn].w=c;g[gn].rev=gn+1;
	gn++;g[gn].to=a;g[gn].next=start[b];start[b]=gn;g[gn].w=0;g[gn].rev=gn-1;
}

inline void FAddEdge(int a,int b,int c)
{
	gn++;G[gn].to=b;G[gn].next=Gstart[a];Gstart[a]=gn;G[gn].w=c;G[gn].rev=gn+1;
	gn++;G[gn].to=a;G[gn].next=Gstart[b];Gstart[b]=gn;G[gn].w=0;G[gn].rev=gn-1;
}


int n,m,S,T,sum,flow,delta,N;
int Map[25][35];
int Topo[MAXN],vh[MAXN],h[MAXN],ind[MAXN],Top;
bool vis[MAXN],flag;

inline int f(int i,int j)
{
	return (i-1)*m+j;
}

void init()
{
	scanf("%d%d",&n,&m);
	for(int a,b,p,i=1;i<=n;i++)
		for(int j=1;j<=m;j++)
		{
			scanf("%d",&Map[i][j]);
			scanf("%d",&p);
			for(int k=0;k<p;k++)
			{
				scanf("%d%d",&a,&b);
				++a;++b;
				FAddEdge(f(i,j),f(a,b),INF);
				++ind[f(a,b)];
			}
			if(j!=m)
			{
				++ind[f(i,j)];
				FAddEdge(f(i,j+1),f(i,j),INF);
			}
		}
	N=n*m;
}

void TopoSort()
{
	for(int i=1;i<=N;i++) if(!ind[i]) Topo[++Top]=i;
	while(Top)
	{
		int p=Topo[Top--];
		vis[p]=1;
		for(int i=Gstart[p];i;i=G[i].next) if(G[i].w>0)
		{
			int v=G[i].to;
			--ind[v];
			if(ind[v]==0) Topo[++Top]=v;
		}
	}
}

void ReBuildMap()
{
	gn=0;
	for(int i=1;i<=N;i++) if(vis[i])
	{
		for(int j=Gstart[i];j;j=G[j].next)
		{
			if(!vis[G[j].to] || G[j].w==0) continue;
			AddEdge(G[j].to,i,G[j].w);
		}
	}
	S=N+1;T=S+1;
	for(int i=1;i<=n;i++)
		for(int j=1;j<=m;j++) 
		{
			if(!vis[f(i,j)]) continue;
			if(Map[i][j]>0) AddEdge(S,f(i,j),Map[i][j]),sum+=Map[i][j];
			else AddEdge(f(i,j),T,-Map[i][j]);
		}
	N=T;
}

void Aug(int p)
{
	if(p==T)
	{
		flag=true;
		flow+=delta;
		return;
	}
	int i,tmp=delta,minnode=N-1;
	for(i=start[p];i;i=g[i].next) if(g[i].w>0)
	{
		int v=g[i].to;
		if(h[p]==h[v]+1)
		{
			delta=min(delta,g[i].w);
			Aug(v);
			if(flag) break;
			if(h[S]>=N) return;
			delta=tmp;
		}
		minnode=min(minnode,h[v]);
	}
	if(flag)
	{
		g[i].w-=delta;
		g[g[i].rev].w+=delta;
	}
	else
	{
		if(--vh[h[p]]==0) h[S]=N;
		h[p]=minnode+1;
		++vh[h[p]];
	}
}

void MAXFLOW()
{
	vh[0]=N;
	while(h[S]<N)
	{
		delta=INF;
		flag=false;
		Aug(S);
	}
}

int main()
{
	init();
	TopoSort();
	ReBuildMap();
	MAXFLOW();
	printf("%d\n",sum-flow);
	
	return 0;
}
