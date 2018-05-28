/*
DATE : 2013-3-20 
RATING : 3
TAG : Splay
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

const int MAXN = 500000 + 100;
const int INF = 0x7FFFFFFF>>2;

struct Splay_Tree
{
	int data,left,right,fa,size;
	int maxl,maxr,maxm,sum;
	bool rev,same;
} spl[MAXN];

int n,m,stk[MAXN],top,ro;

inline void Pushdown(int p);
inline void Pushup(int p);

inline void NewNode(int &p,int f,int d)
{
	p=stk[top--];
	spl[p].left=spl[p].right=0;
	spl[p].fa=f;
	spl[p].data=d;
	spl[p].size=1;
	spl[p].maxl=spl[p].maxm=spl[p].maxr=spl[p].sum=spl[p].data;
	spl[p].rev=spl[p].same=0;
}

inline void Left_Rotate(int p)
{
	Pushdown(spl[p].fa);
	Pushdown(p);
	int k=spl[p].right;
	spl[p].right=spl[k].left;
	spl[spl[k].left].fa=p;
	spl[k].left=p;
	spl[k].size=spl[p].size;
	spl[p].size=spl[spl[p].left].size+spl[spl[p].right].size+1;
	if(spl[p].fa)
	{
		if(spl[spl[p].fa].left==p) spl[spl[p].fa].left=k;
		else spl[spl[p].fa].right=k;
	}
	spl[k].fa=spl[p].fa;
	spl[p].fa=k;
	Pushup(p);
}

inline void Right_Rotate(int p)
{
	Pushdown(spl[p].fa);
	Pushdown(p);
	int k=spl[p].left;
	spl[p].left=spl[k].right;
	spl[spl[k].right].fa=p;
	spl[k].right=p;
	spl[k].size=spl[p].size;
	spl[p].size=spl[spl[p].left].size+spl[spl[p].right].size+1;
	if(spl[p].fa)
	{
		if(spl[spl[p].fa].left==p) spl[spl[p].fa].left=k;
		else spl[spl[p].fa].right=k;
	}
	spl[k].fa=spl[p].fa;
	spl[p].fa=k;
	Pushup(p);
}

void Splay(int p,int g)
{
	for(Pushdown(p);spl[p].fa!=g;)
	{
		if(spl[spl[p].fa].fa==g)
		{
			if(spl[spl[p].fa].left==p) Right_Rotate(spl[p].fa);
			else Left_Rotate(spl[p].fa);
		}
		else if((spl[spl[spl[p].fa].fa].left==spl[p].fa) ^ (spl[spl[p].fa].left==p))
		{
			if(spl[spl[p].fa].left==p) Right_Rotate(spl[p].fa),Left_Rotate(spl[p].fa);
			else Left_Rotate(spl[p].fa),Right_Rotate(spl[p].fa);
		}
		else 
		{
			if(spl[spl[p].fa].left==p) Right_Rotate(spl[spl[p].fa].fa),Right_Rotate(spl[p].fa);
			else Left_Rotate(spl[spl[p].fa].fa),Left_Rotate(spl[p].fa);
		}
	}
	if(!g) ro=p;
	Pushup(p);
}

void Rotate_to(int k,int g)
{
	int p=ro;
	while(spl[spl[p].left].size!=k-1)
	{
		Pushdown(p);
		if(k-1<spl[spl[p].left].size) p=spl[p].left;
		else k-=spl[spl[p].left].size+1,p=spl[p].right;
	}
	Splay(p,g);
}

void MakeSame(int p,int v)
{
	if(!p) return;
	spl[p].data=v;
	spl[p].sum=v*spl[p].size;
	spl[p].maxl=spl[p].maxr=spl[p].maxm=max(spl[p].data,spl[p].sum);
	spl[p].same=1;
}

void Reverse(int p)
{
	if(!p) return;
	swap(spl[p].left,spl[p].right);
	swap(spl[p].maxl,spl[p].maxr);
	spl[p].rev^=1;
}

inline void Pushup(int p)
{
	spl[p].size=spl[spl[p].left].size+spl[spl[p].right].size+1;
	spl[p].sum=spl[spl[p].left].sum+spl[spl[p].right].sum+spl[p].data;
	spl[p].maxl=max(spl[spl[p].left].maxl,spl[spl[p].left].sum+spl[p].data+max(spl[spl[p].right].maxl,0));
	spl[p].maxr=max(spl[spl[p].right].maxr,spl[spl[p].right].sum+spl[p].data+max(spl[spl[p].left].maxr,0));
	spl[p].maxm=max(max(spl[spl[p].left].maxm,spl[spl[p].right].maxm),max(spl[spl[p].left].maxr,0)+spl[p].data+max(0,spl[spl[p].right].maxl));
}

inline void Pushdown(int p)
{
	if(!p) return;
	if(spl[p].same)
	{
		MakeSame(spl[p].left,spl[p].data);
		MakeSame(spl[p].right,spl[p].data);
		spl[p].same=0;
	}
	if(spl[p].rev)
	{
		Reverse(spl[p].left);
		Reverse(spl[p].right);
		spl[p].rev=0;
	}
}

int a[MAXN];

void Build(int &p,int l,int r,int f)
{
	int mid=(l+r)>>1;
	NewNode(p,f,a[mid]);
	if(l<mid) Build(spl[p].left,l,mid-1,p);
	if(mid<r) Build(spl[p].right,mid+1,r,p);
	Pushup(p);
}

void Insert(int pos,int tot)
{
	for(int i=1;i<=tot;++i) scanf("%d",&a[i]);
	Rotate_to(pos,0);
	Rotate_to(pos+1,ro);
	Build(spl[spl[ro].right].left,1,tot,spl[ro].right);
	Splay(spl[spl[ro].right].left,0);
}

int q[MAXN],head,tail;

void Delete(int pos,int tot)
{
	Rotate_to(pos,0);
	Rotate_to(pos+1+tot,ro);
	head=0;tail=1;
	q[head]=spl[spl[ro].right].left;
	while(head!=tail)
	{
		int p=q[head++];
		stk[++top]=p;
		if(spl[p].left) q[tail++]=spl[p].left;
		if(spl[p].right) q[tail++]=spl[p].right;
	}
	spl[spl[ro].right].left=0;
	Splay(spl[ro].right,0);
}

char opr[10];
int tmpa,tmpb,tmpc;

int main()
{
	for(int i=MAXN-1;i;i--) stk[++top]=i;
	scanf("%d%d",&n,&m);
	NewNode(ro,0,-INF);
	NewNode(spl[ro].right,ro,-INF);
	spl[0].maxl=spl[0].maxr=spl[0].maxm=-INF;
	Pushup(ro);
	Insert(1,n);
	while(m--)
	{
		scanf("%s",opr);
		if(opr[2]!='X') scanf("%d%d",&tmpa,&tmpb);
		if(opr[0]=='I') Insert(tmpa+1,tmpb);
		if(opr[0]=='D') Delete(tmpa,tmpb);
		if(opr[0]=='R')
		{
			Rotate_to(tmpa,0);
			Rotate_to(tmpa+tmpb+1,ro);
			Reverse(spl[spl[ro].right].left);
			Splay(spl[spl[ro].right].left,0);
		}
		if(opr[0]=='G')
		{
			Rotate_to(tmpa,0);
			Rotate_to(tmpa+tmpb+1,ro);
			printf("%d\n",spl[spl[spl[ro].right].left].sum);
		}
		if(opr[0]=='M') 
		{
			if(opr[2]=='K')
			{
				scanf("%d",&tmpc);
				Rotate_to(tmpa,0);
				Rotate_to(tmpa+tmpb+1,ro);
				MakeSame(spl[spl[ro].right].left,tmpc);
				Splay(spl[spl[ro].right].left,0);
			}
			else printf("%d\n",spl[ro].maxm);
		}
	}
	
	return 0;
}
