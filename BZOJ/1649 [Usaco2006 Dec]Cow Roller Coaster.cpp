/*
DATE : 2012-12-10 
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

using namespace std;

struct Node
{
	int st,en,len,c,f;
} a[10005];

int n,b,l,ans=-1;
int dp[1005][1005];

bool cmp(Node a,Node b)
{
	return a.en<b.en;
}

int main()
{
	//freopen("1.txt","r",stdin);
	scanf("%d%d%d",&l,&n,&b);
	for(int i=1;i<=n;i++)
	{
		scanf("%d%d%d%d",&a[i].st,&a[i].len,&a[i].f,&a[i].c);
		a[i].en=a[i].st+a[i].len;
	}
	sort(a+1,a+1+n,cmp);
	int now=1;
	memset(dp,-20,sizeof(dp));
	dp[0][0]=0;
	for(int i=1;i<=n;i++)
	{
		if(a[now].en!=i) continue;
		for(int j=a[now].c;j<=b;j++) dp[i][j]=max(dp[i][j],dp[a[now].st][j-a[now].c]+a[now].f);
		now++;i--;
	}
	for(int i=1;i<=b;i++) ans=max(ans,dp[l][i]);
	printf("%d\n",ans);
	return 0;
}
