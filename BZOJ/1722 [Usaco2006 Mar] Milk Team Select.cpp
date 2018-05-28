/*
DATE : 2013-5-14 
RATING : 2
TAG : Ê÷ÐÍ±³°ü 
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
const int INF = 0x7FFFFFFF>>2;

int dp[MAXN][2][MAXN],g[MAXN],a[MAXN],head[MAXN],next[MAXN],s[MAXN];
int n,X;

void DP(int x)
{
	for(int i=0;i<=n;i++) dp[x][0][i]=dp[x][1][i]=-INF;
	s[x]=1;
	for(int i=head[x];i;i=next[i])
	{
		DP(i);
		s[x]+=s[i];
	}
	for(int i=0;i<2;i++) 
	{
		dp[x][i][0]=a[x]*i;
		for(int k=head[x];k;k=next[k])
		{
			memcpy(g,dp[x][i],sizeof(g));
			for(int l=0;l<2;l++)
				for(int p=0;p<=s[k];p++)
					for(int j=p+(i&l);j<=s[x];j++)
					{
						g[j]=max(g[j],dp[x][i][j-p-(i&l)]+dp[k][l][p]);
					}
			memcpy(dp[x][i],g,sizeof(g));
		}
	}
}

int main()
{
	scanf("%d%d",&n,&X);
	for(int b,i=1;i<=n;i++)
	{
		scanf("%d%d",&a[i],&b);
		next[i]=head[b];
		head[b]=i;
	}
	DP(0);
	for(int i=n;i>=0;i--)
		if(dp[0][0][i]>=X)
		{
			printf("%d\n",i);
			return 0;
		}
	printf("-1\n");
	
	return 0;
}
