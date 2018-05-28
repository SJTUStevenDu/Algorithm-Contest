#include <iostream>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <cmath>
#include <algorithm>
#include <fstream>

using namespace std;

const int MAXN = 2000 + 10;
const int MAXM = 10000 + 10;

struct Edge
{
	int next,to;
} g[MAXM];
int gn,start[MAXN];

struct Point 
{
	int k,idx;
} P[MAXN];

bool cmp(Point A,Point B)
{
	return A.k<B.k;
}

inline void AddEdge(int a,int b)
{
	gn++;g[gn].next=start[a];start[a]=gn;g[gn].to=b;
}

int n,m,ind[MAXN],stk[MAXN],Top,limit[MAXN],num;
bool vis[MAXN];

void dfs(int p)
{
	vis[p]=1;
	for(int i=start[p];i;i=g[i].next)
	{
		int v=g[i].to;
		if(!vis[v]) dfs(v);
	}
}

void TopoSort()
{
	for(int i=1;i<=n;i++) if(!ind[i]) stk[++Top]=i;
	while(Top)
	{
		int p=stk[Top--];
		for(int i=start[p];i;i=g[i].next)
		{
			int v=g[i].to;
			if(P[v].k>=P[p].k) P[v].k=P[p].k-1;
			--ind[v];
			if(!ind[v]) stk[++Top]=v;
		}
	}
}

int main()
{
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++) scanf("%d",&P[i].k),P[i].idx=i;
	for(int a,b,i=1;i<=m;i++) 
	{
		scanf("%d%d",&a,&b);
		AddEdge(b,a);
		++ind[a];
	}
	TopoSort();
	sort(P+1,P+1+n,cmp);
	for(int i=1;i<=n;i++)
	{
		memset(vis,0,sizeof(vis));
		dfs(i);
		num=0;
		for(int j=1;j<=n;j++) if(vis[j]) num++;
		limit[i]=num;
		for(int j=1;j<=n;j++) 
		{
			if(!vis[P[j].idx]) 
			{
				++num;
				if(P[j].k<=limit[i]) ++limit[i];
				else if(P[j].k<num) limit[i]=P[j].k+1;
			}
		}
	}
	for(int i=1;i<n;i++) printf("%d ",P[i].idx);
	printf("%d\n",P[n].idx);
	for(int i=1;i<=n;i++) printf("%d ",limit[i]);
	printf("\n");
	
	return 0;
}
