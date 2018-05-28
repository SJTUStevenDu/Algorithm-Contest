/*
DATE : 2013-3-25 
RATING : 1
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

const int MOD = 10000;
const int MAXN = 1000 + 10;

int dp[MAXN][2],sum[MAXN][2],pre,now,n,k;

int main()
{
	scanf("%d%d",&n,&k);
	for(int i=1;i<=n;i++,pre=now)
	{
		now=pre^1;
		dp[1][now]=sum[1][now]=1;
		for(int j=2;j<=k+1;j++)
		{
			dp[j][now]=(sum[j][pre]-sum[j-min(i,j)][pre]+MOD)%MOD;
			sum[j][now]=(sum[j-1][now]+dp[j][now])%MOD;
		}
	}
	printf("%d\n",dp[k+1][now]);
	
	return 0;
}
