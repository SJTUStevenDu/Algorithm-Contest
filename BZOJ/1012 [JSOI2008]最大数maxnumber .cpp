/*
DATE : 2013-3-26 
RATING : 2
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
#include <map>
#include <queue>

//Orz WJMZBMR && sevenkplus

using namespace std;

const int MAXN = 200000 + 10;

struct Seg_Tree
{
	int l,r;
	int maxv;
} seg[MAXN<<2];

int len,Q;
int tmp,ans,MOD;
char opr;

void Build(int ro,int l,int r)
{
	seg[ro].l=l;seg[ro].r=r;
	if(l==r) return;
	int mid=(l+r)>>1;
	Build(ro<<1,l,mid);
	Build(ro<<1|1,mid+1,r);
}

void Update(int ro,int p,int v)
{
	if(seg[ro].l==p && seg[ro].r==p)
	{
		seg[ro].maxv=v;
		return;
	}
	int mid=(seg[ro].l+seg[ro].r)>>1;
	if(p<=mid) Update(ro<<1,p,v);
	else Update(ro<<1|1,p,v);
	seg[ro].maxv=max(seg[ro<<1].maxv,seg[ro<<1|1].maxv);
}

int Query(int ro,int l,int r)
{
	if(seg[ro].l==l && seg[ro].r==r) return seg[ro].maxv;
	int mid=(seg[ro].l+seg[ro].r)>>1;
	if(l>mid) return Query(ro<<1|1,l,r);
	else if(r<=mid) return Query(ro<<1,l,r);
	else return max(Query(ro<<1,l,mid),Query(ro<<1|1,mid+1,r));
}

int main()
{
	scanf("%d%lld",&Q,&MOD);
	Build(1,1,200000);
	while(Q--)
	{
		for(opr=getchar();opr!='A' && opr!='Q';opr=getchar());
		if(opr=='A')
		{
			scanf("%d",&tmp);
			++len;
			tmp=(tmp+ans)%MOD;
			Update(1,len,tmp);
		}
		else 
		{
			int TT;
			scanf("%d",&TT);
			ans=Query(1,len-TT+1,len);
			printf("%d\n",ans);
		}
	}
	
	return 0;
}
