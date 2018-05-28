/*
DATE : 2012-12-16 
RATING : 1
TAG : 
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

const int MAXN = 1000 + 10;

int n,d,k;
int p[MAXN],ans;

void check(int x)
{
	int cnt=0;
	for(int i=0;i<15;i++) cnt+=((x>>i) & 1);
	if(cnt>d) return;
	cnt=n;
	bool flag=0;
	for(int i=1;i<=n;i++)
	{
		flag=0;
		for(int j=0;j<15;j++)
		{
			if(((p[i]>>j) & 1) && !((x>>j) & 1)) {flag=1;break;}
		}
		if(flag) cnt--;
	}
	ans=max(ans,cnt);
}

int main()
{
	scanf("%d%d%d",&n,&k,&d);
	for(int i=1;i<=n;i++) 
	{
		int a,b;
		scanf("%d",&a);
		while(a--) 
		{
			scanf("%d",&b);
			p[i]=p[i]+(1<<(b-1));
		}
	}
	for(int i=0;i<(1<<k);i++) check(i);
	printf("%d\n",ans);
	
	return 0;
}
