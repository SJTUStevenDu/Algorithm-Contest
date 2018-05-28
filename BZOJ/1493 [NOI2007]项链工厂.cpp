/*
DATE : 2013-4-23
RATING : 4
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
#include <map>
#include <vector>
 
//Orz WJMZBMR && sevenkplus
 
using namespace std;
 
const int MAXN = 500000 + 10;
 
struct Segment_Tree
{
    int left,right,lc,rc,sum,same;
} seg[MAXN<<2];
 
int n,m,a[MAXN];
int delay;
bool flip;
 
void Pushdown(int p)
{
    if(seg[p].same)
    {
        if(seg[p].left!=seg[p].right) seg[p<<1].same=seg[p<<1|1].same=seg[p].same;
        seg[p].sum=1;
        seg[p].lc=seg[p].rc=seg[p].same;
        seg[p].same=0;
    }
}
 
void Update(int p)
{
    if(seg[p].left==seg[p].right) return;
    Pushdown(p<<1);
    Pushdown(p<<1|1);
    seg[p].lc=seg[p<<1].lc;
    seg[p].rc=seg[p<<1|1].rc;
    seg[p].sum=seg[p<<1].sum+seg[p<<1|1].sum-(seg[p<<1].rc==seg[p<<1|1].lc);
}
 
void Build(int p,int l,int r)
{
    seg[p].left=l;seg[p].right=r;
    if(l==r)
    {
        seg[p].lc=seg[p].rc=a[l];
        seg[p].sum=1;
        seg[p].same=0;
        return;
    }
    int mid=(l+r)>>1;
    Build(p<<1,l,mid);
    Build(p<<1|1,mid+1,r);
    Update(p);
}
 
void Paint(int p,int l,int r,int v)
{
    Pushdown(p);
    if(seg[p].left==l && seg[p].right==r)
    {
        seg[p].same=v;
        Pushdown(p);
        return;
    }
    int mid=(seg[p].left+seg[p].right)>>1;
    if(r<=mid) Paint(p<<1,l,r,v);
    else if(l>mid) Paint(p<<1|1,l,r,v);
    else
    {
        Paint(p<<1,l,mid,v);
        Paint(p<<1|1,mid+1,r,v);
    }
    Update(p);
}
 
int Getcolor(int p,int x)
{
    Pushdown(p);
    if(seg[p].left==x && seg[p].right==x) return seg[p].lc;
    int mid=(seg[p].left+seg[p].right)>>1;
    if(x<=mid) return Getcolor(p<<1,x);
    else return Getcolor(p<<1|1,x);
}
 
int Query(int p,int l,int r)
{
    Pushdown(p);
    if(seg[p].left==l && seg[p].right==r) return seg[p].sum;
    int mid=(seg[p].left+seg[p].right)>>1;
    if(r<=mid) return Query(p<<1,l,r);
    else if(l>mid) return Query(p<<1|1,l,r);
    else return Query(p<<1,l,mid)+Query(p<<1|1,mid+1,r)-(seg[p<<1].rc==seg[p<<1|1].lc);
    Update(p);
}
 
inline void Getpos(int &x)
{
    if(flip) x=n-x+2;
    x-=delay;
    while(x<1) x+=n;
    while(x>n) x-=n;
}
 
char opr[20];
int tmpa,tmpb,tmpc;
 
int main()
{
    scanf("%d%d",&n,&tmpc);
    for(int i=1;i<=n;i++) scanf("%d",&a[i]);
    scanf("%d",&m);
    Build(1,1,n);
    while(m--)
    {
        scanf("%s",opr);
        if(opr[0]=='R')
        {
            scanf("%d",&tmpa);
            if(flip) delay-=tmpa;
            else delay+=tmpa;
            while(delay<1) delay+=n;
            while(delay>n) delay-=n;
        }
        else if(opr[0]=='F')
        {
            flip=!flip;
        }
        else if(opr[0]=='S')
        {
            scanf("%d%d",&tmpa,&tmpb);
            Getpos(tmpa);Getpos(tmpb);
            int colora=Getcolor(1,tmpa),colorb=Getcolor(1,tmpb);
            Paint(1,tmpa,tmpa,colorb);
            Paint(1,tmpb,tmpb,colora);
        }
        else if(opr[0]=='P')
        {
            scanf("%d%d%d",&tmpa,&tmpb,&tmpc);
            Getpos(tmpa);Getpos(tmpb);
            if(flip) swap(tmpa,tmpb);
            if(tmpa<=tmpb) Paint(1,tmpa,tmpb,tmpc);
            else Paint(1,tmpa,n,tmpc),Paint(1,1,tmpb,tmpc);
        }
        else if(opr[0]=='C')
        {
            if(opr[1]=='S')
            {
                scanf("%d%d",&tmpa,&tmpb);
                Getpos(tmpa);Getpos(tmpb);
                if(flip) swap(tmpa,tmpb);
                if(tmpa<=tmpb) printf("%d\n",Query(1,tmpa,tmpb));
                else
                {
                    tmpc=Query(1,tmpa,n)+Query(1,1,tmpb);
                    if(tmpc>1 && seg[1].lc==seg[1].rc) --tmpc;
                    printf("%d\n",tmpc);
                }
            }
            else
            {
                tmpa=seg[1].sum;
                if(tmpa>1 && seg[1].lc==seg[1].rc) --tmpa;
                printf("%d\n",tmpa);
            }
        }
    }
     
    return 0;
}
