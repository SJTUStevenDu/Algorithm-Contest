/*
DATE : 2013-3-12 
RATING : 2
TAG : MinCut
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

const int MAXN = 10000 + 10;
const int MAXE = MAXN * 10;
const int INF = 0x7FFFFFFF>>2;
const int gx[4]={0,1,0,-1};
const int gy[4]={1,0,-1,0};

struct Edge
{
	int next,to,w,rev;
} g[MAXE*2];
int gn,start[MAXN];

void AddEdge(int a,int b,int c)
{
	gn++;g[gn].to=b;g[gn].next=start[a];start[a]=gn;g[gn].w=c;g[gn].rev=gn+1;
	gn++;g[gn].to=a;g[gn].next=start[b];start[b]=gn;g[gn].w=0;g[gn].rev=gn-1;
}

int n,m,S,T;
int flow,delta,h[MAXN],vh[MAXN];
int Map[105][105];
bool flag;

inline int f(int i,int j)
{
	return (i-1)*m+j;
}

void Aug(int p)
{
	if(p==T)
	{
		flag=1;
		flow+=delta;
		return;
	}
	int i,minnode=n-1,tmp=flow;
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
		g[g[i].rev].w+=delta;
	}
	else 
	{
		vh[h[p]]--;
		if(vh[h[p]]==0) h[S]=n;
		h[p]=minnode+1;
		vh[h[p]]++;
	}
}

int main()
{
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++) 
		for(int j=1;j<=m;j++) scanf("%d",&Map[i][j]);
	S=n*m+1;T=S+1;
	for(int i=1;i<=n;i++)
		for(int j=1;j<=m;j++) 
		{
			if(Map[i][j]==1) AddEdge(S,f(i,j),INF);
			else if(Map[i][j]==2) AddEdge(f(i,j),T,INF);
			for(int k=0;k<4;k++)
			{
				int px=i+gx[k];
				int py=j+gy[k];
				if(px>0 && px<=n && py>0 && py<=m)
				{
					if(Map[i][j]==2 || Map[px][py]==1) continue;
					AddEdge(f(i,j),f(px,py),1);
				}
			}
		}
	n=T;
	vh[0]=n;
	while(h[S]<n)
	{
		flag=0;
		delta=INF;
		Aug(S);
	}
	printf("%d\n",flow);
	
	return 0;
}
