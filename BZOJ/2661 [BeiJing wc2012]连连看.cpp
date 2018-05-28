/*
DATE : 2013-3-6 
RATING : 3
TAG : 二分图最优匹配 
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

const int MAXN = 2000 + 10;
const int MAXM = 50000 + 10;
const int INF = 1000000000;

int gcd(int x,int y)
{
	int tmp;
	while(y)
	{
		tmp=y;
		y=x%y;
		x=tmp;
	}
	return x;
}

int A,B,pn,S,T,ans,X[MAXN],Y[MAXN],cnt;
int sqr[1000*1000+5];

struct Edge
{
	int next,to,w,cost,rev;
} g[MAXM];
int gn,start[MAXN];

void AddEdge(int a,int b,int c,int d)
{
	gn++;g[gn].to=b;g[gn].next=start[a];start[a]=gn;g[gn].w=c;g[gn].cost=d;g[gn].rev=gn+1;
	gn++;g[gn].to=a;g[gn].next=start[b];start[b]=gn;g[gn].w=0;g[gn].cost=-d;g[gn].rev=gn-1;
}

inline void NewNode(int &p) {p=++pn;}

int q[MAXN],head,tail,dist[MAXN],path[MAXN];
bool vis[MAXN];

bool SPFA()
{
	q[head=0]=S;tail=1;
	memset(dist,63,sizeof(dist));
	memset(vis,0,sizeof(vis));
	vis[S]=1;dist[S]=0;
	while(head!=tail)
	{
		int p=q[head++];
		if(head==MAXN) head=0;
		vis[p]=0;
		for(int i=start[p];i;i=g[i].next) if(g[i].w>0)
		{
			int v=g[i].to;
			if(dist[v]>dist[p]+g[i].cost)
			{
				dist[v]=dist[p]+g[i].cost;
				path[v]=i;
				if(!vis[v])
				{
					vis[v]=1;
					q[tail++]=v;
					if(tail==MAXN) tail=0;
				}
			}
		}
	}
	return dist[T]<INF;
}

void Aug()
{
	int delta=INF;
	int now=T;
	while(now!=S)
	{
		int i=path[now];
		delta=min(delta,g[i].w);
		now=g[g[i].rev].to;
	}
	cnt+=delta;
	now=T;
	ans+=dist[T]*delta;
	while(now!=S)
	{
		int i=path[now];
		g[i].w-=delta;
		g[g[i].rev].w+=delta;
		now=g[g[i].rev].to;
	}
}

int main()
{
	scanf("%d%d",&A,&B);
	for(int i=1;i<=1000;i++) sqr[i*i]=i;
	NewNode(S);NewNode(T);
	for(int i=A;i<=B;i++)
	{
		NewNode(X[i]);NewNode(Y[i]);
		for(int j=A;j<i;j++)
		{
			int k=sqr[i*i-j*j];
			if(k && gcd(j,k)==1) AddEdge(X[j],Y[i],1,-i-j),AddEdge(X[i],Y[j],1,-i-j);
		}
	}
	for(int i=A;i<=B;i++) AddEdge(S,X[i],1,0),AddEdge(Y[i],T,1,0);
	while(SPFA()) Aug();
	printf("%d %d\n",cnt/2,-ans/2);
	
	return 0;
}
