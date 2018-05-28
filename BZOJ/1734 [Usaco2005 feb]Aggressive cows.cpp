/*
DATE : 2013-2-22 
RATING : 1
TAG : Binary Search
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

int n,m,tmp;
int pos[MAXN];
int dp[MAXN];
int last[MAXN];

bool check(int x)
{
	memset(last,0,sizeof(last));
	memset(dp,0,sizeof(dp));
	int j=0;
	for(int i=1;i<=n;i++)
	{
		while(pos[i]-pos[j]>=x) j++;
		last[i]=j-1;
	}
	for(int i=1;i<=n;i++) dp[i]=max(dp[i-1],dp[last[i]]+1);
	return dp[n]>=m;
}

int main()
{
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++) scanf("%d",&pos[i]);
	sort(pos+1,pos+1+n);
	int l=1,r=100000000;
	while(l<=r)
	{
		int mid=(l+r)>>1;
		if(check(mid)) l=mid+1;else r=mid-1;
	}
	printf("%d\n",r);
	
	return 0;
}
