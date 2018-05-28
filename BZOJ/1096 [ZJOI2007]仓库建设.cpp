/*
DATE : 2013-3-10 
RATING : 3
TAG : DP –±¬ ”≈ªØ 
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
#include <map>
#include <queue>
#include <vector>

//Orz WJMZBMR && sevenkplus

using namespace std;

const int MAXN = 1000000 + 10;

int n,x[MAXN],p[MAXN],c[MAXN];
long long dp[MAXN];
int q[MAXN],head,tail;
long long sum[MAXN],sum1[MAXN];

bool check(int k)
{
	return (dp[q[head]]-dp[q[head+1]]+sum1[q[head]]-sum1[q[head+1]])<(sum[q[head]]-sum[q[head+1]])*k;
}

int main()
{
	scanf("%d",&n);
	for(int i=1;i<=n;i++)
	{
		scanf("%d%d%d",&x[i],&p[i],&c[i]);
		sum[i]=sum[i-1]+(long long)p[i];
		sum1[i]=sum1[i-1]+(long long)p[i]*x[i];
	}
	for(int i=1;i<=n;i++)
	{
		while(head<tail && !check(x[i])) head++;
		dp[i]=dp[q[head]]-sum[q[head]]*x[i]+sum1[q[head]]+(long long)c[i]+sum[i]*x[i]-sum1[i];
		while(head<tail && (sum[q[tail]]-sum[q[tail-1]])*(dp[q[tail]]+sum1[q[tail]]-dp[i]-sum1[i])>(sum[q[tail]]-sum[i])*(dp[q[tail]]+sum1[q[tail]]-dp[q[tail-1]]-sum1[q[tail-1]])) tail--;
		q[++tail]=i;
	}
	printf("%lld\n",dp[n]);
	
	return 0;
}
