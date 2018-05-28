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

const int MOD = 100000000;
const int MAXN = 1005;

using namespace std;

struct BigNum
{
	int arr[100];
	BigNum() {memset(arr,0,sizeof(arr));}
} dp[MAXN];

int n,k;

BigNum bplus(BigNum a,BigNum b)
{
	BigNum c;
	int len=max(a.arr[0],b.arr[0]);
	for(int i=1;i<=len;i++) 
	{
		c.arr[i]+=(a.arr[i]+b.arr[i]);
		c.arr[i+1]+=c.arr[i]/MOD;
		c.arr[i]%=MOD;
	}
	if(c.arr[len+1]!=0) c.arr[0]=len+1;else c.arr[0]=len;
	return c;
}

int main()
{
	scanf("%d%d",&n,&k);
	dp[0].arr[0]=1;dp[0].arr[1]=1;
	for(int i=1;i<=k;i++) 
		for(int j=1;j<=n;j++) if(j>=i) dp[j]=bplus(dp[j-i],dp[j]);
	printf("%d",dp[n].arr[dp[n].arr[0]]);
	for(int i=dp[n].arr[0]-1;i;i--) printf("%08d",dp[n].arr[i]);
	printf("\n");
	return 0;
}
