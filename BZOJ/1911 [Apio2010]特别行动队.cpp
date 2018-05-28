/*
DATE : 2013-3-7 
RATING : 3
TAG : DP + –±¬ ”≈ªØ 
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

long long dp[MAXN],sum[MAXN];
int n;
long long a,b,c,d;
int q[MAXN],head,tail;

long long calc(int j,int k)
{
	return dp[j]-dp[k]+a*sum[j]*sum[j]-a*sum[k]*sum[k]-b*sum[j]+b*sum[k];
}

int main()
{
	scanf("%d",&n);
	scanf("%lld%lld%lld",&a,&b,&c);
	for(int i=1;i<=n;i++) 
	{
		scanf("%lld",&d);
		sum[i]=sum[i-1]+d;
	}
	for(int i=1;i<=n;i++)
	{
		while(head<tail && calc(q[head],q[head+1])<=2*a*sum[i]*(sum[q[head]]-sum[q[head+1]])) head++;
		long long tmp;
		tmp=sum[i]-sum[q[head]];
		dp[i]=dp[q[head]]+tmp*tmp*a+tmp*b+c;
		while(head<tail && calc(q[tail-1],q[tail])*(sum[q[tail]]-sum[i])<=calc(q[tail],i)*(sum[q[tail-1]]-sum[q[tail]])) tail--;
		q[++tail]=i;
	}
	printf("%lld\n",dp[n]);
	
	return 0;
}
