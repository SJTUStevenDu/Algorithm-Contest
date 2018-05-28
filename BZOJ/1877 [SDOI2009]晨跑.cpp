/*
DATE : 2013-3-5 
RATING : 2
TAG : MinCost
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

const int MAXN = 200 * 200 + 10;
const int MAXE = 100000 + 10;
const int INF = 1000000000;

struct Edge
{
	int next,to,w,cost,rev;
} g[MAXE*2];
int gn,start[MAXN];

void AddEdge(int a,int b,int c,int d)
{
	gn++;g[gn].to=b;g[gn].next=start[a];start[a]=gn;g[gn].w=c;g[gn].cost=d;g[gn].rev=gn+1;
	gn++;g[gn].to=a;g[gn].next=start[b];start[b]=gn;g[gn].w=0;g[gn].cost=-d;g[gn].rev=gn-1;
}

int pn;
inline void NewNode(int &p) {p=++pn;}

int n,m,S,T,MinCost,P1[MAXN],P2[MAXN];
int q[MAXN],head,tail;
bool vis[MAXN];
int path[MAXN],delta,dist[MAXN],cnt;

bool SPFA()
{
	head=0;tail=1;q[head]=S;
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
					q[tail++]=v;
					if(tail==MAXN) tail=0;
				}
			}
		}
	}
	return dist[T]<INF;
}

void Aug()
{
	cnt++;
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
	scanf("%d%d",&n,&m);
	NewNode(S);NewNode(T);
	for(int i=2;i<n;i++) NewNode(P1[i]),NewNode(P2[i]);
	P2[1]=S;P1[n]=T;
	for(int i=2;i<n;i++) AddEdge(P1[i],P2[i],1,0);
	for(int a,b,c,i=1;i<=m;i++) 
	{
		scanf("%d%d%d",&a,&b,&c);
		if(a==n || b==1) continue;	
		AddEdge(P2[a],P1[b],1,c);
	}
	MinCost_MaxFlow();
	printf("%d %d\n",cnt,MinCost);
	return 0;
}
