/*
DATE : 2012-12-6 
RATING : 1
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

const int MAXM = 1000 + 10;

struct Node
{
	int l,r,w;
} a[MAXM];

int n,m,res,ans;
int dp[MAXM];

bool cmp(Node a,Node b)
{
	return a.l<b.l || (a.l==b.l && a.r<b.r);
}

int main()
{
	scanf("%d%d%d",&n,&m,&res);
	for(int i=1;i<=m;i++)
	{
		scanf("%d%d%d",&a[i].l,&a[i].r,&a[i].w);
		a[i].r+=res;
	}
	sort(a+1,a+1+m,cmp);
	for(int i=1;i<=m;i++) 
	{
		for(int j=1;j<=m;j++) 
			if(a[j].r<=a[i].l) dp[i]=max(dp[i],dp[j]);
		dp[i]+=a[i].w;
	}
	for(int i=1;i<=m;i++) ans=max(ans,dp[i]);
	printf("%d\n",ans);
	
	return 0;
}
