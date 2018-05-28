/*
DATE : 2013-3-29 
RATING : 2
TAG : ²î·ÖÔ¼Êø 
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

const int MAXN = 200 + 10;
const int MAXE = 10000 + 10;

struct Edge
{
	int next,to,w;
} g[MAXE];
int gn,start[MAXN];

inline void AddEdge(int a,int b,int c)
{
	gn++;g[gn].to=b;g[gn].next=start[a];start[a]=gn;g[gn].w=c;
}

int n,m,T;
int q[MAXN],head,tail,inq[MAXN],dist[MAXN],S;
bool vis[MAXN];

bool SPFA()
{
	memset(dist,63,sizeof(dist));
	memset(vis,0,sizeof(vis));
	memset(inq,0,sizeof(inq));
	vis[S]=1;head=0;tail=1;dist[S]=0;q[head]=S;
	while(head!=tail)
	{
		int p=q[head++];
		if(head==MAXN) head=0;
		vis[p]=0;
		for(int i=start[p];i;i=g[i].next)
		{
			int v=g[i].to;
			if(dist[v]>dist[p]+g[i].w)
			{
				dist[v]=dist[p]+g[i].w;
				if(!vis[v])
				{
					vis[v]=1;q[tail++]=v;
					if(tail==MAXN) tail=0;
					if(++inq[v]>=n) return true;
				}
			}
		}
	}
	return false;
}

int main()
{
	scanf("%d",&T);
	while(T--)
	{
		gn=0;
		memset(start,0,sizeof(start));
		scanf("%d%d",&n,&m);
		while(m--)
		{
			int a,b,c;
			scanf("%d%d%d",&a,&b,&c);
			--a;
			AddEdge(a,b,c);
			AddEdge(b,a,-c);
		}
		S=n+1;
		for(int i=0;i<=n;i++) AddEdge(S,i,0);
		if(SPFA()) printf("false\n");else printf("true\n");
	}
	
	return 0;
}
