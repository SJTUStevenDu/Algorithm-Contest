/*
DATE : 2013-5-15 
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

//Orz WJMZBMR && sevenkplus

using namespace std;

const int MAXN = 50 + 10;
const int MAXM = 1000 + 10;

bool dp[MAXN][MAXM];
int n,maxlevel,c[MAXN],beginlevel,ans=-1;

int main()
{
	scanf("%d%d%d",&n,&beginlevel,&maxlevel);
	for(int i=1;i<=n;i++) scanf("%d",&c[i]);
	dp[0][beginlevel]=1;
	for(int i=1;i<=n;i++) 
	{
		for(int j=0;j<=maxlevel;j++) 
		{
			if(j+c[i]<=maxlevel) dp[i][j]|=dp[i-1][j+c[i]];
			if(j-c[i]>=0) dp[i][j]|=dp[i-1][j-c[i]];
		}
	}
	for(int i=maxlevel;i>=0;i--)
		if(dp[n][i])
		{
			ans=i;
			break;
		}
	printf("%d\n",ans);
	
	return 0;
}
