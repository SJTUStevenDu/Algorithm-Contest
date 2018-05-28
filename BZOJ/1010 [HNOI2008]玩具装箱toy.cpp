/*
DATE : 2013-3-8 
RATING : 3
TAG : DP + –±¬ ”≈ªØ 
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
#include <queue>

//Orz WJMZBMR && sevenkplus

using namespace std;

const int MAXN = 50000 + 10;

long long dp[MAXN];
int n;
long long A[MAXN],B[MAXN],L;
int q[MAXN],head,tail;

long long calc(int j,int k)
{
	return dp[j]-dp[k]+B[j]*B[j]-B[k]*B[k];
}

int main()
{
	scanf("%d%d",&n,&L);
	for(int a,i=1;i<=n;i++)
	{
		scanf("%d",&a);
		A[i]=A[i-1]+(long long)a;
	}
	for(int i=1;i<=n;i++) A[i]+=i;
	for(int i=0;i<=n;i++) B[i]=A[i]+L+1;
	for(int i=1;i<=n;i++)
	{
		while(head<tail && calc(q[head+1],q[head])<=2*(B[q[head+1]]-B[q[head]])*A[i]) head++;
		long long tmp=B[q[head]];
		dp[i]=dp[q[head]]+(A[i]-tmp)*(A[i]-tmp);
		while(head<tail && calc(q[tail],q[tail-1])*(B[i]-B[q[tail]])>=calc(i,q[tail])*(B[q[tail]]-B[q[tail-1]])) tail--;
		q[++tail]=i;
	}
	printf("%lld\n",dp[n]);
	
	return 0;
}
