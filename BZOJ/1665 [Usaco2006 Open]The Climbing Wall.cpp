/*
DATE : 2012-12-12 
RATING : 1
TAG : Shortest Paths
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

const int MAXM = 2000000 + 5;
const int MAXN = 10000 + 5;

int dis(int x1,int y1,int x2,int y2)
{
	return (x1-x2)*(x1-x2)+(y1-y2)*(y1-y2);
}

struct Edge
{
	int next,to,w;
} g[MAXM];
int start[MAXN],gn;

struct point
{
	int x;int y;
} p[MAXN];

bool cmp(point a,point b)
{
	return a.x<b.x;
}

void AddEdge(int a,int b)
{
	gn++;g[gn].to=b;g[gn].next=start[a];start[a]=gn;
}

int n,h;
int dist[MAXN];
bool vis[MAXN];
int q[MAXN],head,tail;

int main()
{
	scanf("%d%d",&h,&n);
	for(int i=1;i<=n;i++) scanf("%d%d",&p[i].x,&p[i].y);
	sort(p+1,p+1+n,cmp);
	for(int i=1;i<n;i++)
		for(int j=i+1;j<=n;j++) 
		{
			if((p[i].x-p[j].x)*(p[i].x-p[j].x)>1000000) break;
			else if(dis(p[i].x,p[i].y,p[j].x,p[j].y)<=1000000) {AddEdge(i,j);AddEdge(j,i);}
		}
	n+=2;
	for(int i=1;i<n-1;i++)
	{
		if(p[i].y<=1000) AddEdge(n-1,i);
		else if(h-p[i].y<=1000) AddEdge(i,n);
	}
	memset(dist,30,sizeof(dist));
	vis[n-1]=1;dist[n-1]=0;q[++tail]=n-1;
	while(head!=tail)
	{
		head=(head+1)%MAXN;
		int p=q[head];
		vis[p]=0;
		for(int i=start[p];i;i=g[i].next)
		{
			int u=g[i].to;
			if(dist[u]>dist[p]+1)
			{
				dist[u]=dist[p]+1;
				if(!vis[u])
				{
						tail=(tail+1)%n;
						q[tail]=u;
				}
			}
		}
	}
	printf("%d\n",dist[n]-1);
	
	return 0;
}
