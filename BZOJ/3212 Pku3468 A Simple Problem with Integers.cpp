#include <iostream>
#include <cstdio>
#include <cstring>
#include <cstdlib>

using namespace std;

const int MAXN = 100000 + 10;

struct Node
{
	int l,r,add;
	long long sum;
} segtree[MAXN<<2];

int n,m,num[MAXN];

void pushup(int ro)
{
	segtree[ro].sum=segtree[ro<<1].sum+segtree[ro<<1|1].sum;
}

void pushdown(int ro,int k)
{
	segtree[ro<<1].add+=segtree[ro].add;
	segtree[ro<<1|1].add+=segtree[ro].add;
	segtree[ro<<1].sum+=(long long)(k-(k>>1))*segtree[ro].add;
	segtree[ro<<1|1].sum+=(long long)(k>>1)*segtree[ro].add;
	segtree[ro].add=0;
}

void Build(int ro,int l,int r)
{
	segtree[ro].l=l;
	segtree[ro].r=r;
	segtree[ro].add=0;
	if(l==r)
	{
		segtree[ro].sum=num[l];
		return;
	}
	int mid=(l+r)>>1;
	Build(ro<<1,l,mid);
	Build(ro<<1|1,mid+1,r);
	pushup(ro);
	return;
}

void Update(int ro,int l,int r,int v)
{
	if(l==segtree[ro].l && r==segtree[ro].r)
	{
		segtree[ro].add+=v;
		segtree[ro].sum+=(r-l+1)*v;
		return;
	}
	pushdown(ro,segtree[ro].r-segtree[ro].l+1);
	int mid=(segtree[ro].l+segtree[ro].r)>>1;
	if(r<=mid) Update(ro<<1,l,r,v);
	else if(l>mid) Update(ro<<1|1,l,r,v);
	else 
	{
		Update(ro<<1,l,mid,v);
		Update(ro<<1|1,mid+1,r,v);
	}
	pushup(ro);
}

long long Query(int ro,int l,int r)
{
	if(l==segtree[ro].l && r==segtree[ro].r) return segtree[ro].sum;
	pushdown(ro,segtree[ro].r-segtree[ro].l+1);
	int mid=(segtree[ro].l+segtree[ro].r)>>1;
	if(r<=mid) return Query(ro<<1,l,r);
	else if(l>mid) return Query(ro<<1|1,l,r);
	else return Query(ro<<1,l,mid)+Query(ro<<1|1,mid+1,r);
}

int main()
{
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++) scanf("%d",&num[i]);
	Build(1,1,n);
	while(m--)
	{
		char ch;
		int a,b,c;
		scanf("\n%c",&ch);
		if(ch=='Q')
		{
			scanf("%d%d",&a,&b);
			printf("%lld\n",Query(1,a,b));
		}
		else 
		{
			scanf("%d%d%d",&a,&b,&c);
			Update(1,a,b,c);
		}
	}
	return 0;
}
