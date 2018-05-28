/*
DATE : 2012-12-19 
RATING : 3
TAG : Segment Tree
*/
 
#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <cstdlib>
#include <iomanip>
#include <cmath>
#include <vector>
#include <fstream>
#include <string>
 
//Orz WJMZBMR && sevenkplus
 
using namespace std;
 
const int MAXN = 100000 + 5;
 
struct Segment_Tree
{
    int l,r;
    long long sum,add,mul;
} seg[MAXN<<2];
 
int MOD,n,q,a[MAXN];
 
void Build(int ro,int l,int r);
void Pushdown(int ro);
void Mul(int ro,int l,int r,int c);
void Add(int ro,int l,int r,int c);
long long Query(int ro,int l,int r);
 
int main()
{
    scanf("%d%d",&n,&MOD);
    for(int i=1;i<=n;i++) scanf("%d",&a[i]);
    Build(1,1,n);
    scanf("%d",&q);
    while(q--)
    {
        int a,b,c,type;
        scanf("%d",&type);
        if(type==1) 
        {
            scanf("%d %d %d",&a,&b,&c);
            Mul(1,a,b,c);
        }
        else if(type==2)
        {
            scanf("%d %d %d",&a,&b,&c);
            Add(1,a,b,c);
        }
        else
        {
            scanf("%d%d",&a,&b);
            printf("%lld\n",Query(1,a,b));
        }
    }
     
    return 0;
}
 
void Build(int ro,int l,int r)
{
    seg[ro].add=0;
    seg[ro].mul=1;
    seg[ro].l=l;
    seg[ro].r=r;
    if(l==r)
    {
        seg[ro].sum=a[l]%MOD;
        return;
    }
    int mid=(l+r)>>1;
    Build(ro<<1,l,mid);
    Build(ro<<1|1,mid+1,r);
    seg[ro].sum=(seg[ro<<1].sum+seg[ro<<1|1].sum)%MOD;
}
 
void Pushdown(int ro)
{
    int mid=(seg[ro].l+seg[ro].r)>>1;
    if(seg[ro].mul!=1) 
    {
        Mul(ro<<1,seg[ro].l,mid,seg[ro].mul);
        Mul(ro<<1|1,mid+1,seg[ro].r,seg[ro].mul);
        seg[ro].mul=1;
    }
    if(seg[ro].add!=0)
    {
        Add(ro<<1,seg[ro].l,mid,seg[ro].add);
        Add(ro<<1|1,mid+1,seg[ro].r,seg[ro].add);
        seg[ro].add=0;
    }
}
 
void Add(int ro,int l,int r,int c)
{
    if(seg[ro].l==l && seg[ro].r==r)
    {
        seg[ro].sum=(seg[ro].sum+(r-l+1)*(long long)c)%MOD;
        seg[ro].add=(seg[ro].add+(long long)c)%MOD;
        return;
    }
    int mid=(seg[ro].l+seg[ro].r)>>1;
    Pushdown(ro);
    if(r<=mid) Add(ro<<1,l,r,c);
    else if(l>mid) Add(ro<<1|1,l,r,c);
    else
    {
        Add(ro<<1,l,mid,c);
        Add(ro<<1|1,mid+1,r,c);
    }
    seg[ro].sum=(seg[ro<<1].sum+seg[ro<<1|1].sum)%MOD;
}
 
void Mul(int ro,int l,int r,int c)
{
    if(seg[ro].l==l && seg[ro].r==r)
    {
        seg[ro].add=(seg[ro].add*c)%MOD;
        seg[ro].sum=(seg[ro].sum*c)%MOD;
        seg[ro].mul=(seg[ro].mul*c)%MOD;
        return;
    }
    Pushdown(ro);
    int mid=(seg[ro].l+seg[ro].r)>>1;
    if(r<=mid) Mul(ro<<1,l,r,c);
    else if(l>mid) Mul(ro<<1|1,l,r,c);
    else
    {
        Mul(ro<<1,l,mid,c);
        Mul(ro<<1|1,mid+1,r,c);
    }
    seg[ro].sum=(seg[ro<<1].sum+seg[ro<<1|1].sum)%MOD;
}
 
long long Query(int ro,int l,int r)
{
    if(l==seg[ro].l && r==seg[ro].r) return seg[ro].sum;
    Pushdown(ro);
    int mid=(seg[ro].l+seg[ro].r)>>1;
    if(l>mid) return Query(ro<<1|1,l,r);
    if(r<=mid) return Query(ro<<1,l,r);
    return (Query(ro<<1,l,mid)+Query(ro<<1|1,mid+1,r))%MOD;
}
