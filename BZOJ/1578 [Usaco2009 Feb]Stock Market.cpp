/*
DATE : 2013-1-4 
RATING : 2
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

//Orz WJMZBMR && sevenkplus

using namespace std;

int D,S,M;
int dp[500005],cost[15][55];

int main()
{
	scanf("%d%d%d",&S,&D,&M);
	for(int i=1;i<=S;i++)
	{
		for(int j=1;j<=D;j++) scanf("%d",&cost[j][i]);
	}
	for(int i=1;i<=D;i++)
	{
		for(int j=0;j<=M;j++) dp[j]=j;
		for(int j=1;j<=S;j++)
			for(int k=cost[i][j];k<=M;k++)
				dp[k]=max(dp[k],dp[k-cost[i][j]]+cost[i+1][j]);
		M=dp[M];
	}
	printf("%d\n",M);
	
	return 0;
}
