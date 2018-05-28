/*
DATE : 2013-5-24 
RATING : 2
TAG : Tarjan
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

//Orz WJMZBMR && sevenkplus

using namespace std;

const int MAXN = 4000 + 10;
const int MAXE = MAXN * MAXN / 2;

struct Edge
{
	int next,to;
} g[MAXE],G[MAXE];
int gn,start[MAXN],Gstart[MAXN];

inline void AddEdge(int a,int b)
{
	gn++;g[gn].next=start[a];start[a]=gn;g[gn].to=b;
}

inline void GAddEdge(int a,int b)
{
	gn++;G[gn].next=Gstart[a];Gstart[a]=gn;G[gn].to=b;
}

int n,s[MAXN],Belong[MAXN],f[MAXN],stk[MAXN],Top,Index,Bcnt,dfn[MAXN],low[MAXN];
bool Map[MAXN][MAXN],NewMap[MAXN][MAXN],vis[MAXN];
int ans;

void Tarjan(int p)
{
	dfn[p]=low[p]=++Index;
	vis[p]=1;
	stk[++Top]=p;
	for(int i=start[p];i;i=g[i].next)
	{
		int v=g[i].to;
		if(!dfn[v])
		{
			Tarjan(v);
			low[p]=min(low[v],low[p]);
		}
		else if(vis[v]) low[p]=min(low[p],dfn[v]);
	}
	if(low[p]==dfn[p])
	{
		Bcnt++;
		int i=-1;
		while(i!=p)
		{
			i=stk[Top--];
			Belong[i]=Bcnt;
			vis[i]=0;
			s[Bcnt]++;
		}
	}
}

int vv[MAXN],idx;

void dfs(int p)
{
	vv[p]=idx;
	f[p]=s[p];
	for(int i=start[p];i;i=g[i].next)
	{
		int v=g[i].to;
		if(vv[v]!=idx)
		{
			dfs(v);
			f[p]+=f[v];
		}
	}
}

int main()
{
	scanf("%d",&n);
	char ch;
	for(int i=1;i<=n;i++) 
	{
		for(ch=getchar();ch!='0' && ch!='1';ch=getchar());
		for(int j=1;j<=n;j++) {if(ch=='1') AddEdge(i,j);ch=getchar();}
	}
	for(int i=1;i<=n;i++) if(!dfn[i]) Tarjan(i);
	gn=0;
	for(int p=1;p<=n;p++) 
	{
		for(int i=start[p];i;i=g[i].next)
		{
			int v=g[i].to;
			if(Belong[p]==Belong[v]) continue;
			int pp=Belong[p];
			v=Belong[v];
			if(NewMap[pp][v]) continue;
			GAddEdge(pp,v);
			NewMap[pp][v]=1;
		}
	}
	memcpy(g,G,sizeof(g));
	memcpy(start,Gstart,sizeof(start));
	n=Bcnt;
	for(int i=1;i<=n;i++)
	{
		idx=i;
		dfs(i);
		ans+=f[i]*s[i];
	}
	printf("%d\n",ans);
	
	return 0;
}
