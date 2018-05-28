/*
DATE : 2013-4-22 
RATING : 3
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

const int MAXN = 500 + 10;
const int MOD = 1024523;

int dp[MAXN][MAXN][MAXN];
char U[MAXN],D[MAXN];
int n,m;

inline void Add(int &t,int a) {t=(t+a)%MOD;}

int main()
{
	scanf("%d%d",&n,&m);
	scanf("%s",U+1);
	scanf("%s",D+1);
	dp[0][0][0]=1;
	for(int i1=0;i1<=n;i1++) 
	{
		for(int i2=0;i2<=m;i2++)
		{
			for(int j1=0;j1<=n;j1++)
			{
				if(dp[i1][i2][j1]==0) continue;
				int j2=i1+i2-j1;
				if(U[i1+1]==U[j1+1]) Add(dp[i1+1][i2][j1+1],dp[i1][i2][j1]);
				if(U[i1+1]==D[j2+1]) Add(dp[i1+1][i2][j1],dp[i1][i2][j1]);
				if(D[i2+1]==U[j1+1]) Add(dp[i1][i2+1][j1+1],dp[i1][i2][j1]);
				if(D[i2+1]==D[j2+1]) Add(dp[i1][i2+1][j1],dp[i1][i2][j1]);
			}
		}
	}
	printf("%d\n",dp[n][m][n]);
	
	return 0;
}
