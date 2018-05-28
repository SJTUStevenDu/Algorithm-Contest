/*
DATE : 2013-2-21 
RATING : 3
TAG : LCA
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

//Orz WJMZBMR && sevenkplus

using namespace std;

const int MAXN = 400000 + 5;

struct Edge
{
	int to,next;
} g[MAXN*2];
int start[MAXN],gn;

void AddEdge(int a,int b)
{
	gn++;g[gn].to=b;g[gn].next=start[a];start[a]=gn;
}

int n,K;
int Belong[MAXN/2];
int fa[20][MAXN];
int q[MAXN],head,tail;
int dep[MAXN],Log[MAXN],ans[MAXN/2],Low[MAXN/2],ro;
bool vis[MAXN];

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
	for(;fa[u][a]!=fa[u][b];) u++;
	for(;u>=0;u--) if(fa[u][a]!=fa[u][b]) a=fa[u][a],b=fa[u][b];
	if(a!=b) return fa[0][a];
	else return a;
}

int Getdist(int a,int b)
{
	return dep[a]+dep[b]-2*dep[LCA(a,b)];
}

int main()
{
	scanf("%d%d",&n,&K);
	for(int i=1;i<=n;i++) 
	{
		int a,b;
		scanf("%d%d",&a,&b);
		Belong[i]=a;
		if(b==0) {ro=i;continue;}
		AddEdge(i,b);
		AddEdge(b,i);
	}
	q[0]=ro;vis[ro]=1;tail=1;
	while(head<tail)
	{
		int p=q[head++];
		vis[p]=1;
		for(int i=start[p];i;i=g[i].next)
		{
			int v=g[i].to;
			if(vis[v]) continue;
			fa[0][v]=p;
			q[tail++]=v;
			dep[v]=dep[p]+1;
		}
	}
	Log[0]=-1;
	for(int i=1;i<=n;i++) Log[i]=Log[i>>1]+1;
	for(int i=1;i<=Log[n];i++)
		for(int j=1;j<=n;j++) fa[i][j]=fa[i-1][fa[i-1][j]];
	for(int i=1;i<=n;i++) if(dep[Low[Belong[i]]]<dep[i]) Low[Belong[i]]=i;
	for(int i=1;i<=n;i++) 
	{
		int l=Belong[i];
		ans[l]=max(ans[l],Getdist(i,Low[l]));
	}
	for(int i=1;i<=K;i++) printf("%d\n",ans[i]);
	
	return 0;
}
