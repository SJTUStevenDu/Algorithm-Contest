/*
DATE : 2013-4-5 
RATING : 2
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
#include <map>
#include <vector>

//Orz WJMZBMR && sevenkplus

using namespace std;

const int MAXN = 10000 + 10;

int x[MAXN],y[MAXN],t[MAXN],dp[MAXN],n,ans,m;

inline int dist(int i,int j)
{
	return abs(x[i]-x[j])+abs(y[i]-y[j]);
}

int main()
{
	scanf("%d%d",&m,&n);
	for(int i=1;i<=n;i++) scanf("%d%d%d",&t[i],&x[i],&y[i]);
	dp[1]=1;
	for(int i=2;i<=n;i++) 
	{
		for(int j=1;j<i;j++) 
		{
			if(dist(i,j)<=t[i]-t[j]) dp[i]=max(dp[i],dp[j]);
		}
		++dp[i];
	}
	for(int i=1;i<=n;i++) ans=max(ans,dp[i]);
	printf("%d\n",ans);
	
	return 0;
}
