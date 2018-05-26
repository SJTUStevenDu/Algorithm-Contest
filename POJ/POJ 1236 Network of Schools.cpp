/*
DATE : 2013-7-24 
RATING : 2
TAG : SCC
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
#include <vector>

//Orz WJMZBMR && sevenkplus

using namespace std;

const int MAXN = 100 + 10;
const int MAXM = MAXN * MAXN;

struct Edge
{
	int next,to;
} g[MAXM];
int gn,start[MAXN];

inline void AddEdge(int a,int b)
{
	gn++;g[gn].to=b;g[gn].next=start[a];start[a]=gn;
}

int n,dfn[MAXN],low[MAXN],stk[MAXN],Top,Index,Bcnt,Belong[MAXN],ind[MAXN],outd[MAXN],num1,num2;
bool u[MAXN][MAXN],vis[MAXN];

void Tarjan(int p)
{
	dfn[p]=low[p]=++Index;
	vis[p]=1;
	stk[++Top]=p;
	for(int i=start[p];i;i=g[i].next)
	{
		int v=g[i].to;
		if(!dfn[v]) 
		{
			Tarjan(v);
			low[p]=min(low[p],low[v]);
		}
		else if(vis[v]) low[p]=min(low[p],dfn[v]);
	}
	if(low[p]==dfn[p])
	{
		++Bcnt;
		int i=-1;
		while(i!=p)
		{
			i=stk[Top--];
			Belong[i]=Bcnt;
			vis[i]=0;
		}
	}
}

int main()
{
	scanf("%d",&n);
	for(int a,i=1;i<=n;i++) 
		for(;;)
		{
			scanf("%d",&a);
			if(a==0) break;
			AddEdge(i,a);
		}
	for(int i=1;i<=n;i++) if(!dfn[i]) Tarjan(i);
	for(int p=1;p<=n;p++) 
	{
		for(int i=start[p];i;i=g[i].next)
		{
			int v=g[i].to;
			if(Belong[p]==Belong[v]) continue;
			int pp=Belong[p],vv=Belong[v];
			if(u[pp][vv]) continue;
			u[pp][vv]=1;
			ind[vv]++;outd[pp]++;
		}
	}
	n=Bcnt;
	for(int i=1;i<=n;i++) if(!ind[i]) num1++;
	for(int i=1;i<=n;i++) if(!outd[i]) num2++;
	printf("%d\n",num1);
	if(n==1) printf("%d\n",0);
	else printf("%d\n",max(num1,num2));
	
	return 0;
}
