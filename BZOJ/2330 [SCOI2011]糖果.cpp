/*
DATE : 2013-5-20 
RATING : 2
TAG : ²î·ÖÔ¼Êø 
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

//Orz WJMZBMR && sevenkplus

using namespace std;

const int MAXN = 100000 + 10;

struct Edge
{
	int next,to,w;
} g[MAXN*4];
int gn,start[MAXN];

inline void AddEdge(int a,int b,int c)
{
	gn++;g[gn].next=start[a];start[a]=gn;g[gn].to=b;g[gn].w=c;
}

int n,m,x;
long long ans,dist[MAXN];
bool flag=true;
int head,tail,q[MAXN],inq[MAXN];
bool vis[MAXN];

void spfa()
{
	memset(dist,0,sizeof(dist));
	for(int i=2;i<=n;i++) q[tail++]=i,dist[i]=1;
	while(head!=tail)
	{
		int p=q[head++];
		if(head==MAXN) head=0;
		vis[p]=0;
		for(int i=start[p];i;i=g[i].next)
		{
			int v=g[i].to;
			if(dist[v]>=dist[p]+g[i].w) continue;
			dist[v]=dist[p]+g[i].w;
			++inq[v];
			if(inq[v]>=n) {flag=false;return;}
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
					--head;
					if(head==-1) head+=MAXN;
					q[head]=v;
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
		int a,b;
		scanf("%d%d%d",&x,&a,&b);++a;++b;
		if(x==1)
		{
			AddEdge(a,b,0);
			AddEdge(b,a,0);
		}
		else if(x==2)
		{
			if(a==b) flag=false;
			AddEdge(a,b,1);
		}
		else if(x==3)
		{
			AddEdge(b,a,0);
		}
		else if(x==4) 
		{
			if(a==b) flag=false;
			AddEdge(b,a,1);
		}
		else 
		{
			AddEdge(a,b,0);
		}
	}
	++n;
	for(int i=2;i<=n;i++) AddEdge(1,i,1);
	if(!flag) 
	{
		printf("-1\n");
		return 0;
	}
	spfa();
	for(int i=2;i<=n;i++) ans+=dist[i];
	if(flag) printf("%lld\n",ans);
	else printf("-1\n");
	
	return 0;
}
