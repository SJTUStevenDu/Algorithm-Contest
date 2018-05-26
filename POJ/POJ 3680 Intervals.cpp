#include <iostream>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <cmath>
#include <algorithm>
#include <fstream>

using namespace std;

const int MAXN = 500;
const int MAXE = 3000;
const int INF = 1000000000;

struct Edge
{
	int next,to,w,cost;
} g[MAXE];
int gn,start[MAXN];

inline void AddEdge(int a,int b,int c,int d)
{
	gn++;g[gn].next=start[a];start[a]=gn;g[gn].to=b;g[gn].w=c;g[gn].cost=d;
	gn++;g[gn].next=start[b];start[b]=gn;g[gn].to=a;g[gn].w=0;g[gn].cost=-d;
}

int CaseNum;
int n,k,S,T,a[MAXN],q[MAXN],head,tail,dist[MAXN],path[MAXN],ans,u[200000];
bool vis[MAXN];

struct Node
{
	int st,en,ww;
} b[MAXN];

bool SPFA()
{
	head=0;tail=1;
	memset(vis,0,sizeof(vis));
	for(int i=1;i<=T;i++) dist[i]=-INF;
	q[head]=S;vis[S]=1;dist[S]=0;
	while(head!=tail)
	{
		int p=q[head++];
		if(head==MAXN) head=0;
		vis[p]=0;
		for(int i=start[p];i;i=g[i].next) if(g[i].w)
		{
			int v=g[i].to;
			if(dist[v]<dist[p]+g[i].cost)
			{
				dist[v]=dist[p]+g[i].cost;
				path[v]=i;
				if(!vis[v])
				{
					vis[v]=1;
					if(dist[v]>dist[q[head]])
					{
						--head;
						if(head==-1) head+=MAXN;
						q[head]=v;
					}
					else 
					{
						q[tail++]=v;
						if(tail==MAXN) tail=0;
					}
				}
			}
		}
	}
	return dist[T]>-INF;
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
	ans+=delta*dist[T];
	now=T;
	while(now!=S)
	{
		int i=path[now];
		g[i].w-=delta;g[i^1].w+=delta;
		now=g[i^1].to;
	}
}

int main()
{
	scanf("%d",&CaseNum);
	while(CaseNum--)
	{
		scanf("%d%d",&n,&k);
		gn=1;ans=0;a[0]=0;
		memset(start,0,sizeof(start));
		for(int i=1;i<=n;i++) 
		{
			scanf("%d%d%d",&b[i].st,&b[i].en,&b[i].ww);
			a[++a[0]]=b[i].st;
			a[++a[0]]=b[i].en;
		}
		sort(a+1,a+1+a[0]);
		a[0]=unique(a+1,a+a[0]+1)-a-1;
		for(int i=1;i<=a[0];i++) 
		{
			if(i!=a[0]) AddEdge(i,i+1,INF,0);
			u[a[i]]=i;
		}
		for(int i=1;i<=n;i++) AddEdge(u[b[i].st],u[b[i].en],1,b[i].ww);
		S=a[0]+1;T=S+1;
		AddEdge(S,1,k,0);
		AddEdge(a[0],T,k,0);
		while(SPFA()) Aug();
		printf("%d\n",ans);
	}
	
	return 0;
}
