/*
DATE : 2013-1-1 
RATING : 2
TAG : Minimal Spanning Tree
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

//Orz WJMZBMR && sevenkplus

using namespace std;

const int MAXN = 1000 + 5;

struct Edge
{
	int st,en;
	double len;
} g[MAXN*(MAXN-1)/2];

bool cmp(Edge a,Edge b)
{
	return a.len<b.len;
}

struct POINT
{
	int x,y;
} p[MAXN];

int n,father[MAXN],cnt,m;
double ans;

double dist(POINT a,POINT b)
{
	return sqrt((a.x-b.x)*1.0*(a.x-b.x)+(a.y-b.y)*1.0*(a.y-b.y));
}

int getfather(int x)
{
	if(father[x]==x) return father[x];
	else return father[x]=getfather(father[x]);
}

int main()
{
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++) scanf("%d%d",&p[i].x,&p[i].y),father[i]=i;
	for(int i=1;i<=n;i++) 
	{
		for(int j=1;j<i;j++) 
		{
			g[++cnt].st=i;g[cnt].en=j;
			g[cnt].len=dist(p[i],p[j]);
		}
	}
	while(m--)
	{
		int a,b;
		scanf("%d%d",&a,&b);
		father[getfather(a)]=getfather(b);
	}
	sort(g+1,g+cnt+1,cmp);
	for(int i=1;i<=cnt;i++)
	{
		int a=g[i].st,b=g[i].en;
		if(getfather(a)!=getfather(b))
		{
			father[getfather(a)]=getfather(b);
			ans+=g[i].len;
		}
	}
	printf("%.2lf\n",ans);
	
	return 0;
}
