#include <iostream>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <cmath>
#include <algorithm>
#include <fstream>

using namespace std;

const int MAXN = 100000 + 10;

struct Seg_Tree
{
	int left,right,lsum0,lsum1,rsum0,rsum1,lazy,sum0,sum1,sum,size;
} seg[MAXN<<2];

int n,m,a[MAXN];

void Pushup(int p);
void Pushdown(int p);
void Build(int p,int l,int r);
void MakeSame(int p,int l,int r,int v);
void Reverse(int p,int l,int r);
int QuerySum(int p,int l,int r);
int Query(int p,int l,int r);

inline int max(int a,int b,int c) {int res=a;if(b>res) res=b;if(c>res)res=c;return res;}

int main()
{
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++) scanf("%d",&a[i]);
	Build(1,1,n);
	while(m--)
	{
		int opr,x,y;
		scanf("%d%d%d",&opr,&x,&y);++x;++y;
		if(opr==0) MakeSame(1,x,y,0);
		else if(opr==1) MakeSame(1,x,y,1);
		else if(opr==2) Reverse(1,x,y);
		else if(opr==3) printf("%d\n",QuerySum(1,x,y));
		else if(opr==4) printf("%d\n",Query(1,x,y));
	}
	return 0;
}

void Pushup(int p)
{
	seg[p].sum=seg[p<<1].sum+seg[p<<1|1].sum;
	seg[p].sum0=max(seg[p<<1].sum0,seg[p<<1|1].sum0,seg[p<<1].rsum0+seg[p<<1|1].lsum0);
	seg[p].sum1=max(seg[p<<1].sum1,seg[p<<1|1].sum1,seg[p<<1].rsum1+seg[p<<1|1].lsum1);
	seg[p].lsum0=max(seg[p<<1].lsum0,(seg[p<<1].lsum0==seg[p<<1].size) ? seg[p<<1].size+seg[p<<1|1].lsum0 : 0);
	seg[p].rsum0=max(seg[p<<1|1].rsum0,(seg[p<<1|1].rsum0==seg[p<<1|1].size) ? seg[p<<1|1].size+seg[p<<1].rsum0 : 0);
	seg[p].lsum1=max(seg[p<<1].lsum1,(seg[p<<1].lsum1==seg[p<<1].size) ? seg[p<<1].size+seg[p<<1|1].lsum1 : 0);
	seg[p].rsum1=max(seg[p<<1|1].rsum1,(seg[p<<1|1].rsum1==seg[p<<1|1].size) ? seg[p<<1|1].size+seg[p<<1].rsum1 : 0);
	return;
}

void Pushdown(int p)
{
	if(seg[p].lazy==-1) return;
	int mid=(seg[p].left+seg[p].right)>>1;
	if(seg[p].lazy==2)
	{
		Reverse(p<<1,seg[p].left,mid);
		Reverse(p<<1|1,mid+1,seg[p].right);
	}
	else
	{
		MakeSame(p<<1,seg[p].left,mid,seg[p].lazy);
		MakeSame(p<<1|1,mid+1,seg[p].right,seg[p].lazy);
	}
	seg[p].lazy=-1;
}

void Build(int p,int l,int r)
{
	seg[p].left=l;seg[p].right=r;seg[p].lazy=-1;seg[p].size=r-l+1;
	if(l==r)
	{
		if(a[l])
		{
			seg[p].lsum1=seg[p].rsum1=seg[p].sum1=seg[p].sum=1;
			seg[p].lsum0=seg[p].rsum0=seg[p].sum0=0;
		}
		else 
		{
			seg[p].lsum1=seg[p].rsum1=seg[p].sum1=seg[p].sum=0;
			seg[p].lsum0=seg[p].rsum0=seg[p].sum0=1;
		}
		return;
	}
	int mid=(l+r)>>1;
	Build(p<<1,l,mid);
	Build(p<<1|1,mid+1,r);
	Pushup(p);
	return;
}

void MakeSame(int p,int l,int r,int v)
{
	if(seg[p].left==l && seg[p].right==r)
	{
		if(v)
		{
			seg[p].lsum1=seg[p].rsum1=seg[p].sum1=seg[p].sum=seg[p].size;
			seg[p].lsum0=seg[p].rsum0=seg[p].sum0=0;
		}
		else 
		{
			seg[p].lsum1=seg[p].rsum1=seg[p].sum1=seg[p].sum=0;
			seg[p].lsum0=seg[p].rsum0=seg[p].sum0=seg[p].size;
		}
		seg[p].lazy=v;
		return;
	}
	Pushdown(p);
	int mid=(seg[p].left+seg[p].right)>>1;
	if(r<=mid) MakeSame(p<<1,l,r,v);
	else if(l>mid) MakeSame(p<<1|1,l,r,v);
	else MakeSame(p<<1,l,mid,v),MakeSame(p<<1|1,mid+1,r,v);
	Pushup(p);
}

void Reverse(int p,int l,int r)
{
	if(seg[p].left==l && seg[p].right==r)
	{
		swap(seg[p].lsum0,seg[p].lsum1);
		swap(seg[p].rsum0,seg[p].rsum1);
		swap(seg[p].sum0,seg[p].sum1);
		seg[p].sum=seg[p].size-seg[p].sum;
		seg[p].lazy=1-seg[p].lazy;
		return;
	}
	Pushdown(p);
	int mid=(seg[p].left+seg[p].right)>>1;
	if(r<=mid) Reverse(p<<1,l,r);
	else if(l>mid) Reverse(p<<1|1,l,r);
	else Reverse(p<<1,l,mid),Reverse(p<<1|1,mid+1,r);
	Pushup(p);
}

int QuerySum(int p,int l,int r)
{
	if(seg[p].left==l && seg[p].right==r) return seg[p].sum;
	Pushdown(p);
	int mid=(seg[p].left+seg[p].right)>>1;
	if(r<=mid) return QuerySum(p<<1,l,r);
	if(l>mid) return QuerySum(p<<1|1,l,r);
	return QuerySum(p<<1,l,mid)+QuerySum(p<<1|1,mid+1,r);
}

int Query(int p,int l,int r)
{
	if(seg[p].left==l && seg[p].right==r) return seg[p].sum1;
	Pushdown(p);
	int mid=(seg[p].left+seg[p].right)>>1;
	if(r<=mid) return Query(p<<1,l,r);
	if(l>mid) return Query(p<<1|1,l,r);
	return max(Query(p<<1,l,mid),Query(p<<1|1,mid+1,r),min(seg[p<<1].rsum1,mid-l+1)+min(seg[p<<1|1].lsum1,r-mid));
}
