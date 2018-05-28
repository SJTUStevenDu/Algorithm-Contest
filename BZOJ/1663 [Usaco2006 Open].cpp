/*
DATE : 2012-12-12 
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

const int MAXN = 400 + 5;

int n,ans;
int t[MAXN],map[MAXN][MAXN],dp[MAXN];

int main()
{
	scanf("%d",&n);
	for(int i=1;i<=n;i++) scanf("%d",&t[i]);
	for(int i=1;i<=n;i++) 
		for(int j=1;j<=n;j++) scanf("%d",&map[i][j]);
	for(int i=1;i<=n;i++) if(t[i]>=map[1][i]) dp[i]=1;
	bool flag=1;
	while(flag)
	{
		flag=false;
		for(int i=1;i<=n;i++)
			for(int j=1;j<=n;j++) 
				if(i!=j && dp[j]<=dp[i] && map[i][j]<=t[j]-t[i]) flag=true,dp[j]=dp[i]+1;
	}
	for(int i=1;i<=n;i++) ans=max(ans,dp[i]);
	printf("%d\n",ans);
	
	return 0;
}
