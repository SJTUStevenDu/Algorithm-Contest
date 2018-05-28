/*
DATE : 2013-6-3 
RATING : 3
TAG : mincut
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

const int MAXN = 500 * 500 + 10;
const int MAXE = 1000000 + 10;

struct Edge
{
	int next,to,w;
} g[MAXE];
int gn,start[MAXN];

inline void AddEdge(int a,int b,int c)
{
	gn++;g[gn].next=start[a];start[a]=gn;g[gn].to=b;g[gn].w=c;
}

int n;
int S,T,x;
int dist[MAXN],head,tail,q[MAXN];
bool vis[MAXN];

void Spfa()
{
	memset(dist,63,sizeof(dist));
	dist[S]=0;
	q[head=0]=S;tail=1;
	vis[S]=1;
	while(head!=tail)
	{
		int p=q[head++];
		vis[p]=0;
		if(head==MAXN) head=0;
		for(int i=start[p];i;i=g[i].next)
		{
			int v=g[i].to;
			if(dist[v]>dist[p]+g[i].w)
			{
				dist[v]=dist[p]+g[i].w;
				if(!vis[v])
				{
					vis[v]=1;
					if(dist[q[head]]<dist[v])
					{
						q[tail++]=v;
						if(tail==MAXN) tail=0;
					}
					else 
					{
						--head;if(head==-1) head=MAXN-1;
						q[head]=v;
					}
				}
			}
		}
	}
}

inline int f(int i,int j)
{
	return (i-1)*n+j;
}

int main()
{
	scanf("%d",&n);
	S=n*n+1;T=S+1;
	for(int i=1;i<=n;i++) 
	{
		scanf("%d",&x);
		AddEdge(S,f(1,i),x);
	}
	for(int i=1;i<n;i++)
		for(int j=1;j<=n;j++) 
		{
			scanf("%d",&x);
			AddEdge(f(i,j),f(i+1,j),x);
		}
	for(int i=1;i<=n;i++) 
	{
		scanf("%d",&x);
		AddEdge(f(n,i),T,x);
	}
	for(int i=1;i<=n;i++) 
	{
		scanf("%d",&x);
		AddEdge(f(i,1),T,x);
		for(int j=1;j<n;j++) 
		{
			scanf("%d",&x);
			AddEdge(f(i,j+1),f(i,j),x);
		}
		scanf("%d",&x);
		AddEdge(S,f(i,n),x);
	}
	for(int i=1;i<=n;i++) scanf("%d",&x);
	for(int i=1;i<n;i++) 
		for(int j=1;j<=n;j++) 
		{
			scanf("%d",&x);
			AddEdge(f(i+1,j),f(i,j),x);
		}
	for(int i=1;i<=n;i++) scanf("%d",&x);
	for(int i=1;i<=n;i++) 
	{
		scanf("%d",&x);
		for(int j=1;j<n;j++) 
		{
			scanf("%d",&x);
			AddEdge(f(i,j),f(i,j+1),x);
		}
		scanf("%d",&x);
	}
	Spfa();
	printf("%d\n",dist[T]);
	
	return 0;
}
