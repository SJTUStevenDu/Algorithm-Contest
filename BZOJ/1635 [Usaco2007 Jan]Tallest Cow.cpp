/*
DATE : 2012-12-5 
RATING : 1
TAG : 
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

using namespace std;

const int MAXN = 10000 + 5;

struct Node
{
	int l,r;
} a[MAXN];

int n,m,s,b,sum[MAXN];

bool cmp(Node a,Node b)
{
	return a.l<b.l || (a.l==b.l && a.r<b.r);
}

int main()
{
	scanf("%d%d%d%d",&n,&b,&s,&m);
	for(int i=1;i<=m;i++) 
	{
		scanf("%d%d",&a[i].l,&a[i].r);
		if(a[i].l>a[i].r) swap(a[i].l,a[i].r);
	}
	sort(a+1,a+1+m,cmp);
	for(int i=1;i<=m;i++) 
		if(a[i].l!=a[i-1].l || a[i].r!=a[i-1].r) sum[a[i].l+1]--,sum[a[i].r]++;
	for(int i=1;i<=n;i++) 
	{
		s+=sum[i];
		printf("%d\n",s);
	}
	
	return 0;
}
