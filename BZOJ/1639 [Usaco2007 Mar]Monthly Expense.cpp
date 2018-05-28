/*
DATE : 2012-12-5 
RATING : 1
TAG : Binary
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

const int MAXN = 100000 + 10;

int n,m,a[MAXN],l,r;

bool check(int x)
{
	int cnt=0,sum=0;
	for(int i=1;i<n;i++)
	{
		sum+=a[i];
		if(sum>x) cnt++,sum=a[i];
	}
	if(cnt>=m) return false;
	return true;
}

int main()
{
	//freopen("1.txt","r",stdin);
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++) scanf("%d",&a[i]);
	for(int i=1;i<=n;i++) 
	{
		l=max(l,a[i]);
		r+=a[i];
	}
	while(l<r)
	{
		int mid=(l+r)/2;
		if(check(mid)) r=mid;else l=mid+1;
	}
	printf("%d\n",l);
	
	return 0;
}
