/*
DATE : 2013-3-13 
RATING : 2
TAG : Binary
*/

#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <cstdlib>

//Orz WJMZBMR && sevenkplus

using namespace std;

const int MAXN = 200 + 5;

int n,T,g[MAXN][MAXN];
int Link[MAXN];
bool vis[MAXN];

bool Find(int p)
{
	for(int i=1;i<=n;i++)
	{
		if(!g[p][i] || vis[i]) continue;
		vis[i]=1;
		if(Link[i]==0 || Find(Link[i]))
		{
			Link[i]=p;
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
		for(int i=1;i<=n;i++)
			for(int j=1;j<=n;j++) 
				scanf("%d",&g[i][j]);
		int cnt=0;
		bool flag=true;
		for(int i=1;i<=n;i++)
		{
			cnt=0;
			for(int j=1;j<=n;j++) cnt+=g[i][j];
			if(!cnt) flag=false;
		}
		for(int i=1;i<=n;i++)
		{
			cnt=0;
			for(int j=1;j<=n;j++) cnt+=g[j][i];
			if(!cnt) flag=false;
		}
		if(!flag)
		{
			printf("No\n");
			continue;
		}
		memset(Link,0,sizeof(Link));
		for(int i=1;i<=n;i++)
		{
			memset(vis,0,sizeof(vis));
			if(!Find(i))
			{
				flag=false;
				break;
			}
		}
		if(flag) printf("Yes\n");
		else printf("No\n");
	}
	
	return 0;
}
