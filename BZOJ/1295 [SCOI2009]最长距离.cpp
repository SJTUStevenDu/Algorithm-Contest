/*
DATE : 2013-5-21 
RATING : 2
TAG : SPFA
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

const int MAXN = 30 * 30 + 10;
const int MAXE = MAXN * MAXN * 4;
const int gx[4]={1,0,-1,0};
const int gy[4]={0,1,0,-1};

inline double Getdist(int x1,int y1,int x2,int y2) {return sqrt((x1-x2)*(x1-x2)+(y1-y2)*(y1-y2));}

struct Edge
{
	int next,to,w;
} g[MAXE];
int gn,start[MAXN];

inline void AddEdge(int a,int b,int c)
{
	gn++;g[gn].next=start[a];start[a]=gn;g[gn].to=b;g[gn].w=c;
}

int n,m,T;
bool Disabled[MAXN];
double ans;

inline int f(int i,int j) {return (i-1)*m+j;}
inline bool InGraph(int x,int y) {return x>0 && x<=n && y>0 && y<=m;}

int dist[MAXN],q[MAXN],head,tail;
bool vis[MAXN];

void SPFA(int v0)
{
	head=0;tail=1;q[head]=v0;
	memset(vis,0,sizeof(vis));
	memset(dist,63,sizeof(dist));
	vis[v0]=1;dist[v0]=0;
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

int main()
{
	scanf("%d%d",&n,&m);
	scanf("%d",&T);
	char ch=getchar();
	for(int i=1;i<=n;i++)
	{
		for(;ch!='0' && ch!='1';ch=getchar());
		for(int j=1;j<=m;j++) Disabled[f(i,j)]=ch-'0',ch=getchar();
	}
	for(int i=1;i<=n;i++) 
		for(int j=1;j<=m;j++) 
			for(int k=0;k<4;k++)
			{
				int px=i+gx[k];
				int py=j+gy[k];
				if(!InGraph(px,py)) continue;
				AddEdge(f(i,j),f(px,py),Disabled[f(i,j)]+Disabled[f(px,py)]);
			}
	for(int i=1;i<=n;i++)
		for(int j=1;j<=m;j++) if(!Disabled[f(i,j)])
		{
			SPFA(f(i,j));
			for(int ii=1;ii<=n;ii++)
				for(int jj=1;jj<=m;jj++) if(i!=ii && j!=jj)
					if(dist[f(ii,jj)]<=T*2) ans=max(ans,Getdist(i,j,ii,jj));
		}
	printf("%.6lf\n",ans);
	
	return 0;
}
