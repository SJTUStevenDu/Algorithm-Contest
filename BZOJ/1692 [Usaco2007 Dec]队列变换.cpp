/*
DATE : 2013-6-23 
RATING : 3
TAG : Suffix Array
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
#include <map>
#include <vector>

//Orz WJMZBMR && sevenkplus

using namespace std;

const int MAXN = 60000 + 10;

int a[MAXN];
int n,m,cnt;
int sa[MAXN],wa[MAXN],wv[MAXN],wb[MAXN];
int ra[MAXN],rank[MAXN];
char s[MAXN];

void BuildSA()
{
	a[n++]=0;
	int p=1,*x=wa,*y=wb;
	for(int i=0;i<m;i++) ra[i]=0;
	for(int i=0;i<n;i++) ra[x[i]=a[i]]++;
	for(int i=1;i<m;i++) ra[i]+=ra[i-1];
	for(int i=n-1;i>=0;i--) sa[--ra[x[i]]]=i;
	for(int j=1;p<n;j*=2)
	{
		p=0;
		for(int i=n-j;i<n;i++) y[p++]=i;
		for(int i=0;i<n;i++) if(sa[i]>=j) y[p++]=sa[i]-j;
		for(int i=0;i<m;i++) ra[i]=0;
		for(int i=0;i<n;i++) ra[wv[i]=x[y[i]]]++;
		for(int i=1;i<m;i++) ra[i]+=ra[i-1];
		for(int i=n-1;i>=0;i--) sa[--ra[x[y[i]]]]=y[i];
		int *t=x;x=y;y=t;
		p=1;
		x[sa[0]]=0;
		for(int i=1;i<n;i++) if(y[sa[i]]==y[sa[i-1]] && y[sa[i]+j]==y[sa[i-1]+j]) x[sa[i]]=p-1;
		else x[sa[i]]=p++;
		m=p;
	}
	for(int i=0;i<n;i++) rank[sa[i]]=i;
	n--;
}

int main()
{
	scanf("%d",&n);
	char ch=0;
	for(;m<n;ch=getchar()) if(ch>='A' && ch<='Z') a[m++]=ch-'A'+1;
	int l=0,r=n-1;
	a[n++]=0;
	for(int i=n-2;i>=0;i--) a[n++]=a[i];
	m=28;
	BuildSA();
	while(l<=r)
	{
		if(rank[l]<rank[n-r-1]) s[++cnt]=a[l]+'A'-1,l++;
		else s[++cnt]=a[r]+'A'-1,r--;
	}
	for(int i=1;i<=cnt;i++)
	{
		printf("%c",s[i]);
		if(i%80==0) printf("\n");
	}
	printf("\n");
	return 0;
}
