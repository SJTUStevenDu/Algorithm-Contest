/*
DATE : 2012-12-12 
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

const int MAXN = 200000 + 5;

int n,l[MAXN],dp[MAXN];

int main()
{
	scanf("%d",&n);
	for(int i=1;i<=n;i++)
	{
		int a,b;
		scanf("%d%d",&a,&b);
		l[a+b]=max(l[a+b],a);
	}
	for(int i=1;i<=200000;i++) 
	{
		dp[i]=dp[i-1];
		if(l[i]) dp[i]=max(dp[i],dp[l[i]]+1);
	}
	printf("%d\n",dp[200000]);
	
	return 0;
}
