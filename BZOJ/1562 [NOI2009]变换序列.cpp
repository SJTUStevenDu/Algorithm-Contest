/*
DATE : 2013-3-18 
RATING : 2
TAG : Binary Map
*/

#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <cstdlib>
#include <cmath>
#include <vector>
#include <fstream>
#include <string>
#include <map>

//Orz WJMZBMR && sevenkplus

using namespace std;

const int MAXN = 20000 + 10;
const int MAXM = 50000 + 10;

struct Edge
{
	int next,to;
} g[MAXM];
int gn,start[MAXN];

void AddEdge(int a,int b)
{
	gn++;g[gn].to=b;g[gn].next=start[a];start[a]=gn;
}

int n,b;
int Link[MAXN],a[MAXN],m[MAXN];
bool vis[MAXN];

bool Find(int p)
{
	for(int i=start[p];i;i=g[i].next) if(!vis[g[i].to])
	{
		vis[g[i].to]=1;
		if(!Link[g[i].to] || Find(Link[g[i].to]))
		{
			Link[g[i].to]=p;
			m[p]=g[i].to;
			return true;
		}
	}
	return false;
}

int main()
{
	scanf("%d",&n);
	for(int i=0;i<n;i++)
	{
		scanf("%d",&b);
		int x1=(i-b+n)%n;
		int x2=(i+b)%n;
		if(x1<x2) swap(x1,x2);
		AddEdge(i,x1);
		AddEdge(i,x2);
	}
	for(int i=n-1;i>=0;i--)
	{
		memset(vis,0,sizeof(vis));
		if(!Find(i))
		{
			printf("No Answer\n");
			return 0;
		}
	}
	for(int i=0;i<n-1;i++) printf("%d ",m[i]);
	printf("%d\n",m[n-1]);
	return 0;
}
