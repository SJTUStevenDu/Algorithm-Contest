#include <iostream>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <cmath>
#include <algorithm>
#include <fstream>

using namespace std;

const int MAXN = 200000 + 20;

char s[MAXN],a[MAXN];
int n,p[MAXN],c[MAXN],idx,mx,ans;

int main()
{
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
		if(mx>i) p[i]=min(mx-i,p[2*idx-i]);
		else p[i]=1;
		for(;a[p[i]+i]==a[i-p[i]];p[i]++);
		if(i+p[i]>mx) {mx=i+p[i];idx=i;}
	}
	int pos=3;
	for(int i=2;i<n;i++)
		for(;pos<n && pos<i+p[i];pos++)
		{
			if(a[pos]=='#') c[pos]=pos-i;
		}
	pos=n-3;
	for(int i=n-2;i;i--)
		for(;pos && pos>i-p[i];pos--)
		{
			if(c[pos]) c[pos]+=i-pos;
		}
	for(int i=1;i<=n;i++) ans=max(ans,c[i]);
	printf("%d\n",ans);
	
	return 0;
}
