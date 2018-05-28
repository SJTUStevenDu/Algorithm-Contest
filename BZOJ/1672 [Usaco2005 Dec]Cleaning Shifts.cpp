/*
DATE : 2012-12-25 
RATING : 1
TAG : DP
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

using namespace std;

const int MAXN = 10000 + 5;

struct Node
{
	int st,en,w;
} a[MAXN];

int n,S,T,dp[MAXN],ans=1000000000;

bool cmp(Node a,Node b)
{
	return a.en<b.en;
}

int main()
{
	scanf("%d%d%d",&n,&S,&T);
	for(int i=1;i<=n;i++) scanf("%d%d%d",&a[i].st,&a[i].en,&a[i].w);
	memset(dp,20,sizeof(dp));
	sort(a+1,a+1+n,cmp);
	if(T>a[n].en) 
	{
		printf("-1\n");
		return 0;
	}
	int kk=a[n].st;
	for(int i=n-1;i;i--) if(a[i].en>=kk-1) kk=min(kk,a[i].st);
	if(kk>S)
	{
		printf("-1\n");
		return 0;
	}
	for(int i=1;i<=n;i++) if(a[i].st==S) dp[i]=a[i].w;
	for(int i=1;i<=n;i++) 
	{
		if(a[i].st==S) continue;
		for(int j=i-1;j;j--)
		{
			if(a[j].en<a[i].st-1) break;
			dp[i]=min(dp[i],dp[j]);
		}
		dp[i]+=a[i].w;
	}
	for(int i=1;i<=n;i++) if(a[i].en>=T) ans=min(dp[i],ans);
	printf("%d\n",ans);
	
	return 0;
}
