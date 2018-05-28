#include <iostream>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <cmath>
#include <algorithm>
#include <fstream>

using namespace std;

const int MAXN = 2000 + 10;
const int MAXM = 50000 + 10;
const int INF = 0x7FFFFFFF>>2;

struct Edge
{
	int next,to,w,cost;
} g[MAXM];
int gn=1,start[MAXN];

inline void AddEdge(int a,int b,int c,int d)
{
	gn++;g[gn].to=b;g[gn].next=start[a];start[a]=gn;g[gn].w=c;g[gn].cost=d;
	gn++;g[gn].to=a;g[gn].next=start[b];start[b]=gn;g[gn].w=0;g[gn].cost=-d;
}

int n,m,S,T,ans;
int q[MAXN],head,tail,dist[MAXN],path[MAXN];
bool vis[MAXN];

bool SPFA()
{
	memset(dist,63,sizeof(dist));
	memset(vis,0,sizeof(vis));
	head=0;tail=1;q[head]=S;vis[S]=1;dist[S]=0;
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
	int now=T,delta=INF;
	while(now!=S)
	{
		int i=path[now];
		now=g[i^1].to;
		delta=min(delta,g[i].w);
	}
	ans+=delta*dist[T];
	now=T;
	while(now!=S)
	{
		int i=path[now];
		now=g[i^1].to;
		g[i].w-=delta;g[i^1].w+=delta;
	}
}

int main()
{
	scanf("%d%d",&n,&m);
	S=2*n+1;T=S+1;
	for(int i=1;i<=n;i++) AddEdge(S,i,1,0),AddEdge(i+n,T,1,0);
	for(int x,i=1;i<=n;i++) scanf("%d",&x),AddEdge(S,i+n,1,x);
	for(int i=1;i<=m;i++)
	{
		int a,b,c;
		scanf("%d%d%d",&a,&b,&c);
		if(a>b) swap(a,b);
		AddEdge(a,b+n,1,c);
	}
	while(SPFA()) Aug();
	printf("%d\n",ans);
	
	return 0;
}
