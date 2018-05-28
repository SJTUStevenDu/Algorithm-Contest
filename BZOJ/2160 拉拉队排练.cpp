#include <iostream>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <cmath>
#include <algorithm>
#include <fstream>

using namespace std;

const int MAXN = 2000000 + 10;
const int MOD = 19930726;

char s[MAXN],a[MAXN];
int p[MAXN],n,idx,mx;
long long k,num[MAXN],ans=1,cnt;

long long QuickMod(long long a,long long b)
{
	long long res=1;
	while(b)
	{
		if(b&1) res=(res*a)%MOD;
		a=(a*a)%MOD;
		b>>=1;
	}
	return res;
}

int main()
{
	scanf("%d",&n);
	scanf("%lld",&k);
	n=0;
	scanf("%s",s);
	a[0]='$';
	for(int i=0;s[i];i++) 
	{
		a[++n]='#';
		a[++n]=s[i];
	}
	a[++n]='#';
	for(int i=1;i<=n;i++) 
	{
		if(mx>i) p[i]=min(mx-i,p[2*idx-i]);else p[i]=1;
		for(;a[i+p[i]]==a[i-p[i]];p[i]++);
		if(mx<i+p[i])
		{
			mx=i+p[i];
			idx=i;
		}
	}
	for(int i=1;i<=n;i++)
	{
		if(i&1) continue;
		++num[1];
		--num[p[i]];
	}
	for(int i=1;i<=n;i++) num[i]+=num[i-1];
	for(int i=1;i<=n;i+=2) cnt+=num[i];
	if(cnt<k) 
	{
		puts("-1");
		return 0;
	}
	int first=n+1-(n&1);
	for(;!num[first];first-=2);
	for(;;first-=2)
	{
		if(k<=num[first])
		{
			ans=(ans*QuickMod((long long)first,k))%MOD;
			break;
		}
		else 
		{
			ans=(ans*QuickMod((long long)first,num[first]))%MOD;
			k-=num[first];
		}
	}
	printf("%lld\n",ans);
	
	return 0;
}
