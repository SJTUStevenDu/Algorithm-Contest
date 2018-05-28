/*
DATE : 2013-2-22
RATING : DP
TAG : 2
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

//Orz WJMZBMR && sevenkplus

using namespace std;

const int MAXN = 1000000 + 5;

long long a[MAXN];
long long dp[2][MAXN];
long long maxx;
int pos,n;

int main()
{
	scanf("%d",&n);
	for(int i=1;i<=n;i++) scanf("%lld",&a[i]);
	pos=n;
	for(int i=n;i;i--)
	{
		dp[1][i]=maxx;
		dp[0][i]=dp[0][pos];
		if(dp[1][i]<=dp[0][pos]+a[i])
		{
			dp[1][i]=dp[0][pos]+a[i];
			maxx=dp[1][i];pos=i;
			dp[0][i]=dp[1][i+1];
		}
	}
	printf("%lld %lld\n",dp[1][1],dp[0][1]);
	
	return 0;
}
