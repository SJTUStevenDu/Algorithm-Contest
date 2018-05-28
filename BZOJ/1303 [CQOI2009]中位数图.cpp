/*
DATE : 2013-3-11 
RATING : 1
TAG : Math
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

const int MAXN = 100000 + 10;

int n,b,pos;
long long ans;
int a[MAXN],sum[MAXN];
int bsum[MAXN*2],asum[MAXN*2];

int main()
{
	scanf("%d%d",&n,&b);
	for(int i=1;i<=n;i++)
	{
		scanf("%d",&a[i]);
		if(a[i]==b) pos=i,a[i]=0;
		else if(a[i]>b) a[i]=1;
		else a[i]=-1;
		sum[i]=sum[i-1]+a[i];
	}
	for(int i=0;i<pos;i++) asum[sum[i]+MAXN]++;
	for(int i=pos;i<=n;i++) bsum[sum[i]+MAXN]++;
	for(int i=1;i<=n+MAXN+1;i++)
	{
		if(asum[i]==0 || bsum[i]==0) continue;
		ans+=(long long)asum[i]*bsum[i];
	}
	printf("%lld\n",ans);
	
	return 0;
}
