/*
DATE : 2013-3-20 
RATING : 3
TAG : MaxFlow
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

const int MAXN = 45;
const int MAXV = MAXN * MAXN;
const int MAXE = 100000 + 10;
const long long INF = 123456789876LL;
const int gx[4]={1,0,-1,0};
const int gy[4]={0,1,0,-1};

struct Edge
{
	int next,to;
	long long w;
} g[MAXE];
int gn,start[MAXV];

inline void AddEdge(int a,int b,long long c)
{
	gn++;g[gn].next=start[a];start[a]=gn;g[gn].to=b;g[gn].w=c;
	gn++;g[gn].next=start[b];start[b]=gn;g[gn].to=a;g[gn].w=0;
}

int n,m,S,T,Kase;
long long delta,flow,maxx,step;
long long mid,sum1,sum2;
long long Map[MAXN][MAXN];
int vh[MAXV],h[MAXV];
bool flag;

inline int f(int i,int j)
{
	return m*(i-1)+j;
}

void Aug(int p)
{
	if(p==T)
	{
		flag=true;
		flow+=delta;
		return;
	}
	int i,minnode=T-1;
	long long tmp=delta;
	for(i=start[p];i;i=g[i].next) if(g[i].w>0)
	{
		int v=g[i].to;
		if(h[p]==h[v]+1)
		{
			delta=min(delta,g[i].w);
			Aug(v);
			if(h[S]>=T) return;
			if(flag) break;
			delta=tmp;
		}
		minnode=min(minnode,h[v]);
	}
	if(flag)
	{
		g[i].w-=delta;
		g[i^1].w+=delta;
	}
	else 
	{
		if(--vh[h[p]]==0) h[S]=T;
		h[p]=minnode+1;++vh[h[p]];
	}
}

bool check()
{
	gn=1;
	memset(vh,0,sizeof(vh));
	memset(h,0,sizeof(h));
	memset(start,0,sizeof(start));
	flow=0;
	vh[0]=T;
	step=0;
	for(int i=1;i<=n;i++)
		for(int j=1;j<=m;j++)
		{
			step+=(mid-Map[i][j]);
			if((i+j)&1) 
			{
				AddEdge(S,f(i,j),mid-Map[i][j]);
				for(int k=0;k<4;k++) 
				{
					int px=i+gx[k],py=j+gy[k];
					if(px>0 && px<=n && py>0 && py<=m) AddEdge(f(i,j),f(px,py),INF);
				}
			}
			else AddEdge(f(i,j),T,mid-Map[i][j]);
		}
	while(h[S]<T)
	{
		delta=INF;
		flag=false;
		Aug(S);
	}
	return 2*flow==step;
}

int main()
{
	scanf("%d",&Kase);
	while(Kase--)
	{
		scanf("%d%d",&n,&m);
		S=n*m+1;T=S+1;
		sum1=sum2=maxx=0LL;
		for(int i=1;i<=n;i++)
		{
			for(int j=1;j<=m;j++) 
			{
				scanf("%lld",&Map[i][j]);
				if((i+j)&1) sum1+=Map[i][j];
				else sum2+=Map[i][j];
				if(maxx<Map[i][j]) maxx=Map[i][j];
			}
		}
		if(!(n&1) || !(m&1)) 
		{
			if(sum1!=sum2)
			{
				printf("-1\n");
				continue;
			}
			long long l=maxx,r=INF;
			while(l<=r)
			{
				mid=(l+r)/2;
				if(check()) r=mid-1;
				else l=mid+1;
			}
			mid=l;
			if(!check()) printf("-1\n");
			else printf("%lld\n",step/2);
		}
		else 
		{
			mid=sum2-sum1;
			if(mid<maxx || !check())
			{
				printf("-1\n");
				continue;
			}
			printf("%lld\n",step/2);
		}
	}
	
	return 0;
}
