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
#include <fstream>
#include <string>
#include <map>

//Orz WJMZBMR && sevenkplus

using namespace std;

const int MAXN = 50000 + 10;
const int MOD = 10007;

int sum[MAXN],Limit;
int n,m;
int dp[MAXN][2],g[MAXN],p[MAXN],ans;

bool check(int x)
{
	int now=1,cnt=0;
	for(int i=1;i<=n;i++) 
		if(sum[i]-sum[now-1]>x) ++cnt,now=i;
	return cnt+1<=m;
}

int main()
{
	scanf("%d%d",&n,&m);m++;
	for(int a,i=1;i<=n;i++) scanf("%d",&a),sum[i]=sum[i-1]+a,Limit=max(Limit,a);
	int l=Limit,r=sum[n];
	while(l<=r)
	{
		int mid=(l+r)>>1;
		if(check(mid)) r=mid-1;
		else l=mid+1;
	}
	Limit=l;
	int pre=0,now=0;
	dp[0][0]=1;g[0]=1;
	int pos=0;
	for(int i=1;i<=n;i++)
	{
		while(sum[i]-sum[pos]>Limit) ++pos;
		p[i]=pos;g[i]=1;
	}
	for(int i=1;i<=m;i++) 
	{
		pre=now;
		now=pre^1;
		memset(dp[now],0,sizeof(dp[now]));
		for(int j=1;j<=n;j++) dp[j][now]=(dp[p[j]][pre]+g[j-1]-g[p[j]])%MOD;
		ans=(ans+dp[n][now])%MOD;
		g[0]=0;
		for(int j=1;j<=n;j++) g[j]=g[j-1]+dp[j][now];
	}
	printf("%d %d\n",Limit,ans);
	
	return 0;
}
