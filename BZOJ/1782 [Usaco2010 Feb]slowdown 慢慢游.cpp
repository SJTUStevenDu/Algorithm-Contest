/*
DATE : 2013-2-14 
RATING : 2
TAG : DFS + BIT
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

const int MAXN = 100000 + 5;

struct Edge
{
	int to,next;
} g[MAXN*2];
int gn,start[MAXN];

int n,own[MAXN];
int sum[MAXN],ans[MAXN];

void AddEdge(int a,int b)
{
	gn++;g[gn].to=b;g[gn].next=start[a];start[a]=gn;
	gn++;g[gn].to=a;g[gn].next=start[b];start[b]=gn;
}

inline int lowbit(int x) {return x&(-x);}

void Update(int x,int num)
{
	for(int i=x;i<=n;i+=lowbit(i)) sum[i]+=num;
}

int Query(int x)
{
	int re=0;
	for(int i=x;i>0;i-=lowbit(i)) re+=sum[i];
	return re;
}

void dfs(int p,int fa)
{
	ans[own[p]]=Query(own[p]);
	Update(own[p],1);
	for(int i=start[p];i;i=g[i].next)
	{
		if(g[i].to!=fa) dfs(g[i].to,p);
	}
	Update(own[p],-1);
}

int main()
{
	scanf("%d",&n);
	for(int a,b,i=1;i<n;i++) 
	{
		scanf("%d%d",&a,&b);
		AddEdge(a,b);
	}
	for(int a,i=1;i<=n;i++) 
	{
		scanf("%d",&a);
		own[a]=i;
	}
	dfs(1,0);
	for(int i=1;i<=n;i++) printf("%d\n",ans[i]);
	
	return 0;
}
