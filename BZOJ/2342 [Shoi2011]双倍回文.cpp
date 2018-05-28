#include <iostream>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <cmath>
#include <algorithm>
#include <fstream>

using namespace std;

const int MAXN = 1000000 + 10;

char s[MAXN],a[MAXN];
int p[MAXN],idx,mx,n,father[MAXN],ans;

int getfather(int x)
{
	return father[x]==x ? x : father[x]=getfather(father[x]);
}

int main()
{
	scanf("%d",&n);
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
		if(i+p[i]>mx)
		{
			mx=i+p[i];
			idx=i;
		}
	}
	for(int i=1;i<=n;i++) if(a[i]=='#') father[i]=i;else father[i]=i+1;
	for(int i=3;i<=n;i+=2)
	{
		int j=getfather(max(i-p[i]/2,1));
		for(;j<i && j+p[j]<i;father[j]=getfather(j+1),j=father[j]);
		ans=max(ans,(i-j)*2);
	}
	printf("%d\n",ans);
	
	return 0;
}
