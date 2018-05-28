/*
DATE : 2013-3-13 
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
#include <fstream>
#include <string>
#include <map>
#include <queue>

//Orz WJMZBMR && sevenkplus

using namespace std;

const int MAXN = 500 + 10;
const int MAXM = 1000 + 10;
const int INF = 0x7FFFFFFF>>3;

struct Edge
{
	int next,to,w,rev;
} g[MAXM*4];
int gn,start[MAXN];

void AddEdge(int a,int b,int c)
{
	gn++;g[gn].to=b;g[gn].next=start[a];start[a]=gn;g[gn].w=c;g[gn].rev=gn+1;
	gn++;g[gn].to=a;g[gn].next=start[b];start[b]=gn;g[gn].w=0;g[gn].rev=gn-1;
}

int n,m,e[MAXM][3],S,T,K,KK;
int h[MAXN],vh[MAXN],delta,flow;
bool flag;

void Aug(int p)
{
	if(p==T)
	{
		flow+=delta;
		flag=true;
		return;
	}
	int i,minnode=n-1,tmp=delta;
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
		if(!vh[h[p]]) h[S]=n;
		h[p]=minnode+1;
		vh[h[p]]++;
	}
}

int main()
{
	scanf("%d%d%d",&n,&m,&KK);
	for(int i=1;i<=m;++i)
		scanf("%d%d%d",&e[i][0],&e[i][1],&e[i][2]);
	S=e[KK][0],T=e[KK][1];K=e[KK][2];
	for(int i=1;i<=m;++i) 
		if(i!=KK && e[i][2]<=K)
		{
			AddEdge(e[i][1],e[i][0],K-e[i][2]+1);
			AddEdge(e[i][0],e[i][1],K-e[i][2]+1);
		}
	while(h[S]<n)
	{
		delta=INF;
		flag=false;
		Aug(S);
	}
	printf("%d\n",flow);
	
	return 0;
}
