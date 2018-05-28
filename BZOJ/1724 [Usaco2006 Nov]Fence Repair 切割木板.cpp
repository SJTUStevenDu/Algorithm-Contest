/*
DATE : 2013-2-11 
RATING : 2
TAG : Greedy
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

//Orz WJMZBMR && sevenkplus

using namespace std;

const int MAXN = 20000 + 5;
const int INF = 1000000000;

struct Size_Balanced_Tree
{
	int left,right,data,size;
} SBT[MAXN];

int stk[MAXN],top,ro;

inline void Left_Rotate(int &p)
{
	int k=SBT[p].right;
	SBT[p].right=SBT[k].left;
	SBT[k].left=p;
	SBT[k].size=SBT[p].size;
	SBT[p].size=SBT[SBT[p].right].size+SBT[SBT[p].left].size+1;
	p=k;
}

inline void Right_Rotate(int &p)
{
	int k=SBT[p].left;
	SBT[p].left=SBT[k].right;
	SBT[k].right=p;
	SBT[k].size=SBT[p].size;
	SBT[p].size=SBT[SBT[p].left].size+SBT[SBT[p].right].size+1;
	p=k;
}

void Maintain(int &p,bool flag)
{
	if(!flag)
	{
		if(SBT[SBT[SBT[p].left].left].size>SBT[SBT[p].right].size) Right_Rotate(p);
		else if(SBT[SBT[SBT[p].left].right].size>SBT[SBT[p].right].size) Left_Rotate(SBT[p].left),Right_Rotate(p);
		else return;
	}
	else 
	{
		if(SBT[SBT[SBT[p].right].right].size>SBT[SBT[p].left].size) Left_Rotate(p);
		else if(SBT[SBT[SBT[p].right].left].size>SBT[SBT[p].left].size) Right_Rotate(SBT[p].right),Left_Rotate(p);
		else return;
	}
	Maintain(SBT[p].left,false);
	Maintain(SBT[p].right,true);
	Maintain(p,false);
	Maintain(p,true);
}

void Insert(int &p,int v)
{
	if(!p) 
	{
		p=stk[top--];
		SBT[p].left=SBT[p].right=0;
		SBT[p].size=1;
		SBT[p].data=v;
		return;
	}
	SBT[p].size++;
	if(SBT[p].data>v) Insert(SBT[p].left,v);
	else Insert(SBT[p].right,v);
	Maintain(p,v>=SBT[p].data);
}

int Delete(int &p,int v)
{
	int k=SBT[p].data;
	SBT[p].size--;
	if(v==k || (v<k && !SBT[p].left) || (v>k && !SBT[p].right))
	{
		if(!SBT[p].left || !SBT[p].right) 
		{
			stk[++top]=p;
			p=SBT[p].left+SBT[p].right;
		}
		else SBT[p].data=Delete(SBT[p].left,v+1);
		return k;
	}
	if(v<k) return Delete(SBT[p].left,v);
	else return Delete(SBT[p].right,v);
}

int GetMin()
{
	int p=ro;
	while(SBT[p].left) p=SBT[p].left;
	return SBT[p].data;
}

int n;
long long ans;

int main()
{
	for(int i=1;i<MAXN;i++) stk[++top]=i;
	scanf("%d",&n);
	for(int a,i=1;i<=n;i++)
	{
		scanf("%d",&a);
		Insert(ro,a);
	}
	for(int i=1;i<n;i++)
	{
		int tmp1=GetMin();
		Delete(ro,tmp1);
		int tmp2=GetMin();
		int tmp3=tmp1+tmp2;
		ans+=(long long) tmp3;
		Delete(ro,tmp2);
		Insert(ro,tmp3);
	}
	printf("%lld\n",ans);
	
	return 0;
}
