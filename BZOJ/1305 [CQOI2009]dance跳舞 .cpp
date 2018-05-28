/*
DATE : 2013-5-27 
RATING : 2
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

const int MAXN = 200 + 10;
const int INF = 0x7FFFFFFF>>2;

struct Edge
{
	int next,to,w;
} g[10000+10];
int start[MAXN],gn;

inline void AddEdge(int a,int b,int c)
{
	gn++;g[gn].next=start[a];start[a]=gn;g[gn].to=b;g[gn].w=c;
	gn++;g[gn].next=start[b];start[b]=gn;g[gn].to=a;g[gn].w=0;
}

int n,K,S,T,ans,N;
int maxflow,flow,h[MAXN],vh[MAXN];
bool flag;
char Map[MAXN][MAXN];

void Aug(int p)
{
	if(p==T)
	{
		maxflow+=flow;
		flag=1;
		return;
	}
	int minnode=N-1,tmp=flow,i;
	for(i=start[p];i;i=g[i].next) if(g[i].w>0)
	{	
		int v=g[i].to;
		if(h[p]==h[v]+1)
		{
			flow=min(flow,g[i].w);
			Aug(v);
			if(h[S]>=N) return;
			if(flag) break;
			flow=tmp;
		}
		minnode=min(minnode,h[v]);
	}
	if(flag)
	{
		g[i].w-=flow;
		g[i^1].w+=flow;
	}
	else 
	{
		vh[h[p]]--;
		if(vh[h[p]]==0) h[S]=N;
		h[p]=minnode+1;
		vh[h[p]]++;
	}
}

bool check(int x)
{
	//i->i i'->i+n j->j+n*2 j'->j+n*3
	memset(start,0,sizeof(start));
	gn=1;
	for(int i=1;i<=n;i++)
		for(int j=1;j<=n;j++) 
			if(Map[i][j]=='Y') AddEdge(i,j+n*2,1);else AddEdge(i+n,j+n*3,1);
	for(int i=1;i<=n;i++) AddEdge(i,i+n,K);
	for(int i=1;i<=n;i++) AddEdge(i+n*3,i+n*2,K);
	for(int i=1;i<=n;i++) AddEdge(S,i,x);
	for(int i=1;i<=n;i++) AddEdge(i+2*n,T,x);
	memset(vh,0,sizeof(vh));
	memset(h,0,sizeof(h));
	
	vh[0]=N;
	maxflow=0;
	while(h[S]<N)
	{
		flow=INF;
		flag=false;
		Aug(S);
	}
	return maxflow==x*n;
}

int main()
{
	scanf("%d%d",&n,&K);
	for(int i=1;i<=n;i++) scanf("%s",Map[i]+1);
	S=4*n+1;T=4*n+2;
	N=4*n+2;
	int l=1,r=n;
	while(l<=r) 
	{
		int mid=(l+r)>>1;
		if(check(mid)) l=mid+1;
		else r=mid-1;
	}
	printf("%d\n",r);
	
	return 0;
}
