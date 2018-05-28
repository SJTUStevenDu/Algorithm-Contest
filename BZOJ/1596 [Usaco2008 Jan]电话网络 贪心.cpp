/*
DATE : 2013-2-21 
RATING : 2
TAG : Greedy
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

struct Edge
{
	int to,next;
} g[MAXN*2];
int gn,start[MAXN];

void AddEdge(int a,int b)
{
	gn++;g[gn].to=b;g[gn].next=start[a];start[a]=gn;
}

int n,q[MAXN],head,tail,fa[MAXN],ans;
bool vis[MAXN],s[MAXN];

int main()
{
	scanf("%d",&n);
	for(int i=1;i<n;i++)
	{
		int a,b;
		scanf("%d%d",&a,&b);
		AddEdge(a,b);AddEdge(b,a);
	}
	q[0]=1;tail=1;vis[1]=1;fa[1]=1;
	while(head<tail)
	{
		int p=q[head++];
		for(int i=start[p];i;i=g[i].next)
		{
			int v=g[i].to;
			if(!vis[v])
			{
				q[tail++]=v;
				vis[v]=1;
				fa[v]=p;
			}
		}
	}
	tail--;
	memset(vis,0,sizeof(vis));
	memset(s,0,sizeof(s));
	for(int i=tail;i>=0;i--)
	{
		int p=q[i];
		if(!vis[p] && !s[fa[p]]) 
		{
			ans++;
			vis[fa[p]]=vis[p]=vis[fa[fa[p]]]=1;
			s[fa[p]]=1;
		}
	}
	printf("%d\n",ans);
	
	return 0;
}
