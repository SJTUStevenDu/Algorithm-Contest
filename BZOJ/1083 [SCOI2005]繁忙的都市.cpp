/*
DATE : 2013-3-6 
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
#include <map>
#include <queue>
#include <vector>

//Orz WJMZBMR && sevenkplus

using namespace std;

const int MAXN = 300 + 10;
const int MAXE = 100000 + 10;

struct Edge
{
	int next,to,w;
} g[MAXE];
int start[MAXN],gn;

void AddEdge(int a,int b,int c)
{
	gn++;g[gn].to=b;g[gn].next=start[a];start[a]=gn;g[gn].w=c;
}

int n,m,cnt,l,r,mid;
bool vis[MAXN];

void dfs(int p)
{
	vis[p]=1;cnt++;
	for(int i=start[p];i;i=g[i].next)
		if(!vis[g[i].to] && g[i].w<=mid) dfs(g[i].to);
}

bool check(int p)
{
	memset(vis,0,sizeof(vis));
	cnt=0;
	dfs(1);
	return cnt>=n;
}

int main()
{
	scanf("%d%d",&n,&m);
	for(int a,b,c,i=1;i<=m;i++)
	{
		scanf("%d%d%d",&a,&b,&c);
		AddEdge(a,b,c);
		AddEdge(b,a,c);
	}
	l=1,r=10000;
	while(l<=r)
	{
		mid=(l+r)>>1;
		if(check(mid)) r=mid-1;else l=mid+1;
	}
	printf("%d %d\n",n-1,l);
	
	return 0;
}
