/*
DATE : 2012-12-27 
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

using namespace std;

int T,N,C,maxp,ans=-1;
int dp[10005][105]; //dp[i][j]表示前i时间能力值为j时最大次数 
int dpmax[10005]; //dpmax[i]表示前i时间最大次数 
int sk[105]; //sk[i]表示能力值为i所用的最小时间
int classes[10005][3]; 

int main()
{
	scanf("%d%d%d",&T,&C,&N);
	for(int i=1;i<=C;i++)
	{
		scanf("%d%d%d",&classes[i][0],&classes[i][1],&classes[i][2]);
		classes[i][1]+=classes[i][0];
		maxp=max(maxp,classes[i][2]);
	}
	memset(sk,20,sizeof(sk));
	for(int i=1;i<=N;i++)
	{
		int a,b;
		scanf("%d%d",&a,&b);
		sk[a]=min(sk[a],b);
	}
	for(int i=2;i<=100;i++) sk[i]=min(sk[i],sk[i-1]);
	memset(dpmax,-20,sizeof(dpmax));
	memset(dp,-20,sizeof(dp));
	dp[0][1]=dpmax[0]=0;
	for(int i=1;i<=T;i++) 
		for(int j=1;j<=maxp;j++)
		{
			dp[i][j]=dp[i-1][j];
			for(int k=1;k<=C;k++)
				if(classes[k][1]==i && classes[k][2]==j) dp[i][j]=max(dp[i][j],dpmax[classes[k][0]]);
			if(i>=sk[j])dp[i][j]=max(dp[i][j],dp[i-sk[j]][j]+1);
			dpmax[i]=max(dp[i][j],dpmax[i]);
		}
	for(int i=1;i<=maxp;i++) ans=max(ans,dp[T][i]);
	printf("%d\n",ans);
	
	return 0;
}
