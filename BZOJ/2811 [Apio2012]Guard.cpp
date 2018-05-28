/*
DATE : 2013-5-5 
RATING : 3
TAG : DP + Greedy + Scan
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

const int MAXN = 1<<17;

struct Node 
{
	int l,r;
} a[MAXN];

bool cmp(Node A,Node B)
{
	return A.l<B.l || (A.l==B.l && A.r>B.r);
}

int tree[MAXN<<1];
int n,m,k,num;
int d[MAXN],v[MAXN],tot;
int F[MAXN],G[MAXN];
bool GotTheAns;

void Paint(int ro,int l,int r,int curl,int curr)
{
	if(l==curl && r==curr) {tree[ro]=1;return;}
	int mid=(curl+curr)>>1;
	if(r<=mid) Paint(ro<<1,l,r,curl,mid);
	else if(l>mid) Paint(ro<<1|1,l,r,mid+1,curr);
	else 
	{
		Paint(ro<<1,l,mid,curl,mid);
		Paint(ro<<1|1,mid+1,r,mid+1,curr);
	}
}

int get(int x)
{
	int re=0;
	for(int i=x+MAXN-1;i;i>>=1) re|=tree[i];
	return re^1;
}

int main()
{
	scanf("%d%d%d",&n,&k,&m);
	while(m--)
	{
		int xx,b,c;
		scanf("%d%d%d",&xx,&b,&c);
		if(!c) Paint(1,xx,b,1,MAXN);
		else 
		{
			a[++num].l=xx;
			a[num].r=b;
		}
	}
	m=num;
	for(int i=1;i<=n;i++) d[i]=d[i-1]+get(i);
	for(int i=1;i<=n;i++) if(get(i)) v[++tot]=i;
	for(int i=1;i<=m;i++)
	{
		int tmp=a[i].l;
		a[i].l=d[a[i].l];
		if(v[a[i].l]<tmp) a[i].l++;
		a[i].r=d[a[i].r];
	}
	sort(a+1,a+1+m,cmp);
	num=1;
	for(int i=2;i<=m;i++)
	{
		if(num)
			while(a[i].r<=a[num].r && a[i].l>=a[num].l)
			{
				--num;
				if(!num) break;
			}
		a[++num]=a[i];
	}
	m=num;
	if(tot==k)
	{
		for(int i=1;i<=tot;i++) printf("%d\n",v[i]);
		return 0;
	}
	for(int i=1;i<=m;i++) 
	{
		if(F[i]) continue;
		F[i]=F[i-1]+1;
		for(int j=i+1;j<=m;j++)
		{
			if(a[j].l<=a[i].r) F[j]=F[i];
			else break;
		}
	}
	for(int i=m;i;i--)
	{
		if(G[i]) continue;
		G[i]=G[i+1]+1;
		for(int j=i-1;j;j--)
		{
			if(a[j].r>=a[i].l) G[j]=G[i];
			else break;
		}
	}
	for(int i=1;i<=m;i++)
	{
		if(F[i]!=F[i-1]+1) continue;
		if(a[i].l==a[i].r) {GotTheAns=1;printf("%d\n",v[a[i].l]);continue;}
		int L=1,R=m-1;
		int pL=i-1,pR;
		if(a[m].l<=a[i].r-1) pR=m+1;
		else while(L<=R) 
		{
			int mid=(L+R)>>1;
			if(a[mid].l<=a[i].r-1 && a[mid+1].l>a[i].r-1) {pR=mid+1;break;}
			if(a[mid].l<=a[i].r-1) L=mid+1;
			else R=mid-1;
		}
		if(a[pL].r==a[i].r-1) --pL;
		if(F[pL]+1+G[pR]>k)
		{
			GotTheAns=1;
			printf("%d\n",v[a[i].r]);
		}
	}
	if(!GotTheAns) printf("%d\n",-1);
	
	return 0;
}
