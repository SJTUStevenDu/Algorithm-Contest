/*
DATE : 2013-3-16 
RATING : 3
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

//Orz WJMZBMR && sevenkplus

using namespace std;

const int MAXN = 55000 + 10;
const int MAXM = 400000 + 10;
const int INF = 0x7FFFFFFF>>2;

struct Edge
{
	int to,next,w,rev;
} g[MAXM];
int gn,start[MAXN];

inline void AddEdge(int a,int b,int c)
{
	gn++;g[gn].to=b;g[gn].next=start[a];start[a]=gn;g[gn].w=c;g[gn].rev=gn+1;
	gn++;g[gn].to=a;g[gn].next=start[b];start[b]=gn;g[gn].w=0;g[gn].rev=gn-1;
}

int n,m,S,T;
int vh[MAXN],h[MAXN],delta,flow,sum;
bool flag;

void Aug(int p)
{
	if(p==T)
	{
		flag=true;
		flow+=delta;
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
	S=n+m+1;T=S+1;
	for(int a,i=1;i<=n;i++) 
	{
		scanf("%d",&a);
		AddEdge(S,i,a);
	}
	for(int a,b,c,i=1;i<=m;i++) 
	{
		scanf("%d%d%d",&a,&b,&c);
		AddEdge(i+n,T,c);
		AddEdge(a,i+n,INF);
		AddEdge(b,i+n,INF);
		sum+=c;
	}
	n=T;
	vh[0]=n;
	while(h[S]<n)
	{
		flag=false;
		delta=INF;
		Aug(S);
	}
	printf("%d\n",sum-flow);
	
	return 0;
}
