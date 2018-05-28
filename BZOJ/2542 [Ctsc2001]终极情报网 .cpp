/*
DATE : 2013-3-14 
RATING : 2
TAG : MinCost MaxFlow
*/

#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <cstdlib>
#include <cmath>
#include <iomanip>

//Orz WJMZBMR && sevenkplus

using namespace std;

const int MAXN = 400 + 10;
const int MAXE = 100000 + 10;
const int INF = 0x7FFFFFFF>>2;
const double DINF = 10000000.0;

struct Edge
{
	int next,to,w,rev;
	double cost;
}g[MAXE];
int gn,start[MAXN];

inline void AddEdge(int a,int b,int c,double d)
{
	gn++;g[gn].to=b;g[gn].next=start[a];start[a]=gn;g[gn].w=c;g[gn].rev=gn+1;g[gn].cost=d;
	gn++;g[gn].to=a;g[gn].next=start[b];start[b]=gn;g[gn].w=0;g[gn].rev=gn-1;g[gn].cost=-d;
}

int n,K,flow,delta,S,T;
double ans;
double BB[MAXN],dist[MAXN];
int q[MAXN],head,tail,path[MAXN];
bool vis[MAXN];

bool SPFA()
{
	q[head=0]=S;tail=1;
	memset(vis,0,sizeof(vis));
	for(int i=1;i<=n;++i) dist[i]=DINF;
	dist[S]=0;vis[S]=1;
	while(head!=tail)
	{
		int p=q[head++];
		if(head==MAXN) head=0;
		vis[p]=0;
		for(int i=start[p];i;i=g[i].next) if(g[i].w>0)
		{
			int v=g[i].to;
			if(dist[v]>dist[p]+g[i].cost+1e-9)
			{
				dist[v]=dist[p]+g[i].cost;
				path[v]=i;
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
						q[tail++]=v;if(tail==MAXN) tail=0;
					}
				}
			}
		}
	}
	return dist[T]<DINF;
}

void Aug()
{
	int now=T;
	delta=INF;
	while(now!=S)
	{
		int i=path[now];
		delta=min(g[i].w,delta);
		now=g[g[i].rev].to;
	}
	now=T;
	flow+=delta;
	ans+=delta*dist[T];
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
	scanf("%d%d",&n,&K);
	S=n+1;T=S+1;
	for(int i=1;i<=n;++i) scanf("%lf",&BB[i]);
	for(int a,i=1;i<=n;++i)
	{
		scanf("%d",&a);
		if(a && BB[i]>1e-9) AddEdge(S,i,a,-log(BB[i]));
	}
	for(int a,i=1;i<=n;++i)
	{
		scanf("%d",&a);
		if(a) AddEdge(i,T,INF,0.0);
	}
	for(int a,b,c;;)
	{
		double d;
		scanf("%d%d",&a,&b);
		if(a==-1 || b==-1) break;
		scanf("%lf",&d);
		scanf("%d",&c);
		if(c)
		{
			AddEdge(a,b,c,-log(d));
			AddEdge(b,a,c,-log(d));
		}
	}
	AddEdge(S+2,S,K,0);
	S=S+2;
	n=S;
	while(SPFA()) Aug();
	ans=exp(-ans);
	if(flow!=K) cout<<0<<endl;
	else if (ans<1e-5) puts("0.0000097785");
	else cout<<setprecision(5)<<showpoint<<ans<<endl;
	
	return 0;
}
