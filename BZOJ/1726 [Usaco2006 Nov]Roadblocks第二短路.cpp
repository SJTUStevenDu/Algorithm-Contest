/*
DATE : 2013-2-13 
RATING : 2
TAG : SPFA
*/

#include <iostream>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <cmath>
#include <fstream>
#include <string>
#include <algorithm>
#include <iomanip>

//Orz WJMZBMR && sevenkplus

using namespace std;

const int MAXV = 5000 + 5;
const int MAXE = 200000 + 5;

struct Node
{
	int to,next,w;
} g[MAXE];
int gn,start[MAXV];

void AddEdge(int a,int b,int c)
{
	gn++;g[gn].to=b;g[gn].next=start[a];start[a]=gn;g[gn].w=c;
	gn++;g[gn].to=a;g[gn].next=start[b];start[b]=gn;g[gn].w=c;
}

int n,m;
int dist[MAXV],q[MAXV],head,tail,dist1[MAXV];
int ans=1000000000;
bool vis[MAXV];

void Spfa(int v0)
{
	memset(dist,63,sizeof(dist));
	memset(q,0,sizeof(q));
	memset(vis,0,sizeof(vis));
	dist[v0]=0;
	head=0;tail=1;
	q[head]=v0;vis[v0]=1;
	while(head!=tail)
	{
		int p=q[head++];
		if(head==n) head=0;
		vis[p]=0;
		for(int i=start[p];i;i=g[i].next)
		{
			int v=g[i].to;
			if(dist[v]>dist[p]+g[i].w)
			{
				dist[v]=dist[p]+g[i].w;
				if(!vis[v])
				{
					vis[v]=1;
					if(dist[v]<dist[head])
					{
						head--;
						if(head==-1) head+=n;
						q[head]=v;
					}
					else 
					{
						tail++;
						if(tail==n) tail=0;
						q[tail]=v;
					}
				}
			}
		}
	}
}

int main()
{
	scanf("%d%d",&n,&m);
	while(m--)
	{
		int a,b,c;
		scanf("%d%d%d",&a,&b,&c);
		AddEdge(a,b,c);
	}
	Spfa(1);
	memcpy(dist1,dist,sizeof(dist));
	Spfa(n);
	for(int i=1;i<=n;i++) 
	{
		for(int j=start[i];j;j=g[j].next)
		{
			if(dist1[i]+dist[g[j].to]+g[j].w!=dist[1])
			ans=min(ans,dist1[i]+dist[g[j].to]+g[j].w);
		}
	}
	printf("%d\n",ans);
	
	return 0;
}
