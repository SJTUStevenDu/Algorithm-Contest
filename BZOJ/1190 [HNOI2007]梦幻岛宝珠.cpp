/*
DATE : 2013-5-3 
RATING : 3
TAG : ∑÷≤„DP 
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

const int MAXN = 100 + 10;
const int MAXM = 32;

int dp[MAXM][1005],n,W,len;
int w[MAXM][MAXN],p[MAXM][MAXN],cnt[MAXM],sum[MAXM],d[MAXM],ex[MAXM];

int main()
{
	while(scanf("%d%d",&n,&W))
	{
		memset(cnt,0,sizeof(cnt));
		memset(ex,0,sizeof(ex));
		memset(sum,0,sizeof(sum));
		memset(dp,0,sizeof(dp));
		memset(d,0,sizeof(d));
		if(n==-1) break;
		for(int i=1;i<=n;i++)
		{
			int x,y,z;
			scanf("%d%d",&x,&y);
			for(z=0;x%2==0;z++,x/=2);
			cnt[z]++;;
			w[z][cnt[z]]=x;
			p[z][cnt[z]]=y;
			sum[z]+=x;
		}
		for(len=0;W;W/=2,len++) ex[len]=W&1;
		d[0]=sum[0];
		for(int j=1;j<=cnt[0];j++)
			for(int k=d[0];k>=w[0][j];k--) dp[0][k]=max(dp[0][k],dp[0][k-w[0][j]]+p[0][j]);
		for(int i=1;i<len;i++)
		{
			d[i]=sum[i]+(d[i-1]+1>>1);
			for(int j=1;j<=cnt[i];j++)
			{
				for(int k=d[i];k>=w[i][j];k--)
					dp[i][k]=max(dp[i][k],dp[i][k-w[i][j]]+p[i][j]);
			}
			for(int j=d[i];j>=0;j--)
				for(int k=0;k<=d[i-1]+1>>1;k++)
				{
					if(j<k) break;
					dp[i][j]=max(dp[i][j],dp[i-1][min(k*2+ex[i-1],d[i-1])]+dp[i][j-k]);
					if(k*2+ex[i-1]>=d[i-1]) break;
				}
		}
		printf("%d\n",dp[len-1][1]);
	}
	
	return 0;
}
