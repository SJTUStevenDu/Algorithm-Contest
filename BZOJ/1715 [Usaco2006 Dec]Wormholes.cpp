/*
DATE : 2013-1-24 
RATING : 2
TAG : SPFA
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

//Orz WJMZBMR && sevenkplus

using namespace std;

const int MAXN = 500 + 5;
const int MAXE = 6000 + 5;

struct Edge
{
	int next,to,w;
} g[MAXE];
int gn,start[MAXN];

void AddEdge(int a,int b,int c)
{
	gn++;g[gn].w=c;g[gn].to=b;g[gn].next=start[a];start[a]=gn;
}

int n,m,w,T;
int dist[MAXN],in[MAXN];
bool vis[MAXN],ans;
int q[MAXN],head,tail;

int main()
{
	scanf("%d",&T);
	while(T--)
	{
		scanf("%d%d%d",&n,&m,&w);
		memset(start,0,sizeof(start));
		memset(dist,25,sizeof(dist));
		memset(vis,0,sizeof(vis));
		memset(q,0,sizeof(q));
		memset(in,0,sizeof(in));
		head=0;tail=1;ans=false;gn=0;
		for(int a,b,c,i=1;i<=m;i++)
		{
			scanf("%d%d%d",&a,&b,&c);
			AddEdge(a,b,c);
			AddEdge(b,a,c);
		}
		for(int a,b,c,i=1;i<=w;i++)
		{
			scanf("%d%d%d",&a,&b,&c);
			AddEdge(a,b,-c);
		}
		q[head]=1;vis[1]=1;in[1]=1;dist[1]=0;
		while(head!=tail)
		{
			int p=q[head];
			vis[p]=0;
			if(in[p]>n || dist[1]<0)
			{
				ans=true;
				break;
			}
			head=(head+1)%MAXN;
			for(int i=start[p];i;i=g[i].next)
			{
				int v=g[i].to;
				if(dist[v]>dist[p]+g[i].w)
				{
					dist[v]=dist[p]+g[i].w;
					if(!vis[v]) q[tail]=v,in[v]++,vis[v]=1,tail=(tail+1)%MAXN;
				}
			}
		}
		if(ans) printf("YES\n");
		else printf("NO\n");
	}
	
	return 0;
}
