/*
DATE : 2013-1-15 
RATING : 1
TAG : Binary Search + SPFA
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

const int MAXN = 1000 + 5;

int n,map[MAXN][MAXN],m;
int maptmp[MAXN][MAXN];
int k,l,r;
int q[MAXN],head,tail,dist[MAXN];
bool vis[MAXN];

bool check(int x)
{
	memset(maptmp,20,sizeof(maptmp));
	for(int i=1;i<=n;i++) 
		for(int j=1;j<=n;j++) 
			if(map[i][j]>=10000000) continue;
			else if(map[i][j]<=x) maptmp[i][j]=0;
				else maptmp[i][j]=1;
	memset(vis,0,sizeof(vis));
	memset(dist,20,sizeof(dist));
	head=0;tail=1;q[head]=1;vis[1]=1;dist[1]=0;
	while(head!=tail)
	{
		int p=q[head];
		head=(head+1)%MAXN;
		vis[p]=false;
		for(int i=1;i<=n;i++) 
			if(maptmp[p][i]+dist[p]<dist[i])
			{
				dist[i]=dist[p]+maptmp[p][i];
				if(!vis[i]) vis[i]=1,q[tail]=i,tail=(tail+1)%MAXN;
			}
	}
	if(dist[n]>k) return false;
	else return true;
}

int main()
{
	scanf("%d%d%d",&n,&m,&k);
	memset(map,20,sizeof(map));
	for(int i=1;i<=n;i++) map[i][i]=0;
	while(m--)
	{
		int a,b,c;
		scanf("%d%d%d",&a,&b,&c);
		map[a][b]=map[b][a]=min(map[a][b],c);
	}
	l=0;r=1000000;
	while(l<=r)
	{
		int mid=(l+r)/2;
		if(check(mid)) r=mid-1;else l=mid+1;
	}
	if(!check(1000000)) printf("-1\n");
	else printf("%d\n",l);
	
	return 0;
}
