/*
DATE : 2013-4-18
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

//Orz WJMZBMR && sevenkplus

using namespace std;

const int MAXN = 30000;

int n,S;
int dp[MAXN],dp2[MAXN];
int p[MAXN],c[MAXN];
int vmax,ans;

int main()
{
	// freopen("fewcoins.in","r",stdin);
	// freopen("fewcoins.out","w",stdout);
	scanf("%d%d",&n,&S);
	for(int i=1;i<=n;i++) scanf("%d",&p[i]);
	for(int i=1;i<=n;i++) scanf("%d",&c[i]);
	vmax=80;
	memset(dp2,63,sizeof(dp2));
	dp2[0]=0;
	for(int i=1;i<=n;i++)
		for(int j=p[i];j<=vmax;j++) dp2[j]=min(dp2[j],dp2[j-p[i]]+1);
	memset(dp,63,sizeof(dp));
	dp[0]=0;
	for(int i=1;i<=n;i++) 
		for(int j=S+vmax;j>=p[i];j--)
			for(int k=1;k<=min(j/p[i],c[i]);k++)
				dp[j]=min(dp[j],dp[j-k*p[i]]+k);
	ans=0x7FFFFFFF>>2;
	for(int i=0;i<=vmax;i++) ans=min(ans,dp[i+S]+dp2[i]);
	if(ans>10000000) printf("-1\n");
	else printf("%d\n",ans);
	
	return 0;
}
