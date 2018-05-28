/*
DATE : 2013-6-24 
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

const int MAXN = 20000 + 10;

struct Node 
{
	int num,idx;
} ss[MAXN];

bool cmp(Node A,Node B)
{
	return A.num<B.num;
}

int a[MAXN],m,n,k;
int wa[MAXN],wb[MAXN],wv[MAXN],rank[MAXN],sa[MAXN],ra[MAXN],h[MAXN];

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
		for(int i=n-1;i>=0;i--) sa[--ra[wv[i]]]=y[i];
		int *t=x;x=y;y=t;
		p=1;
		x[sa[0]]=0;
		for(int i=1;i<n;i++)
			if(y[sa[i]]==y[sa[i-1]] && y[sa[i]+j]==y[sa[i-1]+j]) x[sa[i]]=p-1;
			else x[sa[i]]=p++;
		m=p;
	}
	for(int i=0;i<n;i++) rank[sa[i]]=i;
	int kk=0;
	for(int i=0;i<n;h[rank[i]]=kk,i++)
	{
		if(kk) kk--;
		for(int j=sa[rank[i]-1];a[i+kk]==a[j+kk];kk++);
	}
	n--;
}

bool check(int x)
{
	int sum=1;
	for(int i=2;i<=n;i++) if(h[i]>=x) {sum++;if(sum>=k) return true;}
	else sum=1;
	return false;
}

int main()
{
	scanf("%d %d",&n,&k);
	for(int i=0;i<n;i++) scanf("%d",&ss[i].num),ss[i].idx=i;
	sort(ss,ss+n,cmp);
	a[ss[0].idx]=1;
	m=1;
	for(int i=1;i<n;i++)
	{
		if(ss[i].num!=ss[i-1].num) m++;
		a[ss[i].idx]=m;
	}
	m++;
	BuildSA();
	int l=1,r=n;
	while(l<=r)
	{
		int mid=(l+r)>>1;
		if(check(mid)) l=mid+1;
		else r=mid-1;
	}
	printf("%d\n",r);
	
	return 0;
}
