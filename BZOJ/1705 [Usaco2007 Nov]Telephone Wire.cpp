/*
DATE : 2013-1-24 
RATING : 1.5
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

//Orz WJMZBMR && sevenkplus

using namespace std;

const int MAXN = 100000 + 5;
const int MAXH = 100 + 1;
const int INF = 1000000000;

int n,c,pre,curr,dp[2][MAXH+5],ans;
int h[MAXN];

inline int sqr(int x) {return x*x;}

int main()
{
	scanf("%d%d",&n,&c);
	for(int i=1;i<=n;i++) scanf("%d",&h[i]);
	for(int i=0;i<MAXH;i++) if(i>=h[1]) dp[1][i]=sqr(h[1]-i);else dp[1][i]=INF;
	for(int i=2;i<=n;i++)
	{
		curr=i%2;
		pre=curr^1;
		int best=INF;
		for(int j=0;j<MAXH;j++) 
		{
			best=min(best,dp[pre][j]-c*j);
			dp[curr][j]=best+c*j;
		}
		best=INF;
		for(int j=MAXH-1;j>=0;j--) 
		{
			best=min(best,dp[pre][j]+c*j);
			dp[curr][j]=min(dp[curr][j],best-c*j);
		}
		for(int j=0;j<MAXH;j++) if(h[i]>j) dp[curr][j]=INF;else dp[curr][j]+=sqr(h[i]-j);
	}
	ans=INF;
	for(int i=0;i<MAXH;i++) if(ans>=dp[curr][i]) ans=dp[curr][i];
	printf("%d\n",ans);
	
	return 0;
}
