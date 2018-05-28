/*
DATE : 2013-2-14 
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

const int MAXN = 300 + 5;
const int INF = 1000000000;

int n,m;
int a[MAXN],b[MAXN];
int dp[MAXN],cost[MAXN];

int main()
{
	scanf("%d%d",&m,&n);
	for(int i=1;i<=n;i++) scanf("%d%d",&a[i],&b[i]);
	dp[0]=1;
	for(int i=1;i<=n;i++)
	{
		dp[i]=INF;
		int cur=a[i],nex=b[i];
		for(int j=i-1;j>=0;j--)
		{
			if(cur>m || nex>m) break;
			int day=dp[j]+2-(cost[j]<=m-cur);
			if(day<dp[i] || (day==dp[i] && nex<=cost[i]))
			{
				dp[i]=day;
				cost[i]=nex;
			}
			cur+=a[j];nex+=b[j];
		}
	}
	printf("%d\n",dp[n]+1);
	
	return 0;
}
