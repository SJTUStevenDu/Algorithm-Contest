/*
DATE : 2013-1-3 
RATING : 3
TAG : Tree DP
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

const int MAXN = 10000 + 5;
const int INF = 1000000000;

struct Edge
{
	int to,next;
} g[MAXN*2];
int start[MAXN],gn;

void AddEdge(int a,int b)
{
	gn++;g[gn].to=b;g[gn].next=start[a];start[a]=gn;
	gn++;g[gn].to=a;g[gn].next=start[b];start[b]=gn;
}

int n,dp[MAXN][3],q[MAXN],head,tail,outdegree[MAXN];
bool vis[MAXN];

int main()
{
	scanf("%d",&n);
	for(int i=1;i<n;i++) 
	{
		int a,b;
		scanf("%d%d",&a,&b);
		AddEdge(a,b);
	}
	head=0;q[1]=1;vis[1]=1;tail=1;
	while(head!=tail)
	{
		int p=q[++head];
		for(int i=start[p];i;i=g[i].next)
		{
			int u=g[i].to;
			if(!vis[u]) vis[u]=1,q[++tail]=u,outdegree[p]++;
		}
	}
	memset(vis,0,sizeof(vis));
	for(int i=1;i<=n;i++) if(outdegree[i]==0) dp[i][0]=1,dp[i][2]=INF;
	for(int i=n;i;i--)
	{
		int p=q[i];
		vis[p]=1;
		if(!outdegree[p]) continue;
		bool f=0;
		int mindelta=INF;
		for(int j=start[p];j;j=g[j].next)
		{
			int u=g[j].to;
			if(vis[u])
			{
				dp[p][0]+=min(dp[u][0],min(dp[u][1],dp[u][2]));
				dp[p][1]+=min(dp[u][0],dp[u][2]);
				if(dp[u][0]<dp[u][2]) dp[p][2]+=dp[u][0],f=1;
				else dp[p][2]+=dp[u][2],mindelta=min(mindelta,dp[u][0]-dp[u][2]);
			}
		}
		dp[p][0]++;
		if(!f) dp[p][2]+=mindelta;
	}
	printf("%d\n",min(dp[1][0],dp[1][2]));
	
	return 0;
}
