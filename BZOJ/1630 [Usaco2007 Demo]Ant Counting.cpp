/*
DATE : 2012-12-6 
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

const int MAXN = 100005;
const int MOD = 1000000;

int a[MAXN],n,m,st,en,sum[MAXN],ans;
int dp[2][MAXN];

int main()
{
	scanf("%d%d%d%d",&n,&m,&st,&en);
	for(int i=1;i<=m;i++) 
	{
		int x;
		scanf("%d",&x);
		a[x]++;
	}
	dp[0][0]=1;
	for(int i=1;i<=n;i++) 
	{
		int x=i&1;
		int y=!x;
		memset(sum,0,sizeof(sum));
		sum[0]=dp[y][0];
		for(int j=1;j<=en;j++) sum[j]=(sum[j-1]+dp[y][j])%MOD;
		for(int j=0;j<=en;j++)
		{
			dp[x][j]=sum[j];
			if(a[i]<j) dp[x][j]=(dp[x][j]-sum[j-a[i]-1]+MOD)%MOD;
		}
	}
	for(int i=st;i<=en;i++) ans=(ans+dp[n&1][i])%MOD;
	printf("%d\n",ans);
	
	return 0;
}
