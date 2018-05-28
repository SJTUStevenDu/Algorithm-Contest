/*
DATE : 2013-3-25 
RATING : 2
TAG : DP
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
#include <map>
#include <queue>

//Orz WJMZBMR && sevenkplus

using namespace std;

const int MAXN = 200;
const int MAXK = 25;
const int MOD = 12345678;

int n,m,k;
int dp[2][MAXN][MAXK][MAXK],pre,now;
int ans;

int main()
{
	scanf("%d%d%d",&n,&m,&k);
	dp[0][0][0][0]=1;
	for(int i=0;i<n+m;i++,pre=now)
	{
		now=pre^1;
		memset(dp[now],0,sizeof(dp[now]));
		for(int j=0;j<=min(i,n);j++)
		{
			for(int k1=0;k1<=j;++k1)
			{
				if(k1>k) break;
				for(int k2=0;k2<=i-j;++k2)
				{
					if(k2>k) break;
					if(j<n && k1<k) dp[now][j+1][k1+1][max(k2-1,0)]=(dp[now][j+1][k1+1][max(k2-1,0)]+dp[pre][j][k1][k2])%MOD;
					if(i-j<m && k2<k) dp[now][j][max(k1-1,0)][k2+1]=(dp[now][j][max(k1-1,0)][k2+1]+dp[pre][j][k1][k2])%MOD;
				}
			}
		}
	}
	for(int i=0;i<=k;i++)
	{
		for(int j=0;j<=k;j++)
		{
			ans=(ans+dp[now][n][i][j])%MOD;
		}
	}
	printf("%d\n",ans);
	
	return 0;
}
