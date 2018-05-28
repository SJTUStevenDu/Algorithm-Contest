/*
DATE : 2013-3-26 
RATING : 2
TAG : Segment_Tree + Greedy
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

const int MAXN = 100000 + 10;

int a[MAXN],n,m,ans;

struct Fence
{
	int st,en;
} b[MAXN];

bool cmp(Fence A,Fence B)
{
	return A.st<B.st;
}

struct Seg_Tree
{
	int left,right,minv,add;
} seg[MAXN<<2];

void Update(int ro,int l,int r,int v);

void Pushdown(int ro)
{
	if(!ro || !seg[ro].add) return;
	int mid=(seg[ro].left+seg[ro].right)>>1;
	Update(ro<<1,seg[ro].left,mid,seg[ro].add);
	Update(ro<<1|1,mid+1,seg[ro].right,seg[ro].add);
	seg[ro].add=0;
}

void Pushup(int ro)
{
	seg[ro].minv=min(seg[ro<<1].minv,seg[ro<<1|1].minv);
}

void Build(int ro,int l,int r)
{
	seg[ro].left=l;seg[ro].right=r;seg[ro].add=0;
	if(l==r)
	{
		seg[ro].minv=a[l];
		return;
	}
	int mid=(l+r)>>1;
	Build(ro<<1,l,mid);
	Build(ro<<1|1,mid+1,r);
	Pushup(ro);
}

void Update(int ro,int l,int r,int v)
{
	if(seg[ro].left==l && seg[ro].right==r)
	{
		seg[ro].add+=v;
		seg[ro].minv+=v;
		return;
	}
	Pushdown(ro);
	int mid=(seg[ro].left+seg[ro].right)>>1;
	if(r<=mid) Update(ro<<1,l,r,v);
	else if(l>mid) Update(ro<<1|1,l,r,v);
	else Update(ro<<1,l,mid,v),Update(ro<<1|1,mid+1,r,v);
	Pushup(ro);
}

int Query(int ro,int l,int r)
{
	if(seg[ro].left==l && seg[ro].right==r) return seg[ro].minv;
	Pushdown(ro);
	int mid=(seg[ro].left+seg[ro].right)>>1;
	if(r<=mid) return Query(ro<<1,l,r);
	else if(l>mid) return Query(ro<<1|1,l,r);
	else return min(Query(ro<<1,l,mid),Query(ro<<1|1,mid+1,r));
}

int main()
{
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++) scanf("%d",&a[i]);
	Build(1,1,n);
	for(int i=1;i<=m;i++) scanf("%d%d",&b[i].st,&b[i].en);
	sort(b+1,b+1+m,cmp);
	for(int i=m;i;i--)
	{
		if(Query(1,b[i].st,b[i].en)>=1)
		{
			++ans;
			Update(1,b[i].st,b[i].en,-1);
		}
	}
	printf("%d\n",ans);
	
	return 0;
}
