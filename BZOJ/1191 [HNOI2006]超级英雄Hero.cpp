/*
DATE : 2013-2-25 
RATING : 2
TAG : Binary Map
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

//Orz WJMZBMR && sevenkplus

using namespace std;

const int MAXN = 5000 + 10;
const int MAXE = 100000 + 10;

struct Node 
{
	int to,next;
} g[MAXE*2];
int start[MAXN],gn;

void AddEdge(int a,int b)
{
	gn++;g[gn].to=b;g[gn].next=start[a];start[a]=gn;
}

int n,m,ans;
int Link[MAXN];
bool vis[MAXN];

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
	scanf("%d%d",&n,&m);
	for(int i=1;i<=m;i++)
	{
		int a,b;
		scanf("%d%d",&a,&b);
		AddEdge(i,a+m+1);
		AddEdge(i,b+m+1);
	}
	for(int i=1;i<=m;i++)
	{
		memset(vis,0,sizeof(vis));
		if(Find(i)) ans++;
		else break;
	}
	printf("%d\n",ans);
	
	return 0;
}
