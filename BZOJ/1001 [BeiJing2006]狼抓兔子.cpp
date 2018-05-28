/*
DATE : 2013-3-17 
RATING : 3
TAG : 平面图最小割 
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
#include <map>
#include <vector>

//Orz WJMZBMR && sevenkplus

using namespace std;

const int MAXN = 2000000 + 10;
const int MAXE = 3000000 + 10;

struct Edge
{
	int next,to,w;
} g[MAXE];
int gn,start[MAXN];

void AddEdge(int a,int b,int c)
{
	gn++;g[gn].to=b;g[gn].next=start[a];start[a]=gn;g[gn].w=c;
}

int n,m,S,T,a;
int dist[MAXN],q[MAXN],head,tail;
bool vis[MAXN];

inline int f(int i,int j,int Type)
{
	return ((i-1)*m+j-1)*2+Type;
}

int main()
{
	scanf("%d%d",&n,&m);
	S=f(n,m,2)+1;T=S+1;
	if(n==1 || m==1)
	{
		int maxx=0x7FFFFFFF>>2;
		if(n==1)
		{ 
			for(int i=1;i<m;i++) scanf("%d",&a), maxx=min(maxx,a);
		}
		else for(int i=1;i<n;i++) scanf("%d",&a), maxx=min(maxx,a);
		printf("%d\n",maxx);
		return 0;
	}
	for(int i=1;i<=n;i++) 
		for(int j=1;j<m;j++)
		{
			scanf("%d",&a);
			if(i==1) AddEdge(f(i,j,2),T,a);
			else if(i==n) AddEdge(S,f(i-1,j,1),a);
			else AddEdge(f(i,j,2),f(i-1,j,1),a);
		}
	for(int i=1;i<n;i++) 
		for(int j=1;j<=m;j++) 
		{
			scanf("%d",&a);
			if(j==1) AddEdge(S,f(i,j,1),a);
			else if(j==m) AddEdge(f(i,j-1,2),T,a);
			else AddEdge(f(i,j-1,2),f(i,j,1),a);
		}
	for(int i=1;i<n;i++)
		for(int j=1;j<m;j++)
		{
			scanf("%d",&a);
			AddEdge(f(i,j,1),f(i,j,2),a);
		}
	memset(dist,63,sizeof(dist));
	q[head]=S;vis[S]=1;dist[S]=0;tail=1;
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
					vis[v]=1;
					if(dist[v]<dist[q[head]])
					{
						--head;if(head==-1) head=MAXN-1;
						q[head]=v;
					}
					else 
					{
						q[++tail]=v;if(tail==MAXN) tail=0;
					}
				}
			}
		}
	}
	printf("%d\n",dist[T]);
	
	return 0;
}
