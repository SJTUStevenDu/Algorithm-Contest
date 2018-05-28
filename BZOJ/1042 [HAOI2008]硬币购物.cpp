/*
DATE : 2013-4-3 
RATING : 2
TAG : DP + »›≥‚‘≠¿Ì 
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

//Orz WJMZBMR && sevenkplus

using namespace std;

const int MAXN = 100000 + 10;

int T,c[5],d[5],s,b[5];
long long dp[MAXN];
long long ans;

inline void Add(int x)
{
	if(x>=0) ans+=dp[x];
}

inline void Sub(int x)
{
	if(x>=0) ans-=dp[x];
}

int main()
{
	for(int i=0;i<4;i++) scanf("%d",&c[i]);
	scanf("%d",&T);
	dp[0]=1;
	for(int i=0;i<4;i++)
		for(int j=c[i];j<=MAXN-10;j++) dp[j]+=dp[j-c[i]];
	while(T--)
	{
		for(int i=0;i<4;i++) scanf("%d",&d[i]);
		scanf("%d",&s);
		ans=dp[s];
		for(int i=0;i<4;i++) b[i]=(d[i]+1)*c[i];
		for(int i=0;i<4;i++) Sub(s-b[i]);
		for(int i=0;i<4;i++) 
			for(int j=i+1;j<4;j++) Add(s-b[i]-b[j]);
		for(int i=0;i<4;i++)
			for(int j=i+1;j<4;j++) 
				for(int k=j+1;k<4;k++) Sub(s-b[i]-b[j]-b[k]);
		Add(s-b[0]-b[1]-b[2]-b[3]);
		printf("%lld\n",ans);
	}

	return 0;
}
