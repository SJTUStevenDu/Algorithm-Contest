/*
DATE : 2012-12-16 
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

const int MAXN = 50000 + 5;
const int MAXM = 200000 + 5;

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

int n,m,b;
int dist[MAXN],q[MAXN],head,tail;
bool vis[MAXN];

int main()
{
	scanf("%d%d%d",&n,&m,&b);
	for(int i=1;i<=m;i++) 
	{
		int x,y,z;
		scanf("%d%d%d",&x,&y,&z);
		AddEdge(x,y,z);
	}
	memset(dist,30,sizeof(dist));
	vis[1]=1;q[++tail]=1;dist[1]=0;
	while(head!=tail)
	{
		head=(head+1)%MAXN;
		int p=q[head];
		vis[p]=0;
		for(int i=start[p];i;i=g[i].next) if(dist[g[i].to]>dist[p]+g[i].w)
		{
			dist[g[i].to]=dist[p]+g[i].w;
			if(!vis[g[i].to]) tail=(tail+1)%MAXN,q[tail]=g[i].to,vis[g[i].to]=1;
		}
	}
	for(int i=1;i<=b;i++) 
	{
		int x,y;
		scanf("%d%d",&x,&y);
		printf("%d\n",dist[x]+dist[y]);
	}
	
	return 0;
}
