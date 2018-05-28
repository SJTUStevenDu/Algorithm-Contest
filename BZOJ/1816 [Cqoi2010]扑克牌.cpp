#include <iostream>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <cmath>
#include <algorithm>
#include <fstream>

using namespace std;

const int MAXN = 100 + 10;
const int INF = 1000000000;

int n,a[MAXN];

bool check(int x)
{
	long long res=0;
	for(int i=0;i<=n;i++) if(x>a[i]) res+=(long long)(x-a[i]);
	return res<=x;
}

int main()
{
	scanf("%d",&n);
	for(int i=0;i<=n;i++) scanf("%d",&a[i]);
	int l=0,r=INF;
	while(l<=r)
	{
		int mid=(l+r)>>1;
		if(check(mid)) l=mid+1;
		else r=mid-1;
	}
	printf("%d\n",r);
	
	return 0;
}
