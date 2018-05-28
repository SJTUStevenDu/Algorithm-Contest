/*
DATE : 2013-3-19 
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

const int MAXN = 20000 + 10;
const int MAXM = 400000 + 10;
const int INF = 0x7FFFFFFF>>2;

struct Edge
{
	int next,to,w,rev;
} g[MAXM];
int gn,start[MAXN];

inline void AddEdge(int a,int b,int c)
{
	gn++;g[gn].to=b;g[gn].next=start[a];start[a]=gn;g[gn].w=c;g[gn].rev=gn+1;
	gn++;g[gn].to=a;g[gn].next=start[b];start[b]=gn;g[gn].w=1;g[gn].rev=gn-1;
}

int n,m,S,T,L,ans,h[MAXN],vh[MAXN];
int e[MAXM/2][3];
bool flag;

inline int GetInt()
{
	char ch=0;
	int re=0;
	for(;ch>'9' || ch<'0';ch=getchar());
	for(;ch<='9' && ch>='0';ch=getchar()) re=re*10+ch-'0';
	return re;
}

int delta;

void Aug(int p)
{
	if(p==T)
	{
		ans+=delta;
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
			if(h[S]>=n) return ;
			if(flag) break;
			delta=tmp;
		}
		minnode=min(minnode,h[v]);
	}
	if(flag)
	{
		g[g[i].rev].w+=delta;
		g[i].w-=delta;
	}
	else 
	{
		--vh[h[p]];
		if(vh[h[p]]==0) h[S]=n;
		h[p]=minnode+1;
		++vh[h[p]];
	}
}

int main()
{
	n=GetInt();m=GetInt();
	for(int i=1;i<=m;++i)
	{
		e[i][0]=GetInt();
		e[i][1]=GetInt();
		e[i][2]=GetInt();
	}
	S=GetInt();T=GetInt();L=GetInt();
	for(int i=1;i<=m;++i)
	{
		if(e[i][2]<L) AddEdge(e[i][0],e[i][1],1);
	}
	vh[0]=n;
	while(h[S]<n)
	{
		delta=INF;
		flag=false;
		Aug(S);
	}
	gn=0;
	memset(start,0,sizeof(start));
	memset(h,0,sizeof(h));
	memset(vh,0,sizeof(vh));
	for(int i=1;i<=m;++i)
	{
		if(e[i][2]>L) AddEdge(e[i][0],e[i][1],1);
	}
	vh[0]=n;
	while(h[S]<n)
	{
		delta=INF;
		flag=false;
		Aug(S);
	}
	printf("%d\n",ans);
	
	return 0;
}
