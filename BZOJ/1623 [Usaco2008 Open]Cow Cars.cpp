#include <iostream>
#include <cstdio>
#include <algorithm>

using namespace std;

const int MAXN = 50000 + 5;
int n,m,d,l,j=1,ans;
int cnt[MAXN],a[MAXN];

int main()
{
	cin>>n>>m>>d>>l;
	for(int i=1;i<=n;i++) scanf("%d",&a[i]);
	for(int i=1;i<=n;i++) a[i]=(a[i]-l+d)/d-1;
	sort(a+1,a+1+n);
	for(int i=1;i<=n;i++) 
	{
		if(cnt[j]<=a[i]) cnt[j]++,j++,ans++;
		if(j>m) j=1;
	}
	printf("%d\n",ans);
	
	return 0;
}
