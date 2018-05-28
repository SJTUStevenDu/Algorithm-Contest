/*
DATE : 2013-4-5 
RATING : 2
TAG : Greedy
*/

#include <iostream>
#include <cstdio>
#include <algorithm>

//Orz WJMZBMR && sevenkplus

using namespace std;

const int MAXN = 1000000 + 10;
const long long INF = 1LL<<62;

int n,a[MAXN],b[MAXN];
long long ans[MAXN];

inline int abs(int x) {return x>0 ? x : -x;}

int main()
{
	scanf("%d",&n);
	for(int i=1;i<=n;i++) scanf("%d%d",&a[i],&b[i]);
	sort(a+1,a+1+n);
	sort(b+1,b+1+n);
	for(int i=1;i<=n;i++) ans[i]=INF;
	for(int i=1;i<=n;i++) 
	{
		if(a[i]!=b[i]) ans[i]=min(ans[i],ans[i-1]+(long long)abs(a[i]-b[i]));
		if(i>1 && a[i]!=b[i-1] && b[i]!=a[i-1]) ans[i]=min(ans[i],ans[i-2]+(long long)abs(a[i]-b[i-1])+abs(a[i-1]-b[i]));
		if(i>2)
		{
			if(a[i]!=b[i-1] && a[i-1]!=b[i-1] && a[i-2]!=b[i]) ans[i]=min(ans[i],ans[i-3]+abs(a[i]-b[i-1])+abs(a[i-1]-b[i-2])+abs(a[i-2]-b[i]));
			if(a[i]!=b[i-2] && a[i-1]!=b[i] && a[i-2]!=b[i-1]) ans[i]=min(ans[i],ans[i-3]+abs(a[i]-b[i-2])+abs(a[i-1]-b[i])+abs(a[i-2]-b[i-1]));
			if(a[i]!=b[i-2] && a[i-1]!=b[i-1] && a[i-2]!=b[i]) ans[i]=min(ans[i],ans[i-3]+abs(a[i]-b[i-2])+abs(a[i-1]-b[i-1])+abs(a[i-2]-b[i]));
		}
	}
	printf("%lld\n",ans[n]);
	
	return 0;
}
