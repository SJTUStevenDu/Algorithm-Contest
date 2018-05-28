/*
DATE : 2012-12-14 
RATING : 1
TAG : MST
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

const int MAXN = 2000 + 5;
const int MAXM = 10000 + 5;

struct Edge
{
	int a,b,w;
} g[MAXM];

int n,m,father[MAXN],cnt,ans;

int getfather(int x)
{
	if(father[x]==x) return x;
	else return father[x]=getfather(father[x]);
}

bool cmp(Edge a,Edge b)
{
	return a.w<b.w;
}

int main()
{
	scanf("%d%d",&n,&m);
	for(int i=1;i<=m;i++)
	{
		int a,b,c;
		scanf("%d%d%d",&a,&b,&c);
		g[i].a=a;g[i].b=b;g[i].w=c;
	}
	sort(g+1,g+1+m,cmp);
	for(int i=1;i<=n;i++) father[i]=i;
	for(int i=1;i<=m;i++) 
	{
		if(cnt>=n-1) break;
		if(getfather(g[i].a)==getfather(g[i].b)) continue;
		else {father[getfather(g[i].b)]=getfather(g[i].a);ans=g[i].w;cnt++;}
	}
	printf("%d\n",ans);
	
	return 0;
}
