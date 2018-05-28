/*
DATE : 2013-2-15 
RATING : 3
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

const int MAXN = 500000 + 5;

struct Edge
{
	int to,next;
} g[MAXN*2];
int gn,start[MAXN];

void AddEdge(int a,int b)
{
	gn++;g[gn].to=b;g[gn].next=start[a];start[a]=gn;
}

int n,m,dep[MAXN];
int fa[19][MAXN];
int Log[MAXN];
bool vis[MAXN];
int q[MAXN],head,tail;

inline int getfa(int p,int r)
{
	while(r) p=fa[Log[r]][p],r-=(1<<Log[r]);
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

int getdist(int a,int b)
{
	return dep[a]+dep[b]-2*dep[LCA(a,b)];
}

int main()
{
	scanf("%d%d",&n,&m);
	for(int a,b,i=1;i<n;i++) 
	{
		scanf("%d%d",&a,&b);
		AddEdge(a,b);AddEdge(b,a);
	}
	q[head]=1;tail=1;vis[1]=1;
	while(head!=tail)
	{
		int p=q[head++];
		for(int i=start[p];i;i=g[i].next)
		{
			int v=g[i].to;
			if(!vis[v]) q[tail++]=v,dep[v]=dep[p]+1,vis[p]=1,fa[0][v]=p;
		}
	}
	Log[0]=-1;
	for(int i=1;i<=n;i++) Log[i]=Log[i>>1]+1;
	for(int i=1;i<=Log[n];i++)
		for(int j=1;j<=n;j++) fa[i][j]=fa[i-1][fa[i-1][j]];
	while(m--)
	{
		int ans=1000000000,pos=0,a,b,c;
		scanf("%d%d%d",&a,&b,&c);
		if(getdist(a,b)+getdist(c,LCA(a,b))<ans) ans=getdist(a,b)+getdist(c,LCA(a,b)),pos=LCA(a,b);
		if(getdist(b,c)+getdist(a,LCA(b,c))<ans) ans=getdist(b,c)+getdist(a,LCA(b,c)),pos=LCA(b,c);
		if(getdist(a,c)+getdist(b,LCA(a,c))<ans) ans=getdist(a,c)+getdist(b,LCA(a,c)),pos=LCA(a,c);
		printf("%d %d\n",pos,ans);
	}
	
	return 0;
}
