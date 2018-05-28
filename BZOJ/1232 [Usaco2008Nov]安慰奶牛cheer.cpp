/*
DATE : 2013-1-2 
RATING : 1
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

const int MAXE = 100000 + 5;
const int MAXN = 10000 + 5;

struct Edge
{
	int from,to,w;
} g[MAXE];

bool cmp(Edge a,Edge b)
{
	return a.w<b.w;
}

int n,p,father[MAXN];
int c[MAXN],ans,minc=0x7FFFFFFF;

int getfather(int x)
{
	if(father[x]==x) return x;
	else return father[x]=getfather(father[x]);
}

int main()
{
	scanf("%d%d",&n,&p);
	for(int i=1;i<=n;i++) scanf("%d",&c[i]),minc=min(minc,c[i]),father[i]=i;
	for(int i=1;i<=p;i++) scanf("%d%d%d",&g[i].from,&g[i].to,&g[i].w),g[i].w=2*g[i].w+c[g[i].from]+c[g[i].to];
	sort(g+1,g+1+p,cmp);
	for(int i=1;i<=p;i++) 
	{
		if(getfather(g[i].to)!=getfather(g[i].from))
		{
			ans+=g[i].w;
			father[getfather(g[i].to)]=getfather(g[i].from);
		}
	}
	printf("%d\n",ans+minc);
	
	return 0;
}
