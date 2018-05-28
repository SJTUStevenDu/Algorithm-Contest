/*
DATE : 2012-12-2 
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

int n,m,d[10005],dp[10005][505];

int main()
{
	//freopen("1.txt","r",stdin);
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++) scanf("%d",&d[i]);
	for(int i=1;i<=n;i++)
	{
		dp[i][0]=dp[i-1][0];
		for(int j=1;j<=m;j++) 
		{
			if(i>=j) dp[i][0]=max(dp[i][0],dp[i-j][j]);
			dp[i][j]=max(dp[i-1][j-1]+d[i],dp[i][j]);
		}
	}
	printf("%d\n",dp[n][0]);
	
	return 0;
}
