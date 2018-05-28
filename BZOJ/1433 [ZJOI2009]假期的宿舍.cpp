/*
DATE : 2013-3-13 
RATING : 2
TAG : MaxFlow
*/

#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <cstdlib>
#include <iomanip>
#include <cmath>
#include <vector>
#include <fstream>
#include <string>
#include <map>
#include <queue>

//Orz WJMZBMR && sevenkplus

using namespace std;

const int MAXN = 60;
const int MAXM = 50000;

struct Edge
{
	int next,to;
} g[MAXM];
int gn,start[MAXN*2];

void AddEdge(int a,int b)
{
	gn++;g[gn].to=b;g[gn].next=start[a];start[a]=gn;
}

int n,T,cnt,ans;
int Link[MAXN*2],X[MAXN],Y[MAXN];
bool vis[MAXN*2],flag;
int isStudent[MAXN],gohome[MAXN];

bool Find(int p)
{
	for(int i=start[p];i;i=g[i].next)
	{
		int v=g[i].to;
		if(vis[v]) continue;
		vis[v]=1;
		if(!Link[v] || Find(Link[v]))
		{
			Link[v]=p;
			return true;
		}
	}
	return false;
}

int main()
{
	scanf("%d",&T);
	while(T--)
	{
		scanf("%d",&n);
		flag=0;
		memset(Link,0,sizeof(Link));
		for(int i=1;i<=n;i++) scanf("%d",&isStudent[i]);
		for(int i=1;i<=n;i++) scanf("%d",&gohome[i]);
		gn=0;
		memset(start,0,sizeof(start));
		for(int i=1;i<=n;i++)
		{
			for(int j=1;j<=n;j++)
			{
				int a;
				scanf("%d",&a);
				if(!isStudent[j]) continue;
				if(a==0)
				{
					if(i==j) AddEdge(i,j+n);
					continue;
				}
				AddEdge(i,j+n);
			}
		}
		for(int i=1;i<=n;i++)
		{
			if(isStudent[i] && gohome[i]) continue;
			memset(vis,0,sizeof(vis));
			if(!Find(i)) 
			{
				flag=1;
				printf("T_T\n");
				break;
			}
		}
		if(!flag) printf("^_^\n");
	}
	
	return 0;
}
