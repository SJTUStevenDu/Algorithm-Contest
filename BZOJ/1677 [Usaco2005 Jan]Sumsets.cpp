/*
DATE : 2012-12-14 
RATING : 1
TAG : DP
*/

#include <iostream>
#include <cstdio>
#include <cstring>
#include <string>
#include <cstdlib>
#include <algorithm>

using namespace std;

int n;
int dp[1000005];

int main()
{
	cin>>n;
	dp[1]=1;
	int p=1;
	for (int i=2;i<=n;i+=2)	dp[i]=dp[i+1]=(dp[i-1]+dp[p])%1000000000,p++;
	cout<<dp[n]<<endl;
	return 0;
}
