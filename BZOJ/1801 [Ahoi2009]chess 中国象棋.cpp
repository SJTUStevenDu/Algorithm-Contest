#include <iostream>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <cmath>
#include <algorithm>
#include <fstream>

using namespace std;

const int MAXN = 100 + 10;
const int MOD = 9999973;

long long dp[2][MAXN][MAXN];
int n,m,now,pre;
long long ans;

inline void Add(long long &a,long long b)
{
	a+=b;
	a%=MOD;
}

inline long long C(int x)
{
	long long res=x;
	res=res*(res-1)/2;
	res%=MOD;
	return res;
}

int main()
{
	scanf("%d%d",&n,&m);
	now=1;pre=0;
	dp[now][m][0]=1;
	for(int k=1;k<=n;k++)
	{
		now^=1;pre^=1;
		memset(dp[now],0,sizeof(dp[now]));
		for(int i=0;i<=m;i++)
			for(int j=0;j<=m-i;j++)
			{
				int z=m-i-j;
				Add(dp[now][i][j],dp[pre][i][j]);
				if(i<m && j) Add(dp[now][i][j],dp[pre][i+1][j-1]*(i+1));
				if(j<m && z) Add(dp[now][i][j],dp[pre][i][j+1]*(j+1));
				if(i+2<=m && j-1) Add(dp[now][i][j],dp[pre][i+2][j-2]*C(i+2));
				if(j+2<=m && z-1) Add(dp[now][i][j],dp[pre][i][j+2]*C(j+2));
				if(i+1<=m && z) Add(dp[now][i][j],dp[pre][i+1][j]*(i+1)*j);
			}
	}
	for(int i=0;i<=m;i++)
		for(int j=0;j<=m;j++) Add(ans,dp[now][i][j]);
	printf("%lld\n",ans);
	
	return 0;
}
