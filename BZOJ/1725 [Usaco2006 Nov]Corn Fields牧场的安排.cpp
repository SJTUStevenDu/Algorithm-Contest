/*
DATE : 2013-2-13 
RATING : 2
TAG : ??DP 
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

const int MOD = 100000000;
const int MAXN = 13;

int dp[MAXN][1<<MAXN];
int st[MAXN];
int n,m,ans;

int main()
{
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++) 
		for(int a,j=1;j<=m;j++)
		{
			scanf("%d",&a);
			st[i]=st[i]*2+a;
		}
	for(int i=0;i<(1<<m);i++) if((i|st[1])==st[1] && ((i&(i>>1))==0)) dp[1][i]=1;
	for(int i=2;i<=n;i++)
		for(int j=0;j<(1<<m);j++)
		{
			if((j&(j>>1))!=0 || (j|st[i-1])!=st[i-1]) continue;
			for(int k=0;k<(1<<m);k++)
				if((j&k)==0 && (k|st[i])==st[i] && ((k&(k>>1))==0)) 
					dp[i][k]=(dp[i][k]+dp[i-1][j])%MOD;
		}
	for(int i=0;i<(1<<m);i++) ans=(ans+dp[n][i])%MOD;
	printf("%d\n",ans);
	
	return 0;
}
