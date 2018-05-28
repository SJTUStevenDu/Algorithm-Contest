/*
DATE : 2012-11-29 
RATING : 1
TAG : simulation
*/

#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <cstdlib>
#include <iomanip>

using namespace std;

const int MAXN = 50000 + 10;
int h[MAXN],v[MAXN],sum[MAXN],ans,n;

int main()
{
	scanf("%d",&n);
	for(int i=1;i<=n;i++) scanf("%d%d",&h[i],&v[i]);
	for(int i=1;i<=n;i++) 
	{
		for(int j=i-1;j>0;j--) if(h[j]>h[i]) {sum[j]+=v[i];break;}
		for(int j=i+1;j<=n;j++)if(h[j]>h[i]) {sum[j]+=v[i];break;}
	}
	for(int i=1;i<=n;i++) ans=max(ans,sum[i]);
	printf("%d\n",ans);
	
	return 0;
}
