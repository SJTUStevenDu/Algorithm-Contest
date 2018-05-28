/*
DATE : 2013-7-29
RATING : 4
TAG : QTree
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

const int MAXN = 30000 + 10;
const int INF = 0x7FFFFFFF>>2;

struct Edge
{
	int next,to;
} g[MAXN*2];
int gn,start[MAXN];

inline void AddEdge(int a,int b)
{
	gn++;g[gn].to=b;g[gn].next=start[a];start[a]=gn;
}

struct Seg_Tree
{
    int left,right,maxx,sum;
} seg[MAXN<<2];

int n,Q,head,tail,cnt;
int w[MAXN],b[MAXN],sz[MAXN],fa[MAXN],Top[MAXN],dep[MAXN],q[MAXN],suc[MAXN],pos[MAXN],x,y,res;
char opr[20];

void Pushup(int p)
{
    seg[p].maxx=max(seg[p<<1].maxx,seg[p<<1|1].maxx);
    seg[p].sum=seg[p<<1].sum+seg[p<<1|1].sum;
}

void Build(int p,int l,int r)
{
    seg[p].left=l;seg[p].right=r;
    if(l==r)
    {
        seg[p].maxx=seg[p].sum=w[b[l]];
        return;
    }
    int mid=(l+r)>>1;
    Build(p<<1,l,mid);
    Build(p<<1|1,mid+1,r);
    Pushup(p);
}

void Update(int p,int v,int x)
{
    if(seg[p].left==x && seg[p].right==x)
    {
        seg[p].maxx=seg[p].sum=v;
        return;
    }
    int mid=(seg[p].left+seg[p].right)>>1;
    if(x<=mid) Update(p<<1,v,x);
    else Update(p<<1|1,v,x);
    Pushup(p);
}

int QueryMax(int p,int l,int r)
{
    if(seg[p].left==l && seg[p].right==r) return seg[p].maxx;
    int mid=(seg[p].left+seg[p].right)>>1;
    if(r<=mid) return QueryMax(p<<1,l,r);
    else if(l>mid) return QueryMax(p<<1|1,l,r);
    else return max(QueryMax(p<<1,l,mid),QueryMax(p<<1|1,mid+1,r));
}

int QuerySum(int p,int l,int r)
{
    if(seg[p].left==l && seg[p].right==r) return seg[p].sum;
    int mid=(seg[p].left+seg[p].right)>>1;
    if(r<=mid) return QuerySum(p<<1,l,r);
    else if(l>mid) return QuerySum(p<<1|1,l,r);
    else return QuerySum(p<<1,l,mid)+QuerySum(p<<1|1,mid+1,r);
}

int main()
{
	scanf("%d",&n);
	for(int i=1;i<n;i++)
	{
		scanf("%d%d",&x,&y);
		AddEdge(x,y);
		AddEdge(y,x);
	}
	for(int i=1;i<=n;i++) scanf("%d",&w[i]);
	q[0]=1;dep[1]=1;tail=1;
	while(head<tail)
	{
		int p=q[head++];
		for(int i=start[p];i;i=g[i].next)
		{
			int v=g[i].to;
			if(dep[v]) continue;
			fa[v]=p;
			dep[v]=dep[p]+1;
			q[tail++]=v;
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
        if(!Top[p])
            for(int k=p;k;k=suc[k])
            {
                Top[k]=p;
                b[++cnt]=k;
                pos[k]=cnt;
            }
	}
	Build(1,1,n);
	scanf("%d",&Q);
	while(Q--)
	{
        scanf("%s",opr);
        scanf("%d%d",&x,&y);
        if(opr[0]=='C')
        {
            Update(1,y,pos[x]);
        }
        else if(opr[1]=='M')
        {
            res=-INF;
            while(Top[x]!=Top[y])
            {
                if(dep[Top[x]]<dep[Top[y]]) swap(x,y);
                res=max(res,QueryMax(1,pos[Top[x]],pos[x]));
                x=fa[Top[x]];
            }
            if(dep[x]<dep[y]) swap(x,y);
            res=max(res,QueryMax(1,pos[y],pos[x]));
            printf("%d\n",res);
        }
        else
        {
            res=0;
            while(Top[x]!=Top[y])
            {
                if(dep[Top[x]]<dep[Top[y]]) swap(x,y);
                res+=QuerySum(1,pos[Top[x]],pos[x]);
                x=fa[Top[x]];
            }
            if(dep[x]<dep[y]) swap(x,y);
            res+=QuerySum(1,pos[y],pos[x]);
            printf("%d\n",res);
        }
	}

	return 0;
}
