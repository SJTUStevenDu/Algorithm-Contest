#include <iostream>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <cmath>
#include <algorithm>
#include <fstream>

using namespace std;

const int MAXN = 1000 + 10;
const int MAXE = 80000 + 10;
const int INF = 0x7FFFFFFF>>2;

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

int n,m,head,tail,S,T,sp,ans;
int p[MAXN],a[MAXN][MAXN],cnt[MAXN],cur[MAXN],dist[MAXN],q[MAXN],path[MAXN];
bool vis[MAXN];

bool SPFA()
{
	head=0;tail=1;
	memset(dist,63,sizeof(dist));
	dist[S]=0;vis[S]=1;q[head]=S;
	while(head!=tail)
	{
		int p=q[head++];
		if(head==MAXN) head=0;
		vis[p]=0;
		for(int i=start[p];i;i=g[i].next) if(g[i].w)
		{
			int v=g[i].to;
			if(dist[v]>dist[p]+g[i].cost)
			{
				dist[v]=dist[p]+g[i].cost;
				path[v]=i;
				if(vis[v]) continue;
				vis[v]=1;
				q[tail++]=v;
				if(tail==MAXN) tail=0;
			}
		}
	}
}

void Aug()
{
	ans+=dist[T];
	int now=T;
	while(now!=S)
	{
		int i=path[now];
		g[i].w--;g[i^1].w++;
		now=g[i^1].to;
	}
}

int main()
{
	scanf("%d%d",&n,&m);
	gn=1;
	for(int i=1;i<=n;i++) scanf("%d",&p[i]),sp+=p[i];
	S=n+m+sp+1;T=S+1;
	for(int i=1;i<=n;i++) AddEdge(S,i,p[i],0);
	for(int i=1;i<=n;i++) 
		for(int j=1;j<=m;j++) scanf("%d",&a[i][j]),AddEdge(i,n+j,1,a[i][j]);
	for(int i=1;i<=m;i++) 
	{
		cnt[i]=1;
		AddEdge(n+i,T,1,0);
		cur[i]=gn-1;
	}
	for(int k=1;k<=sp;k++)
	{
		SPFA();
		Aug();
		int x=1;
		for(;g[cur[x]].w;x++);
		++cnt[x];
		for(int i=1;i<=n;i++) AddEdge(i,n+m+k,1,a[i][x]*cnt[x]);
		AddEdge(n+m+k,T,1,0);
		cur[x]=gn-1;
	}
	printf("%d\n",ans);
	
	return 0;
}
