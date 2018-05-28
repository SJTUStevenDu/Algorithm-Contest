/*
DATE : 2012-12-13 
RATING : 3
TAG : Tarjan
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

const int MAXV = 10000 + 5;
const int MAXM = 50000 + 5;

struct Edge
{
	int next,to;
} g[MAXM];
int start[MAXV],gn;

inline void AddEdge(int a,int b)
{
	gn++;g[gn].to=b;g[gn].next=start[a];start[a]=gn;
}

int belong[MAXV],stack[MAXV],top;
int dfn[MAXV],low[MAXV],bcnt,Dindex,cnt[MAXV],ans,n,m;
bool vis[MAXV];

void tarjan(int p)
{
	vis[p]=1;
	stack[++top]=p;
	dfn[p]=low[p]=++Dindex;
	for(int i=start[p];i;i=g[i].next)
	{
		int u=g[i].to;
		if(!vis[u])
		{
			tarjan(u);
			low[p]=min(low[p],low[u]);
		}
		else low[p]=min(low[p],dfn[u]);
	}
	if(dfn[p]==low[p])
	{
		int i=-1;
		bcnt++;
		while(i!=p)
		{
			cnt[bcnt]++;
			i=stack[top--];
			vis[i]=0;
			belong[i]=bcnt;
		}
	}
}

int main()
{
	//freopen("1.txt","r",stdin);
	scanf("%d%d",&n,&m);
	for(int i=1;i<=m;i++)
	{
		int a,b;
		scanf("%d%d",&a,&b);
		AddEdge(a,b);
	}
	for(int i=1;i<=n;i++) if(!dfn[i]) tarjan(i);
	for(int i=1;i<=bcnt;i++) if(cnt[i]>1) ans++;
	printf("%d\n",ans);
	
	return 0;
}
