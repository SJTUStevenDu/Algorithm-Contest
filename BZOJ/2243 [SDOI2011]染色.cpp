/*
DATE : 2013-7-29
RATING : 4
TAG : Qtree
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

struct Edge
{
    int next,to;
} g[MAXN*2];
int gn,start[MAXN];

inline void AddEdge(int a,int b)
{
    gn++;g[gn].next=start[a];start[a]=gn;g[gn].to=b;
}

struct Seg_Tree
{
    int left,right,sum,lc,rc,lazy;
}seg[MAXN<<2];

int n,Q,head,tail,cnt,x,y,z;
int b[MAXN],fa[MAXN],dep[MAXN],suc[MAXN],q[MAXN],Top[MAXN],sz[MAXN],a[MAXN],pos[MAXN];
char opr[20];

void Pushup(int p) {seg[p].sum=seg[p<<1].sum+seg[p<<1|1].sum-(seg[p<<1].rc==seg[p<<1|1].lc);seg[p].lc=seg[p<<1].lc;seg[p].rc=seg[p<<1|1].rc;}

void Pushdown(int p)
{
    if(seg[p].lazy!=-1)
    {
        seg[p<<1|1].lc=seg[p<<1|1].rc=seg[p<<1].lc=seg[p<<1].rc=seg[p].lazy;
        seg[p<<1|1].sum=seg[p<<1].sum=1;
        seg[p<<1].lazy=seg[p<<1|1].lazy=seg[p].lazy;
        seg[p].lazy=-1;
    }
}

void Build(int p,int l,int r)
{
    seg[p].left=l;seg[p].right=r;seg[p].lazy=-1;
    if(l==r) 
    {
        seg[p].sum=1;
        seg[p].lc=seg[p].rc=a[b[l]];
        return;
    }
    int mid=(seg[p].left+seg[p].right)>>1;
    Build(p<<1,l,mid);
    Build(p<<1|1,mid+1,r);
    Pushup(p);
}

void Update(int p,int l,int r,int c)
{
    if(seg[p].left==l && seg[p].right==r)
    {
        seg[p].sum=1;
        seg[p].lc=seg[p].rc=c;
        seg[p].lazy=c;
        return;
    }
    Pushdown(p);
    int mid=(seg[p].left+seg[p].right)>>1;
    if(r<=mid) Update(p<<1,l,r,c);
    else if(l>mid) Update(p<<1|1,l,r,c);
    else Update(p<<1,l,mid,c),Update(p<<1|1,mid+1,r,c);
    Pushup(p);
}

int Query(int p,int l,int r)
{
    if(seg[p].left==l && seg[p].right==r) return seg[p].sum;
    Pushdown(p);
    int mid=(seg[p].left+seg[p].right)>>1;
    if(r<=mid) return Query(p<<1,l,r);
    else if(l>mid) return Query(p<<1|1,l,r);
    else return Query(p<<1,l,mid)+Query(p<<1|1,mid+1,r)-(seg[p<<1].rc==seg[p<<1|1].lc);
}

int QueryCol(int p,int x)
{
    if(seg[p].left==x && seg[p].right==x) return seg[p].lc;
    Pushdown(p);
    int mid=(seg[p].left+seg[p].right)>>1;
    if(x<=mid) return QueryCol(p<<1,x);
    else return QueryCol(p<<1|1,x);
}

int main()
{
	scanf("%d%d",&n,&Q);
	for(int i=1;i<=n;i++) scanf("%d",&a[i]);
	for(int i=1;i<n;i++)
    {
        scanf("%d%d",&x,&y);
        AddEdge(x,y);
        AddEdge(y,x);
    }
    head=0;tail=1;q[head]=1;dep[1]=1;
    while(head<tail)
    {
        int p=q[head++];
        for(int i=start[p];i;i=g[i].next)
        {
            int v=g[i].to;
            if(dep[v]) continue;
            q[tail++]=v;
            fa[v]=p;
            dep[v]=dep[p]+1;
        }
    }
	for(int i=tail-1;i>=0;i--)
    {
        int p=q[i];
        ++sz[p];
        sz[fa[p]]+=sz[p];
        if(sz[p]>sz[suc[fa[p]]]) suc[fa[p]]=p;
    }
    for(int i=0;i<tail;i++)
    {
        int p=q[i];
        if(Top[p]) continue;
        for(int k=p;k;k=suc[k])
        {
            Top[k]=p;
            b[++cnt]=k;
            pos[k]=cnt;
        }
    }
    Build(1,1,n);
    while(Q--)
    {
        scanf("%s",opr);
        if(opr[0]=='C')
        {
            scanf("%d%d%d",&x,&y,&z);
            while(Top[x]!=Top[y])
            {
                if(dep[Top[x]]<dep[Top[y]]) swap(x,y);
                Update(1,pos[Top[x]],pos[x],z);
                x=fa[Top[x]];
            }
            if(dep[x]<dep[y]) swap(x,y);
            Update(1,pos[y],pos[x],z);
        }
        else 
        {
            int sum=0;
            scanf("%d%d",&x,&y);
            while(Top[x]!=Top[y])
            {
                if(dep[Top[x]]<dep[Top[y]]) swap(x,y);
                sum+=Query(1,pos[Top[x]],pos[x]);
                sum-=(QueryCol(1,pos[Top[x]])==QueryCol(1,pos[fa[Top[x]]]));
                x=fa[Top[x]];
            }
            if(dep[x]<dep[y]) swap(x,y);
            sum+=Query(1,pos[y],pos[x]);
            printf("%d\n",sum);
        }
    }
    
	return 0;
}
