/*
DATE : 2013-5-14 
RATING : 3
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

const int MAXN = 100000 + 10;
const int MAXE = 300000 + 10;

struct Edge
{
	int next,to;
} g[MAXE];
int gn,start[MAXN];

inline void AddEdge(int a,int b)
{
	gn++;g[gn].next=start[a];start[a]=gn;g[gn].to=b;
}

int n,m,Belong[MAXN],Bcnt,Index,stk[MAXN],Top;
int ans;
int dfn[MAXN],low[MAXN],ind[MAXN],pre[MAXN];
bool vis[MAXN];

void Tarjan(int p)
{
	++Index;
	dfn[p]=low[p]=Index;
	stk[++Top]=p;
	vis[p]=1;
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
	if(dfn[p]==low[p])
	{
		Bcnt++;
		int i=-1;
		while(i!=p)
		{
			i=stk[Top--];
			vis[i]=0;
			Belong[i]=Bcnt;
		}
	}
	return;
}

int main()
{
	scanf("%d%d",&n,&m);
	for(int a,b,i=1;i<=m;i++) 
	{
		scanf("%d%d",&a,&b);
		AddEdge(a,b);
	}
	for(int i=1;i<=n;i++) if(!dfn[i]) Tarjan(i);
	for(int i=1;i<=n;i++)
	{
		for(int j=start[i];j;j=g[j].next)
		{
			int v=g[j].to;
			if(Belong[i]==Belong[v]) continue;
			if(pre[Belong[v]]==0) pre[Belong[v]]=Belong[i];
			else if(pre[Belong[v]]!=Belong[i]) pre[Belong[v]]=-1;
		}
	}
	for(int i=1;i<=Bcnt;i++) if(pre[i]==0) ++ans;
	for(int i=1;i<=n;i++) if(pre[Belong[i]]==0)
	{
		bool flag=true;
		for(int j=start[i];j;j=g[j].next)
		{
			int v=g[j].to;
			if(Belong[i]==Belong[v]) {flag=false;break;}
			if(pre[Belong[v]]!=-1) {flag=false;break;}
		}
		if(flag) {ans--;break;}
	}
	printf("%.6lf\n",(n-ans)*1.0/n);
	
	return 0;
}
