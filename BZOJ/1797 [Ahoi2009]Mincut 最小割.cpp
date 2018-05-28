/*
DATE : 2013-3-3 
RATING : 3
TAG : MinCut + Tarjan
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
#include <queue>
#include <vector>

//Orz WJMZBMR && sevenkplus

using namespace std;

const int MAXN = 4000 + 10;
const int MAXM = 60000 + 10;
const int INF = 1000000000;

struct Edge
{
	int next,to,w,rev,num;
} g[MAXM*2];
int gn,start[MAXN];

void AddEdge(int a,int b,int c,int d)
{
	gn++;g[gn].to=b;g[gn].next=start[a];start[a]=gn;g[gn].rev=gn+1;g[gn].w=c;g[gn].num=d;
	gn++;g[gn].to=a;g[gn].next=start[b];start[b]=gn;g[gn].rev=gn-1;g[gn].w=0;g[gn].num=0;
}

int n,m,S,T;
int e[MAXM][2];
int h[MAXN],vh[MAXN];
int stk[MAXN],Top,Belong[MAXN],Bcnt,Index;
int dfn[MAXN],low[MAXN];
bool vis[MAXN],flag;
int flow;

void Aug(int p)
{
	if(p==T)
	{
		flag=true;
		return;
	}
	int i,tmp=flow,minnode=n-1;
	for(i=start[p];i;i=g[i].next) if(g[i].w>0)
	{
		int v=g[i].to;
		if(h[p]==h[v]+1)
		{
			flow=min(flow,g[i].w);
			Aug(v);
			if(flag) break;
			if(h[S]>=n) return;
			flow=tmp;
		}
		minnode=min(minnode,h[v]);
	}
	if(flag)
	{
		g[i].w-=flow;
		g[g[i].rev].w+=flow;
	}
	else 
	{
		vh[h[p]]--;
		if(vh[h[p]]==0) h[S]=n;
		h[p]=minnode+1;
		vh[h[p]]++;
	}
}

void MAXFLOW()
{
	vh[0]=n;
	while(h[S]<n)
	{
		flow=INF;
		flag=false;
		Aug(S);
	}
}

void Tarjan(int p)
{
	dfn[p]=low[p]=++Index;
	stk[++Top]=p;
	vis[p]=1;
	for(int i=start[p];i;i=g[i].next) if(g[i].w>0)
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
			vis[i]=0;
			Belong[i]=Bcnt;
		}
	}
}

int main()
{
	scanf("%d%d%d%d",&n,&m,&S,&T);
	for(int a,b,c,i=1;i<=m;i++) 
	{
		scanf("%d%d%d",&a,&b,&c);
		AddEdge(a,b,c,i);
	}
	MAXFLOW();
	for(int i=1;i<=n;i++) if(!dfn[i]) Tarjan(i);
	for(int p=1;p<=n;p++)
	{
		for(int i=start[p];i;i=g[i].next) if(g[i].num)
		{
			int v=g[i].to,d=g[i].num;
			if(Belong[p]!=Belong[v] && g[i].w==0) e[d][0]=1;else e[d][0]=0;
			if(Belong[p]!=Belong[v] && Belong[p]==Belong[S] && Belong[v]==Belong[T] && g[i].w==0) e[d][1]=1;else e[d][1]=0;
		}
	}
	for(int i=1;i<=m;i++) printf("%d %d\n",e[i][0],e[i][1]);
	
	return 0;
}
