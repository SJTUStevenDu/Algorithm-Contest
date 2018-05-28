/*
DATE : 2012-12-13 
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

//Orz WJMZBMR && sevenkplus

using namespace std;

const int MAXN = 105;

int r,c;
int dp[MAXN][MAXN],a[MAXN][MAXN];

int main()
{
	scanf("%d%d",&r,&c);
	for(int i=1;i<=r;i++) 
		for(int j=1;j<=c;j++) scanf("%d",&a[i][j]);
	dp[1][1]=a[1][1];
	for(int i=2;i<=r;i++) dp[i][1]=-10000000;
	for(int j=2;j<=c;j++) 
		for(int i=1;i<=r;i++) 
		{
			dp[i][j]=dp[i][j-1];	
			if(i>1) dp[i][j]=max(dp[i][j],dp[i-1][j-1]);
			if(i<r) dp[i][j]=max(dp[i][j],dp[i+1][j-1]);
			dp[i][j]+=a[i][j];
		}
	printf("%d\n",dp[r][c]);
	
	return 0;
}
