/*
DATE : 2012-12-10 
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

const int MAXN = 5000 + 5;

long long a[MAXN],dp[MAXN],ans;
int n;

int main()
{
	scanf("%d",&n);
	for(int i=1;i<=n;i++) scanf("%d",&a[i]);
	for(int i=1;i<=n;i++) 
	{
		for(int j=1;j<i;j++) if(a[i]>a[j]) dp[i]=max(dp[i],dp[j]);
		dp[i]++;
		ans=max(dp[i],ans);
	}
	printf("%lld\n",ans);
	
	return 0;
}
