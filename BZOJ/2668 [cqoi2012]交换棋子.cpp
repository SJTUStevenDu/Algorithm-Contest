/*
DATE : 2013-03-15 
RATING : 3
TAG : MinCost MaxFlow
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

const int MAXN = 25;
const int MAXV = MAXN * MAXN * 2;
const int MAXE = MAXV * MAXV / 2;
const int INF = 0x7FFFFFFF>>2;
const int gx[8]={0,1,0,-1,-1,1,1,-1};
const int gy[8]={1,0,-1,0,-1,1,-1,1};

struct Edge
{
	int next,to,w,cost,rev;
} g[MAXE];
int gn,start[MAXV];

inline void AddEdge(int a,int b,int c,int d)
{
	gn++;g[gn].to=b;g[gn].next=start[a];start[a]=gn;g[gn].w=c;g[gn].cost=d;g[gn].rev=gn+1;
	gn++;g[gn].to=a;g[gn].next=start[b];start[b]=gn;g[gn].w=0;g[gn].cost=-d;g[gn].rev=gn-1;
}

int n,m,pn,S,T,ans,cnt1,cnt2,flow;
int A[MAXN][MAXN],B[MAXN][MAXN];
int q[MAXV],head,tail,path[MAXV],delta,dist[MAXV];
int a[MAXN][MAXN],b[MAXN][MAXN],Lim[MAXN][MAXN];
bool vis[MAXV];

inline void NewNode(int &p) {p=++pn;}

bool SPFA()
{
	q[head=0]=S;tail=1;
	memset(vis,0,sizeof(vis));
	memset(dist,63,sizeof(dist));
	dist[S]=0;vis[S]=1;
	while(head!=tail)
	{
		int p=q[head++];
		if(head==MAXV) head=0;
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
					if(dist[v]>dist[q[head]])
					{
						q[tail++]=v;if(tail==MAXV) tail=0;
					}
					else 
					{
						--head;if(head==-1) head=MAXV-1;q[head]=v;
					}
				}
			}
		}
	}
	return dist[T]<INF;
}

void Aug()
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
	flow+=delta;
	ans+=delta*dist[T];
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
	scanf("%d%d",&n,&m);
	char ch=0;
	for(int i=1;i<=n;i++)
	{
		while(ch!='0' && ch!='1') ch=getchar();
		for(int j=1;j<=m;j++) 
		{
			a[i][j]=ch-'0';
			if(a[i][j]) cnt1++;
			ch=getchar();
		}
	}
	ch=0;
	for(int i=1;i<=n;i++)
	{
		while(ch!='0' && ch!='1') ch=getchar();
		for(int j=1;j<=m;j++) 
		{
			b[i][j]=ch-'0';
			if(b[i][j]) cnt2++;
			ch=getchar();
		}
	}
	ch=0;
	for(int i=1;i<=n;i++)
	{
		while(ch<'0' || ch>'9') ch=getchar();
		for(int j=1;j<=m;j++) Lim[i][j]=ch-'0',ch=getchar();
	}
	if(cnt1!=cnt2)
	{
		printf("-1\n");
		return 0;
	}
	NewNode(S);NewNode(T);
	for(int i=1;i<=n;i++) 
		for(int j=1;j<=m;j++) NewNode(A[i][j]),NewNode(B[i][j]);
	for(int i=1;i<=n;i++)
	{
		for(int j=1;j<=m;j++) 
		{
			if(a[i][j] && b[i][j]) {AddEdge(A[i][j],B[i][j],Lim[i][j]/2,0);cnt1--;}
			else 
			{
				if(a[i][j] || b[i][j]) AddEdge(A[i][j],B[i][j],(Lim[i][j]+1)/2,0);
				else AddEdge(A[i][j],B[i][j],Lim[i][j]/2,0);
				if(a[i][j]) AddEdge(S,A[i][j],1,0);
				if(b[i][j]) AddEdge(B[i][j],T,1,0);
			}
			for(int k=0;k<8;k++)
			{
				int px=i+gx[k],py=j+gy[k];
				if(px>0 && px<=n && py>0 && py<=m) AddEdge(B[i][j],A[px][py],INF,1);
			}
		}
	}
	while(SPFA()) Aug();
	if(flow==cnt1) printf("%d\n",ans);
	else printf("-1\n");
	
	return 0;
}
