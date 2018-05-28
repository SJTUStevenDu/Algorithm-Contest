/*
DATE : 2013-5-23 
RATING : 3
TAG : Tarjan 2-SAT
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

const int MAXN = 1000 + 10;
const int MAXE = 10000 + 10;

struct Edge
{
	int next,to;
} g[MAXE];
int gn,start[MAXN];

inline void AddEdge(int a,int b)
{
	gn++;g[gn].to=b;g[gn].next=start[a];start[a]=gn;
}

int T,n,m,ask[MAXE][3];
int Belong[MAXN],dfn[MAXN],low[MAXN],Bcnt,Index,stk[MAXN],Top;
bool vis[MAXN];
bool ans;

void PreDo()
{
	memset(ask,0,sizeof(ask));
	memset(dfn,0,sizeof(dfn));
	memset(vis,0,sizeof(vis));
	memset(low,0,sizeof(low));
	memset(Belong,0,sizeof(Belong));
	memset(start,0,sizeof(start));
	Index=Bcnt=gn=Top=0;
	ans=true;
}

void Tarjan(int p)
{
	++Index;
	vis[p]=1;
	stk[++Top]=p;
	dfn[p]=low[p]=Index;
	for(int i=start[p];i;i=g[i].next)
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
		Bcnt++;
		int i=-1;
		while(i!=p)
		{
			i=stk[Top--];
			Belong[i]=Bcnt;
			vis[i]=0;
		}
	}
}

int main()
{
	scanf("%d",&T);
	while(T--)
	{
		PreDo();
		scanf("%d%d",&n,&m);
		for(int i=1;i<=m;i++)
		{
			char ch;
			int p1,p2;
			for(ch=getchar();ch!='m' && ch!='h';ch=getchar());
			scanf("%d",&p1);
			if(ch=='h') p1+=n;
			for(ch=getchar();ch!='m' && ch!='h';ch=getchar());
			scanf("%d",&p2);
			if(ch=='h') p2+=n;
			if(p1>n) AddEdge(p1-n,p2);
			else AddEdge(p1+n,p2);
			if(p2>n) AddEdge(p2-n,p1);
			else AddEdge(p2+n,p1);
		}
		for(int i=1;i<=n*2;i++) if(!dfn[i]) Tarjan(i);
		for(int i=1;i<=n;i++) if(Belong[i]==Belong[i+n]) ans=false;
		if(ans) printf("GOOD\n");
		else printf("BAD\n");
	}
	
	return 0;
}
