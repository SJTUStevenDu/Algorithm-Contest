/*
DATE : 2013-5-3 
RATING : 2
TAG : Enum
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

const int MAXN = 25;

long long sum[MAXN*2],a[MAXN];
int n;
int ans;

int main()
{
	scanf("%d",&n);
	for(int i=1;i<=n;i++) 
	{
		scanf("%lld",&a[i]);
		sum[i]=sum[i-1]+a[i];
	}
	for(int i=n+1;i<2*n;i++) sum[i]=sum[i-1]+a[i-n];
	for(int x1=1;x1<n;x1++)
		for(int x2=x1+1;x2<=n;x2++)
			if(sum[x2-1]-sum[x1-1]==sum[x1+n-1]-sum[x2-1]) ++ans;
	ans=ans*(ans-1)/2;
	printf("%d\n",ans);
	
	return 0;
}
