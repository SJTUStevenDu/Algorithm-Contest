/*
DATE : 2013-3-21 
RATING : 2
TAG : MinCut
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
#include <queue>

//Orz WJMZBMR && sevenkplus

using namespace std;

const int MAXN = 300 + 10;
const int MAXM = MAXN * (MAXN-1) + 10;
const int INF = 0x7FFFFFFF>>2;

struct Edge
{
	int next,to,w;
} g[MAXM];
int gn,start[MAXN];

inline void AddEdge(int a,int b,int c)
{
	gn++;g[gn].to=b;g[gn].next=start[a];start[a]=gn;g[gn].w=c;
	gn++;g[gn].to=a;g[gn].next=start[b];start[b]=gn;g[gn].w=0;
}

inline void FAddEdge(int a,int b,int c)
{
	gn++;g[gn].to=b;g[gn].next=start[a];start[a]=gn;g[gn].w=c;
	gn++;g[gn].to=a;g[gn].next=start[b];start[b]=gn;g[gn].w=c;
}

int n,m,S,T,ans,delta;
int vh[MAXN],h[MAXN];
bool flag;
/*
int Aug(int p,int flow)
{
	if(p==T) return flow;
	int tmp=flow,minnode=n-1;
	for(int i=start[p];i;i=g[i].next) if(g[i].w>0)
	{
		int v=g[i].to;
		if(h[p]==h[v]+1)
		{
			int ff=Aug(v,min(g[i].w,tmp));
			tmp-=ff;
			g[i].w-=ff;
			g[i^1].w+=ff;
			if(h[S]>=n || tmp==0) return flow-tmp;
		}
		if(g[i].w>0) minnode=min(minnode,h[v]);
	}
	if(flow==tmp)
	{
		if(--vh[h[p]]==0) h[S]=n;
		h[p]=minnode+1;++vh[h[p]];
	}
	return flow-tmp;
}*/

void Aug(int p)
{
	if(p==T)
	{
		flag=true;
		ans+=delta;
		return;
	}
	int i,tmp=delta,minnode=n-1;
	for(i=start[p];i;i=g[i].next) if(g[i].w>0)
	{
		int v=g[i].to;
		if(h[p]==h[v]+1)
		{
			delta=min(delta,g[i].w);
			Aug(v);
			if(h[S]>=n) return;
			if(flag) break;
			delta=tmp;
		}
		minnode=min(minnode,h[v]);
	}
	if(flag)
	{
		g[i].w-=delta;
		g[i^1].w+=delta;
	}
	else 
	{
		if(--vh[h[p]]==0) h[S]=n;
		h[p]=minnode+1;++vh[h[p]];
	}
}

int main()
{
	scanf("%d%d",&n,&m);
	gn=1;
	S=n+1;T=n+2;
	for(int a,i=1;i<=n;i++)
	{
		scanf("%d",&a);
		if(a) AddEdge(S,i,1);
		else AddEdge(i,T,1);
	}
	while(m--)
	{
		int a,b;
		scanf("%d%d",&a,&b);
		FAddEdge(a,b,1);
	}
	n=n+2;
	vh[0]=n;
//	while(h[S]<n) ans+=Aug(S,INF);
	while(h[S]<n)
	{
		delta=INF;
		flag=false;
		Aug(S);
	}
	printf("%d\n",ans);
	
	return 0;
}
