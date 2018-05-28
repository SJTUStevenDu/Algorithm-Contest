/*
DATE : 2013-4-27
RATING : 3
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

const int MAXN = 80;

struct Node
{
	int w,data,f;
} a[MAXN];

int n,K;
int dp[MAXN][MAXN][MAXN];
int sum[MAXN];

bool cmp1(Node A,Node B)
{
	return A.w<B.w;
}

bool cmp2(Node A,Node B)
{
	return A.data<B.data;
}

int main()
{
	scanf("%d%d",&n,&K);
	for(int i=1;i<=n;i++) scanf("%d",&a[i].data);
	for(int i=1;i<=n;i++) scanf("%d",&a[i].w);
	for(int i=1;i<=n;i++) scanf("%d",&a[i].f);
	sort(a+1,a+1+n,cmp1);
	for(int i=1;i<=n;i++) a[i].w=i;
	sort(a+1,a+1+n,cmp2);
	for(int i=1;i<=n;i++) 
		for(int x=1;x<=n;x++) if(a[i].w>=x) dp[i][i][x]=a[i].f;else dp[i][i][x]=a[i].f+K;
	for(int i=1;i<=n;i++) sum[i]=sum[i-1]+a[i].f;
	for(int x=n;x;x--)
		for(int l=1;l<n;l++)
			for(int i=1;i+l<=n;i++)
			{
				int j=l+i;
				int res=0x7FFFFFFF>>2;
				for(int k=i;k<=j;k++)
				{
					if(a[k].w>=x) res=min(res,dp[i][k-1][a[k].w]+dp[k+1][j][a[k].w]+sum[j]-sum[i-1]);
					res=min(res,dp[i][k-1][x]+dp[k+1][j][x]+sum[j]-sum[i-1]+K);
				}
				dp[i][j][x]=res;
			}
	printf("%d\n",dp[1][n][1]);
	
	return 0;
}
