/*
DATE : 2013-2-15 
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

const int MAXN = 100000 + 5;

int n,v;
int dp[MAXN],dp2[MAXN];

int main()
{
	scanf("%d%d",&n,&v);
	for(int i=1;i<=n;i++)
	{
		int Base,m;
		scanf("%d%d",&Base,&m);
		for(int j=1;j<=Base;j++) dp2[j]=0;
		for(int j=Base;j<=v;j++) dp2[j]=dp[j-Base];
		while(m--)
		{
			int a,b;
			scanf("%d%d",&a,&b);
			for(int j=v;j>=Base+a;j--) dp2[j]=max(dp2[j],dp2[j-a]+b);
		}
		for(int j=Base;j<=v;j++) dp[j]=max(dp[j],dp2[j]);
	}
	printf("%d\n",dp[v]);
	
	return 0;
}
