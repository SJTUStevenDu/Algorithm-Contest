#include <iostream>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <cmath>
#include <algorithm>
#include <fstream>

using namespace std;

const int MAXN = 2000000 + 10;

char s[MAXN],a[MAXN];
int p[MAXN],idx,mx,ans,n,CaseNum;

int main()
{
	while(~scanf("%s",s))
	{
		if(s[0]=='E') break;
		idx=mx=ans=n=0;
		memset(p,0,sizeof(p));
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
			if(i+p[i]>mx)
			{
				idx=i;
				mx=i+p[i];
			}
		}
		for(int i=2;i<n;i++) ans=max(ans,p[i]-1);
		printf("Case %d: %d\n",++CaseNum,ans);
	}
	
	return 0;
}
