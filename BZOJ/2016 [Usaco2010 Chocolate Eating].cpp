/*
DATE : 2012-12-17 
RATING : 1
TAG : Binary Search
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

using namespace std;

const int MAXN = 50000 + 5;

long long n,h[MAXN],l,r,d,day[MAXN];

bool check(long long x)
{
	long long now=0,j=0;
	for(long long i=1;i<=d;i++)
	{
		now/=2;
		while(now<x && j<n) now+=h[++j],day[j]=i;
		if(now<x) return false;
	}
	for(long long i=j+1;i<=n;i++) day[i]=d;
	return true;
}

int main()
{
	scanf("%lld%lld",&n,&d);
	for(long long i=1;i<=n;i++) {scanf("%lld",&h[i]);r+=h[i];}
	while(l<r)
	{
		long long mid=(l+r+1)/2;
		if(check(mid)) l=mid;else r=mid-1;
	}
	check(l);
	printf("%lld\n",l);
	for(long long i=1;i<=n;i++) printf("%lld\n",day[i]);
	
	return 0;
}
