/*
DATE : 2012-12-30 
RATING : 3
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

const int MAXN = 100000 + 5;

struct Seg_Tree
{
	int left,right,sum,lazy;
} seg[MAXN<<2];

int n,m,a,b,t;

void Build(int ro,int l,int r);
void Pushdown(int ro);
void Update(int ro,int l,int r);
int Query(int ro,int l,int r);

int main()
{
	scanf("%d%d",&n,&m);
	Build(1,1,n);
	while(m--)
	{
		scanf("%d%d%d",&t,&a,&b);
		if(t) printf("%d\n",Query(1,a,b));
		else Update(1,a,b);
	}
	
	return 0;
}

void Build(int ro,int l,int r)
{
	seg[ro].left=l;seg[ro].right=r;seg[ro].lazy=0;seg[ro].sum=0;
	if(l==r) return;
	int mid=(l+r)>>1;
	Build(ro<<1,l,mid);
	Build(ro<<1|1,mid+1,r);
}

void Pushdown(int ro)
{
	if(!seg[ro].lazy) return;
	int mid=(seg[ro].left+seg[ro].right)>>1;
	Update(ro<<1,seg[ro].left,mid);
	Update(ro<<1|1,mid+1,seg[ro].right);
	seg[ro].lazy=0;
}

void Update(int ro,int l,int r)
{
	if(l==seg[ro].left && r==seg[ro].right)
	{
		seg[ro].lazy=!seg[ro].lazy;
		seg[ro].sum=(seg[ro].right-seg[ro].left+1)-seg[ro].sum;
		return;
	}
	Pushdown(ro);
	int mid=(seg[ro].left+seg[ro].right)>>1;
	if(r<=mid) Update(ro<<1,l,r);
	else if(l>mid) Update(ro<<1|1,l,r);
	else 
	{
		Update(ro<<1,l,mid);
		Update(ro<<1|1,mid+1,r);
	}
	seg[ro].sum=seg[ro<<1].sum+seg[ro<<1|1].sum;
}

int Query(int ro,int l,int r)
{
	if(l==seg[ro].left && seg[ro].right==r) return seg[ro].sum;
	Pushdown(ro);
	int mid=(seg[ro].left+seg[ro].right)>>1;
	if(r<=mid) return Query(ro<<1,l,r);
	else if(l>mid) return Query(ro<<1|1,l,r);
	else return Query(ro<<1,l,mid)+Query(ro<<1|1,mid+1,r);
}
