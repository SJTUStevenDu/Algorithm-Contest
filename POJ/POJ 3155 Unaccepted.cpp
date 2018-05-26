#include <iostream>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <cmath>
#include <algorithm>
#include <fstream>

//实际上应该是对的，被卡精度，不知道该怎么弄了T_T 

using namespace std;

const int MAXN = 2000 + 10;
const int MAXM = 10000 + 20;
const double INF = 1e10;

struct Edge
{
	int next,to;
	double w;
} g[MAXM];
int gn,start[MAXN];

inline void AddEdge(int a,int b,double c)
{
	gn++;g[gn].next=start[a];start[a]=gn;g[gn].to=b;g[gn].w=c;
	gn++;g[gn].next=start[b];start[b]=gn;g[gn].to=a;g[gn].w=0;
}

int n,m,vh[MAXN],h[MAXN],S,T,N,e[MAXM][2],cnt;
bool vis[MAXN];
double ans;

double Aug(int p,double flow)
{
	if(p==T) return flow;
	int minnode=N-1;
	double l=flow;
	for(int i=start[p];i;i=g[i].next) if(g[i].w>0)
	{
		int v=g[i].to;
		if(h[p]==h[v]+1)
		{
			double f=Aug(v,min(l,g[i].w));
			l-=f;
			g[i].w-=f;
			g[i^1].w+=f;
			if(l<1e-7 || h[S]>=N) return flow-l;
		}
		minnode=min(minnode,h[v]);
	}
	if(flow==l)
	{
		if(--vh[h[p]]==0) h[S]=N;
		++vh[h[p]=minnode+1];
	}
	return flow-l;
}

double check(double mid)
{
	double res=m;
	gn=1;ans=0;
	memset(h,0,sizeof(h));
	memset(vh,0,sizeof(vh));
	memset(start,0,sizeof(start));
	for(int i=1;i<=n;i++) AddEdge(i,T,mid);
	for(int i=1;i<=m;i++) AddEdge(S,i+n,1);
	for(int i=1;i<=m;i++) AddEdge(i+n,e[i][0],INF),AddEdge(i+n,e[i][1],INF);
	vh[0]=N;
	while(h[S]<N) res-=Aug(S,INF);
	return res;
}

int main()
{
	scanf("%d%d",&n,&m);
	if(m==0)
	{
		printf("1\n1\n");
		return 0;
	}
	for(int i=1;i<=m;i++) scanf("%d%d",&e[i][0],&e[i][1]);
	S=n+m+1;T=S+1;N=T;
	double l=0,r=INF;
	while(r-l>1e-6)
	{
		double mid=(l+r)/2;
		if(check(mid)>0) l=mid;
		else r=mid;
	}
	check(l);
	for(int p=1;p<=n;p++) 
		for(int i=start[p];i;i=g[i].next) if(g[i].to==T && g[i].w<1e-7) ++cnt,vis[p]=1;
	printf("%d\n",cnt);
	for(int i=1;i<=n;i++) if(vis[i]) printf("%d\n",i);
	
	return 0;
}
