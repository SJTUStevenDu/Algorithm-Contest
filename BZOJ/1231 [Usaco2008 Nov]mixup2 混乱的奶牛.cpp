/*
DATE : 2013-1-26 
RATING : 2
TAG : 状圧DP 
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

int a[17];
int n,k;
long long dp[16][1<<16];
long long ans;

int main()
{
	scanf("%d%d",&n,&k);
	for(int i=0;i<n;i++) scanf("%d",&a[i]);
	for(int i=0;i<n;i++) dp[i][1<<i]=1;
	for(int i=1;i<(1<<n);i++) 
	{
		for(int j=0;j<n;j++) if(i&(1<<j))
		{
			for(int l=0;l<n;l++)
			{
				if(!((1<<l)&i) && abs(a[j]-a[l])>k) dp[l][(1<<l) | i]+=dp[j][i];
			}
		}
	}
	for(int i=0;i<n;i++) ans+=dp[i][(1<<n)-1];
	printf("%lld\n",ans);
	
	return 0;
}
