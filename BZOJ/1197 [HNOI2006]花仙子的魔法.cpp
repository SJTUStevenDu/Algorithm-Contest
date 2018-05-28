/*
DATE : 2013-2-26 
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

//Orz WJMZBMR && sevenkplus

using namespace std;

const int MAXN = 15 + 5;
const int MAXM = 100 + 5;

int n,m;
long long dp[MAXN][MAXM];

int main()
{
	scanf("%d%d",&m,&n);
	for(int i=1;i<=m;i++) dp[0][i]=2;
	for(int i=1;i<=n;i++) dp[i][1]=2;
	for(int i=1;i<=n;i++)
		for(int j=2;j<=m;j++) dp[i][j]=dp[i-1][j-1]+dp[i][j-1];
	printf("%lld\n",dp[n][m]);
	
	return 0;
}
