/*
DATE : 2013-6-9 
RATING : 2
TAG : binary search
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
#include <map>
#include <vector>

//Orz WJMZBMR && sevenkplus

using namespace std;

const int MAXN = 200000 + 10;
const long long INF = (1<<31)-1;

long long S[MAXN],E[MAXN],D[MAXN];
int T,n;

long long Count(long long x)
{
	long long res=0;
	for(int i=1;i<=n;i++) 
	{
		if(x<S[i]) continue;
		if(x>E[i]) res+=(E[i]-S[i])/D[i]+1;
		else res+=(x-S[i])/D[i]+1;
	}
	return res;
}

int main()
{
	scanf("%d",&T);
	while(T--)
	{
		scanf("%d",&n);
		for(int i=1;i<=n;i++) scanf("%lld%lld%lld",&S[i],&E[i],&D[i]);
		long long l=0,r=INF;
		while(l<=r)
		{
			long long mid=(l+r)/2;
			if(Count(mid)%2==0) l=mid+1;
			else r=mid-1;
		}
		if(r>=INF) printf("Poor QIN Teng:(\n");
		else printf("%lld %lld\n",r+1,Count(r+1)-Count(r));
	}
	
	return 0;
}
