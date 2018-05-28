/*
DATE : 2013-2-15 
RATING : 2
TAG : LCA
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

const int MAXN = 1000 + 5;

struct Edge
{
	int to,next,w;
} g[MAXN*2];
int gn,start[MAXN];

void AddEdge(int a,int b,int c)
{
	gn++;g[gn].to=b;g[gn].next=start[a];start[a]=gn;g[gn].w=c;
}

int n,Q,fa[15][MAXN],Log[MAXN];
int dep[MAXN],dist[MAXN];
bool vis[MAXN];
int q[MAXN],head,tail;

int getfa(int p,int r)
{
	while(r) p=fa[Log[r]][p],r-=1<<Log[r];
	return p;
}

int LCA(int a,int b)
{
	if(dep[a]<dep[b]) swap(a,b);
	a=getfa(a,dep[a]-dep[b]);
	int u=0;
	for(;fa[u][a]!=fa[u][b];)u++;
	for(;u>=0;u--) if(fa[u][a]!=fa[u][b]) a=fa[u][a],b=fa[u][b];
	if(a!=b) return fa[0][a];
	else return a;
}

int GetDist(int a,int b)
{
	return dist[a]+dist[b]-2*dist[LCA(a,b)];
}

int main()
{
	scanf("%d%d",&n,&Q);
	for(int a,b,c,i=1;i<n;i++)
	{
		scanf("%d%d%d",&a,&b,&c);
		AddEdge(a,b,c);
		AddEdge(b,a,c);
	}
	Log[0]=-1;
	for(int i=1;i<=n;i++) Log[i]=Log[i>>1]+1;
	q[head]=1;tail=1;vis[1]=1;
	while(head<tail)
	{
		int p=q[head++];
		for(int i=start[p];i;i=g[i].next)
		{
			int v=g[i].to;
			if(!vis[v]) q[tail++]=v,vis[v]=1,dep[v]=dep[p]+1,dist[v]=dist[p]+g[i].w,fa[0][v]=p;
		}
	}
	for(int i=1;i<=Log[n];i++) 
		for(int j=1;j<=n;j++) fa[i][j]=fa[i-1][fa[i-1][j]];
	while(Q--)
	{
		int a,b;
		scanf("%d%d",&a,&b);
		printf("%d\n",GetDist(a,b));
	}
	
	return 0;
}
