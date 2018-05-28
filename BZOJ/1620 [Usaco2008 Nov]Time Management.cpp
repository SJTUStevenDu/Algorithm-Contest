#include <iostream>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <algorithm>

using namespace std;

const int MAXN = 1000 + 10;

struct Node
{
	int t,r;
} a[MAXN];
int n,ans;

bool cmp(Node a,Node b)
{
	return a.r>b.r;
}

int main()
{
	scanf("%d",&n);
	for(int i=1;i<=n;i++) scanf("%d%d",&a[i].t,&a[i].r);
	sort(a+1,a+1+n,cmp);
	ans=a[1].r;
	for(int i=1;i<n;i++) 
	{
		ans-=a[i].t;
		ans=min(ans,a[i+1].r);
	}
	ans-=a[n].t;
	if(ans<0) printf("-1\n");
	else printf("%d\n",ans);
	
	return 0;
}
