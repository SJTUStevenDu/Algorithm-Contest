/*
DATE : 2013-3-29 
RATING : 2
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
#include <map>
#include <queue>

//Orz WJMZBMR && sevenkplus

using namespace std;

const int MAXN = 1000 + 10;

int n,prime[MAXN],len;
unsigned long long dp[MAXN],f[MAXN],ans;
bool isPrime[MAXN];

void PreDo()
{
	for(int i=2;i<=n;i++) if(!isPrime[i])
	{
		isPrime[i]=1;
		prime[++len]=i;
		for(int j=i*i;j<=n;j+=i) isPrime[j]=1;
	}
	return;
}

int main()
{
	cin>>n;
	PreDo();
	dp[0]=1;
	for(int i=1;i<=len;i++)
	{
		memcpy(f,dp,sizeof(dp));
		for(int j=prime[i];j<=n;j*=prime[i])
		{
			for(int k=j;k<=n;k++)
				dp[k]+=f[k-j];
		}
	}
	for(int i=1;i<=n;i++) ans+=dp[i];
	ans++;
	cout<<ans<<endl;
	
	return 0;
}
