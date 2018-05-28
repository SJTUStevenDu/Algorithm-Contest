/*
DATE : 2013-03-18 
RATING : 3
TAG : Math DP
*/

#include <iostream>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <cmath>
#include <fstream>
#include <string>
#include <algorithm>
#include <map>
#include <vector>

//Orz WJMZBMR && sevenkplus

using namespace std;

const int MAXN = 1000 + 10;
const int MAXE = 10000 + 10;

struct Edge 
{
	int next,to;
} g[MAXE];
int gn,start[MAXN];

void AddEdge(int a,int b)
{
	gn++;g[gn].next=start[a];start[a]=gn;g[gn].to=b;
}

int n,m;
int dist[MAXN][MAXN],outd[MAXN],q[MAXN],head,tail,S,T;
double dp[MAXN][MAXN];
bool vis[MAXN];

void BFS(int s)
{
	q[head=0]=s;tail=1;
	memset(vis,0,sizeof(vis));
	vis[s]=1;
	while(head!=tail)
	{
		int p=q[head++];
		for(int i=start[p];i;i=g[i].next)
		{
			int v=g[i].to;
			if(vis[v]) continue;
			dist[s][v]=dist[s][p]+1;
			q[tail++]=v;
			vis[v]=1;
		}
	}
	return;
}

int Walk(int s,int t)
{
	int re=0;
	for(int i=start[s];i;i=g[i].next)
	{
		int v=g[i].to;
		if(re==0 || (dist[re][t]>dist[v][t]) || (dist[re][t]==dist[v][t] && re>v)) re=v;
	}
	return re;
}

double DP(int s,int t)
{
	if(s==t) return 0.0;
	if(dp[s][t]>1e-6) return dp[s][t];
	int tmp=Walk(s,t);
	if(tmp!=t) tmp=Walk(tmp,t);
	if(tmp==t) return 1.0;
	double re=0;
	for(int i=start[t];i;i=g[i].next) re+=(DP(tmp,g[i].to)+1.0)/outd[t];
	return dp[s][t]=re;
}

int main()
{
	scanf("%d%d",&n,&m);
	scanf("%d%d",&S,&T);
	for(int i=1;i<=n;++i) AddEdge(i,i),++outd[i];
	for(int a,b,i=1;i<=m;++i)
	{
		scanf("%d%d",&a,&b);
		AddEdge(a,b);
		AddEdge(b,a);
		++outd[a];++outd[b];
	}
	for(int i=1;i<=n;i++) BFS(i);
	printf("%.3lf\n",DP(S,T));
	
	return 0;
}

