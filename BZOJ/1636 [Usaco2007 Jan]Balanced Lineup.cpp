/*
DATE : 2012-11-29 
RATING : 1
TAG : Segment Tree
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

const int MAXN = 50000+5;
struct Segment_Tree
{
	int minn,maxn,left,right;
} segtree[MAXN<<2];

int n,q,h[MAXN];

void build(int ro,int l,int r)
{
	segtree[ro].left=l;segtree[ro].right=r;
	if(l==r)
	{
		segtree[ro].minn=segtree[ro].maxn=h[l];
		return;
	}
	int mid=(l+r)/2;
	build(ro*2,l,mid);
	build(ro*2+1,mid+1,r);
	segtree[ro].minn=min(segtree[ro*2].minn,segtree[ro*2+1].minn);
	segtree[ro].maxn=max(segtree[ro*2].maxn,segtree[ro*2+1].maxn);
	return;
}

int Getmax(int ro,int l,int r)
{
	if(segtree[ro].left==l && segtree[ro].right==r) return segtree[ro].maxn;
	int mid=(segtree[ro].left+segtree[ro].right)/2;
	if(r<=mid) return Getmax(ro*2,l,r);
	if(l>mid) return Getmax(ro*2+1,l,r);
	return max(Getmax(ro*2,l,mid),Getmax(ro*2+1,mid+1,r));
}

int Getmin(int ro,int l,int r)
{
	if(segtree[ro].left==l && segtree[ro].right==r) return segtree[ro].minn;
	int mid=(segtree[ro].left+segtree[ro].right)/2;
	if(r<=mid) return Getmin(ro*2,l,r);
	if(l>mid) return Getmin(ro*2+1,l,r);
	return min(Getmin(ro*2,l,mid),Getmin(ro*2+1,mid+1,r));
}

int main()
{
	scanf("%d%d",&n,&q);
	for(int i=1;i<=n;i++) scanf("%d",&h[i]);
	build(1,1,n);
	while(q--)
	{
		int a,b;
		scanf("%d%d",&a,&b);
		printf("%d\n",Getmax(1,a,b)-Getmin(1,a,b));
	}
	
	return 0;
}
