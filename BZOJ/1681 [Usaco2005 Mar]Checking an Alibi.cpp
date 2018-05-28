/*
DATE : 2012-12-14 
RATING : 1
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

using namespace std;

const int MAXN = 500 + 5;
const int MAXM = 1000 * 2 + 5;

struct Edge
{
	int to,next,w;
} g[MAXM];
int start[MAXN],gn;

void AddEdge(int a,int b,int c)
{
	gn++;g[gn].to=b;g[gn].next=start[a];start[a]=gn;g[gn].w=c;
	gn++;g[gn].to=a;g[gn].next=start[b];start[b]=gn;g[gn].w=c;
}

int n,m,c,t;
int dist[MAXN],ans[MAXN];
bool vis[MAXN];
int q[MAXN],head,tail;

int main()
{
	scanf("%d%d%d%d",&n,&m,&c,&t);
	for(int i=1;i<=m;i++) 
	{
		int x,y,z;
		scanf("%d%d%d",&x,&y,&z);
		AddEdge(x,y,z);
	}
	memset(dist,25,sizeof(dist));
	q[++tail]=1;vis[1]=1;dist[1]=0;
	while(head!=tail)
	{
		head=(head+1)%MAXN;
		int p=q[head];
		vis[p]=0;
		for(int i=start[p];i;i=g[i].next)
		{
			int u=g[i].to;
			if(dist[u]>dist[p]+g[i].w)
			{
				dist[u]=dist[p]+g[i].w;
				if(!vis[u]) tail=(tail+1)%MAXN,q[tail]=u;vis[u]=1;
			}
		}
	}
	for(int i=1;i<=c;i++)
	{
		int a;
		scanf("%d",&a);
		if(dist[a]<=t) ans[++ans[0]]=i;
	}
	for(int i=0;i<=ans[0];i++) printf("%d\n",ans[i]);
	
	return 0;
}
