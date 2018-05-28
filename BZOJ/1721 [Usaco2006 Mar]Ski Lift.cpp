/*
DATE : 2013-1-4 
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

//Orz WJMZBMR && sevenkplus

using namespace std;

const int MAXN = 5000 + 5;
const double eps=0.0000001;

int n,len;
int dp[MAXN],h[MAXN];
bool able[MAXN][MAXN];

int main()
{
	scanf("%d%d",&n,&len);
	for(int i=1;i<=n;i++) scanf("%d",&h[i]);
	for(int i=1;i<=n;i++) 
	{
		double maxslope=-1e10;
		for(int j=i+1;j<=n;j++)
		{
			double current_slope=(h[j]-h[i])*1.0/(j-i);
			if(maxslope<=current_slope+eps) able[i][j]=1;else able[i][j]=0;
			maxslope=max(maxslope,current_slope);
		}
	}
	memset(dp,20,sizeof(dp));
	dp[1]=1;
	for(int i=2;i<=n;i++) 
		for(int j=max(1,i-len);j<i;j++)
			if(dp[i]>dp[j]+1 && able[j][i]) dp[i]=dp[j]+1;
	printf("%d\n",dp[n]);
	return 0;
}
