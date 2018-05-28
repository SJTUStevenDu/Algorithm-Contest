/*
DATE : 2012-12-31 
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

int T,W;
int dp[1005][34];
int a[1005];

int main()
{
	scanf("%d%d",&T,&W);
	for(int i=1;i<=T;i++) 
	{
		scanf("%d",&a[i]);
		a[i]--;
	}
	for(int i=1;i<=T;i++)
	{
		for(int j=0;j<=W;j++) 
		{
			dp[i][j]=max(dp[i][j],dp[i-1][j]+(j%2==a[i] ? 1 : 0));
			if(j) dp[i][j]=max(dp[i][j],dp[i-1][j-1]+(j%2!=a[i] ? 1 : 0));
		}
	}
	printf("%d\n",dp[T][W]);
	
	return 0;
}
