/*
DATE : 2013-3-19 
RATING : 2
TAG : Binary Search
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
#include <vector>

//Orz WJMZBMR && sevenkplus

using namespace std;

const int MAXN = 150;

int map[MAXN][MAXN];
int n,m;
int X[MAXN],Y[MAXN];
int Lim;
bool vis[MAXN];
int Link[MAXN],cnt;

bool Find(int p)
{
	for(int i=1;i<=n;i++) if(map[p][i]<=Lim)
	{
		if(vis[i]) continue;
		vis[i]=1;
		if(Link[i]==0 || Find(Link[i]))
		{
			Link[i]=p;
			return true;
		}
	}
	return false;
}

void check()
{
	cnt=0;
	memset(Link,0,sizeof(Link));
	for(int i=1;i<=n;i++)
	{
		memset(vis,0,sizeof(vis));
		if(Find(i)) cnt++;
	}
}

int dist(int x1,int y1,int x2,int y2)
{
	return (x1-x2)*(x1-x2)+(y1-y2)*(y1-y2);
}

bool Find2(int p)
{
	for(int i=1;i<=n;i++) if(map[p][i]>=Lim)
	{
		if(vis[i]) continue;
		vis[i]=1;
		if(Link[i]==0 || Find2(Link[i]))
		{
			Link[i]=p;
			return true;
		}
	}
	return false;
}

void check2()
{
	cnt=0;
	memset(Link,0,sizeof(Link));
	for(int i=1;i<=n;i++)
	{
		memset(vis,0,sizeof(vis));
		if(Find2(i)) cnt++;
	}
}

int main()
{
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++) scanf("%d%d",&X[i],&Y[i]);
	for(int i=1;i<=n;i++) scanf("%d%d",&X[i+n],&Y[i+n]);
	for(int i=1;i<=n;i++) 
	{
		for(int j=n+1;j<=2*n;j++)
			map[i][j-n]=dist(X[i],Y[i],X[j],Y[j]);
	}
	int l=0,r=10000000;
	while(l<=r)
	{
		int mid=(l+r)/2;
		Lim=mid;
		check();
		if(cnt>=m) r=mid-1;else l=mid+1;
	}
	printf("%.2lf ",sqrt(l));
	l=0,r=10000000;
	while(l<=r)
	{
		int mid=(l+r)/2;
		Lim=mid;
		check2();
		if(n-cnt<=m) l=mid+1;else r=mid-1;
	}
	if(r<10000000) printf("%.2lf\n",sqrt(r));
	else printf("+INF\n");
	
	return 0;
}
