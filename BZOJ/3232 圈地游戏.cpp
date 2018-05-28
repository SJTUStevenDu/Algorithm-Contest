#include <iostream>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <cmath>
#include <algorithm>
#include <fstream>

using namespace std;

const int MAXC = 55;
const int MAXN = MAXC * MAXC + 10;
const int MAXE = 30000 + 10;
const double INF = 1e10;
const double eps = 1e-11;

struct Edge
{
	int next,to;
	long double w;
} g[MAXE];
int gn,start[MAXN];

inline void AddEdge(int a,int b,long double c)
{
	gn++;g[gn].to=b;g[gn].next=start[a];start[a]=gn;g[gn].w=c;
}

int n,m,S,T,N;
int A[MAXC][MAXC],B[MAXC][MAXC],C[MAXC][MAXC],vh[MAXN],h[MAXN],idx[MAXC][MAXC];

long double Aug(int p,long double flow)
{
	if(p==T) return flow;
	long double l=flow;
	int minnode=N-1;
	for(int i=start[p];i;i=g[i].next) 
	{
		int v=g[i].to;
		if(h[p]==h[v]+1 && g[i].w>0)
		{
			long double f=Aug(v,min(l,g[i].w));
			l-=f;
			g[i].w-=f;
			g[i^1].w+=f;
			if(l==0 || h[S]>=N) return flow-l;
		}
		if(g[i].w>0) minnode=min(minnode,h[v]);
	}
	if(l==flow)
	{
		--vh[h[p]];
		if(vh[h[p]]==0) h[S]=N;
		h[p]=minnode+1;
		vh[h[p]]++;
	}
	return flow-l;
}

bool check(double x)
{
	gn=1;
	memset(start,0,sizeof(start));
	long double res=0;
	for(int i=0;i<=n+1;i++) 
		for(int j=0;j<=m+1;j++)
			if(!i || !j || i==n+1 || j==m+1) AddEdge(idx[i][j],T,INF),AddEdge(T,idx[i][j],0);
			else AddEdge(S,idx[i][j],A[i][j]),AddEdge(idx[i][j],S,0),res+=A[i][j];
	for(int i=0;i<=n;i++)
		for(int j=1;j<=m;j++) AddEdge(idx[i][j],idx[i+1][j],B[i][j]*x),AddEdge(idx[i+1][j],idx[i][j],B[i][j]*x);
	for(int i=1;i<=n;i++)
		for(int j=0;j<=m;j++) AddEdge(idx[i][j],idx[i][j+1],C[i][j]*x),AddEdge(idx[i][j+1],idx[i][j],C[i][j]*x);
	memset(h,0,sizeof(h));
	memset(vh,0,sizeof(vh));
	vh[0]=N;
	while(h[S]<N) res-=Aug(S,INF);
	return res<1e-9;
}

int main()
{
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++) 
		for(int j=1;j<=m;j++) scanf("%d",&A[i][j]);
	for(int i=0;i<=n;i++)
		for(int j=1;j<=m;j++) scanf("%d",&B[i][j]);
	for(int i=1;i<=n;i++)
		for(int j=0;j<=m;j++) scanf("%d",&C[i][j]);
	S=1;
	for(int i=0;i<=n+1;i++)
		for(int j=0;j<=m+1;j++) idx[i][j]=S++;
	T=S+1;
	N=T;
	double l=0.0,r=n*m*100;
	while(r-l>1e-6)
	{
		double mid=(l+r)/2;
		if(check(mid)) r=mid;else l=mid;
	}
	printf("%.3lf\n",l);
	
	return 0;
}
