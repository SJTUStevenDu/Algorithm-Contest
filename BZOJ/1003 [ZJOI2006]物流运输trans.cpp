/*
DATE : 2013-3-28 
RATING : 3
TAG : DP
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

const int MAXN = 100 + 10;
const int MAXV = 20 + 10;
const int MAXE = 400 + 10;
const int INF = 0x7FFFFFFF>>2;

struct Edge
{
	int next,to,w;
} g[MAXE];
int gn,start[MAXV];

inline void AddEdge(int a,int b,int c)
{
	gn++;g[gn].next=start[a];start[a]=gn;g[gn].to=b;g[gn].w=c;
}

int n,m,f[MAXN],K,E,D,dist[MAXV],head,tail,q[MAXV],dp[MAXN];
bool able[MAXV],vis[MAXV];
int unable[MAXE][3];

void ReBuild(int dayl,int dayr)
{
	memset(able,0,sizeof(able));
	for(int i=1;i<=D;++i)
		if(max(unable[i][1],dayl)<=min(dayr,unable[i][2])) able[unable[i][0]]=1;
}

void SPFA()
{
	memset(vis,0,sizeof(vis));
	for(int i=1;i<=m;i++) dist[i]=INF;
	head=0;tail=1;
	q[head]=1;dist[1]=0;vis[1]=1;
	while(head!=tail)
	{
		int p=q[head++];
		if(head==MAXV) head=0;
		vis[p]=0;
		for(int i=start[p];i;i=g[i].next)
		{
			int v=g[i].to;
			if(able[v]) continue;
			if(dist[v]>dist[p]+g[i].w)
			{
				dist[v]=dist[p]+g[i].w;
				if(!vis[v])
				{
					
					vis[v]=1;
					if(dist[q[head]]<dist[v])
					{
						q[tail++]=v;if(tail==MAXV) tail=0;
					}
					else 
					{
						--head;if(head==-1) head+=MAXV;
						q[head]=v;
					}
				}
			}
		}
	}
}

int main()
{
	scanf("%d%d%d%d",&n,&m,&K,&E);
	while(E--)
	{
		int a,b,c;
		scanf("%d%d%d",&a,&b,&c);
		AddEdge(a,b,c);AddEdge(b,a,c);
	}
	scanf("%d",&D);
	for(int i=1;i<=D;i++) scanf("%d%d%d",&unable[i][0],&unable[i][1],&unable[i][2]);
	for(int i=1;i<=n;i++) 
	{
		ReBuild(1,i);
		SPFA();
		if(dist[m]>=INF) dp[i]=INF;
		else dp[i]=dist[m]*i;
		for(int j=2;j<i;j++)
		{
			ReBuild(j+1,i);
			SPFA();
			if(dist[m]<INF) dp[i]=min(dp[i],dp[j]+K+dist[m]*(i-j));
		}
	}
	printf("%d\n",dp[n]);
	
	return 0;
}
