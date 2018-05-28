/*
DATE : 2013-5-21 
RATING : 3
TAG : MaxFlow
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

const int MAXV = 100 + 10;
const int MAXE = 2000 + 10;
const double INF = 1e10;
const double eps=1e-6;

struct Edge
{
	int next,to;
	double w;
} g[MAXE],G[MAXE];
int gn=1,start[MAXV];

inline void AddEdge(int a,int b,int c) {gn++;G[gn].next=start[a];start[a]=gn;G[gn].to=b;G[gn].w=c;gn++;G[gn].next=start[b];start[b]=gn;G[gn].to=a;G[gn].w=0;}

int n,m,P,S,T;
double flow,delta,maxw,maxflow;
int h[MAXV],vh[MAXV];
bool flag;

void Aug(int p)
{
	if(p==T)
	{
		flow+=delta;
		flag=true;
		return;
	}
	int minnode=n-1,i;
	double tmp=delta;
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
		--vh[h[p]];
		if(vh[h[p]]==0) h[S]=n;
		h[p]=minnode+1;
		vh[h[p]]++;
	}
}

int main()
{
	scanf("%d%d%d",&n,&m,&P);
	for(int a,b,c,i=1;i<=m;i++) 
	{
		scanf("%d%d%d",&a,&b,&c);
		AddEdge(a,b,c);
		if(c>maxw) maxw=c;
	}
	S=1;T=n;
	memcpy(g,G,sizeof(g));
	vh[0]=n;
	while(h[S]<n)
	{
		flag=false;
		delta=INF;
		Aug(S);
	}
	maxflow=flow;
	double l=0.0,r=maxw;
	while(l+eps<=r)
	{
		double mid=(l+r)/2;
		flow=0.0;
		memset(h,0,sizeof(h));
		vh[0]=n;
		memcpy(g,G,sizeof(g));
		for(int i=2;i<=gn;i++) if(g[i].w>mid) g[i].w=mid;
		while(h[S]<n)
		{
			flag=false;
			delta=(double)INF;
			Aug(S);
		}
		if(fabs(flow-maxflow)<eps) r=mid;
		else l=mid;
	}
	printf("%.0lf\n%.6lf\n",maxflow,P*l);
	
	return 0;
}
