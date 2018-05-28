/*
DATE : 2012-12-23 
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

const int MAXN = 1000000;
const int MAXQ = 100000 + 5;

struct seg_tree
{
	int left,right,sum,add;
} seg[MAXN*8+10];

struct List_Of_Unequal
{
	int answer,type;
	bool already_del;
	List_Of_Unequal(){already_del=0;}
} List[MAXQ];

int n,cnt;

void Build(int ro,int l,int r);
void Pushdown(int ro);
void Update(int ro,int l,int r,int c);
int Query(int ro,int k);

int main()
{
	Build(1,-MAXN,MAXN);
	scanf("%d",&n);
	while(n--)
	{
		char s[20];
		scanf("%s",s);
		if(s[0]=='A')
		{
			int a,b,c;
			scanf("%d %d %d",&a,&b,&c);
			cnt++;b=c-b;
			if(a==0)
			{
				if(b>=0) List[cnt].type=-1;
				else {List[cnt].type=0;Update(1,-MAXN,MAXN,1);}
			}
			else if(a>0)
			{
				List[cnt].type=1;
				if(b==0) List[cnt].answer=1;
				else if(b>0) List[cnt].answer=b/a+1;
				else {List[cnt].answer=b/a;if(b%a==0)List[cnt].answer++;}
				if(List[cnt].answer>MAXN) List[cnt].type=-1;
				else {List[cnt].answer=max(List[cnt].answer,-MAXN);Update(1,List[cnt].answer,MAXN,1);}
			}
			else 
			{
				List[cnt].type=2;
				if(b==0) List[cnt].answer=-1;
				else if(b>0) List[cnt].answer=b/a-1;
				else {List[cnt].answer=b/a;if(b%a==0) List[cnt].answer--;}
				if(List[cnt].answer<-MAXN) List[cnt].type=-1;
				else {List[cnt].answer=min(List[cnt].answer,MAXN);Update(1,-MAXN,List[cnt].answer,1);}
			}
		}
		else if(s[0]=='D')
		{
			int a;
			scanf("%d",&a);
			if(!List[a].already_del)
			{
				List[a].already_del=1;
				if(List[a].type==0) Update(1,-MAXN,MAXN,-1);
				else if(List[a].type==1) Update(1,List[a].answer,MAXN,-1);
				else if(List[a].type==2) Update(1,-MAXN,List[a].answer,-1);
			}
		}
		else 
		{
			int k;
			scanf("%d",&k);
			printf("%d\n",Query(1,k));
		}
	}
	
	return 0;
}

void Build(int ro,int l,int r)
{
	seg[ro].left=l;seg[ro].right=r;seg[ro].add=seg[ro].sum=0;
	if(l==r) return;
	int mid=(l+r)>>1;
	Build(ro<<1,l,mid);
	Build(ro<<1|1,mid+1,r);
	return;
}

void Pushdown(int ro)
{
	if(!seg[ro].add) return;
	int mid=(seg[ro].left+seg[ro].right)>>1;
	Update(ro<<1,seg[ro].left,mid,seg[ro].add);
	Update(ro<<1|1,mid+1,seg[ro].right,seg[ro].add);
	seg[ro].add=0;
}

void Update(int ro,int l,int r,int c)
{
	if(l==seg[ro].left && r==seg[ro].right)
	{
		seg[ro].sum+=(r-l+1)*c;
		seg[ro].add+=c;
		return;
	}
	Pushdown(ro);
	int mid=(seg[ro].left+seg[ro].right)>>1;
	if(l>mid) Update(ro<<1|1,l,r,c);
	else if(r<=mid) Update(ro<<1,l,r,c);
	else {Update(ro<<1,l,mid,c);Update(ro<<1|1,mid+1,r,c);}
	seg[ro].sum=seg[ro<<1].sum+seg[ro<<1|1].sum;
}

int Query(int ro,int k)
{
	if(seg[ro].left==k && seg[ro].right==k) return seg[ro].sum;
	Pushdown(ro);
	int mid=(seg[ro].left+seg[ro].right)>>1;
	if(k<=mid) return Query(ro<<1,k);
	else return Query(ro<<1|1,k);
}
