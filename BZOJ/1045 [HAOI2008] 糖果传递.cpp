/*
DATE : 2013-6-9 
RATING : 1
TAG : MAth
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

const int MAXN = 1000000 + 10;

int n,a[MAXN],p[MAXN];
long long ave,ans,mid;

int main()
{
	scanf("%d",&n);
	for(int i=1;i<=n;i++) scanf("%d",&a[i]),ave+=a[i];
	ave/=n;
	for(int i=1;i<=n;i++) p[i]=ave-a[i]+p[i-1];
	sort(p+1,p+1+n);
	if(n%2==0) ave=p[n/2];
	else ave=p[n/2+1];
	for(int i=1;i<=n;i++) ans+=abs(ave-p[i]);
	printf("%lld\n",ans);
	
	return 0;
}
