/*
DATE : 2012-12-10 
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

int n,m,L,a[50005];

bool check(int x)
{
	int k=0,cnt=0;
	for(int i=1;i<=n;i++) 
	{
		if(a[i]-k<x) cnt++;else k=a[i];
	}
	if(cnt<=m) return true;else return false;
}

int main()
{
	//freopen("1.txt","r",stdin);
	scanf("%d %d %d",&L,&n,&m);
	a[++n]=L;
	for(int i=1;i<n;i++) scanf("%d",&a[i]);
	sort(a+1,a+1+n);
	int l=1,r=L;
	while(l<=r)
	{
		int mid=(l+r)/2;
		if(check(mid)) l=mid+1;
		else r=mid-1;
	}
	printf("%d\n",r);
	
	return 0;
}
