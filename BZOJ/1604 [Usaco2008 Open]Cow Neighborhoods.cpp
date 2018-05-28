/*
DATE : 2013-2-16 
RATING : 3 
TAG : SBT + ²¢²é¼¯ 
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

const int MAXN = 100000 + 5;
const int INF = ~0U>>2;

struct Size_Balanced_Tree
{
	int left,right,data,num,size;
} SBT[MAXN];

int stk[MAXN],ro,top;
int n,Lim,father[MAXN];

struct Node
{
	int x,y;
} Cow[MAXN];

bool cmp(Node a,Node b)
{
	return a.x<b.x;
}

int getfather(int x)
{
	if(father[x]==x) return x;
	else return father[x]=getfather(father[x]);
}

void Left_Rotate(int &p)
{
	int k=SBT[p].right;
	SBT[p].right=SBT[k].left;
	SBT[k].left=p;
	SBT[k].size=SBT[p].size;
	SBT[p].size=SBT[SBT[p].left].size+SBT[SBT[p].right].size+1;
	p=k;
}

void Right_Rotate(int &p)
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
		else if(SBT[SBT[SBT[p].right].left].size>SBT[SBT[p].right].size) Right_Rotate(SBT[p].right),Left_Rotate(p);
		else return;
	}
	Maintain(SBT[p].left,false);
	Maintain(SBT[p].right,true);
	Maintain(p,false);
	Maintain(p,true);
}

void Insert(int &p,int v,int num)
{
	if(!p)
	{
		p=stk[top--];
		SBT[p].left=SBT[p].right=0;
		SBT[p].data=v;
		SBT[p].num=num;
		SBT[p].size=1;
		return;
	}
	SBT[p].size++;
	if(v<SBT[p].data) Insert(SBT[p].left,v,num);
	else Insert(SBT[p].right,v,num);
	Maintain(p,v>SBT[p].data);
}

int tt;
int Delete(int &p,int v)
{
	int k=SBT[p].data;
	int q=SBT[p].num;
	SBT[p].size--;
	if(v==k || (v<k && SBT[p].left==0) || (v>k && SBT[p].right==0))
	{
		if(SBT[p].left==0 || SBT[p].right==0) 
		{
			stk[++top]=p;
			p=SBT[p].left+SBT[p].right;
		}
		else 
		{
			SBT[p].data=Delete(SBT[p].left,v+1);
			SBT[p].num=tt;
		}
		tt=q;
		return k;
	}
	if(v<k) return Delete(SBT[p].left,v);
	else return Delete(SBT[p].right,v);
}

int Getpred(int v)
{
	int p=ro,re=-INF,number=-1;
	while(p)
	{
		if(SBT[p].data<v && SBT[p].data>re) re=SBT[p].data,number=SBT[p].num;
		if(SBT[p].data<v) p=SBT[p].right;else p=SBT[p].left;
	}
	return number;
}

int Getsucc(int v)
{
	int p=ro,re=INF,number=-1;
	while(p)
	{
		if(SBT[p].data>v && SBT[p].data<re) re=SBT[p].data,number=SBT[p].num;
		if(SBT[p].data<v) p=SBT[p].right;else p=SBT[p].left;
	}
	return number;
}

int main()
{
	scanf("%d%d",&n,&Lim);
	for(int i=1;i<=n;i++) scanf("%d%d",&Cow[i].x,&Cow[i].y);
	for(int i=1;i<=n;i++) father[i]=i;
	for(int i=1;i<=n;i++) Cow[i].x=Cow[i].x+Cow[i].y,Cow[i].y=Cow[i].x-2*Cow[i].y;
	for(int i=1;i<MAXN;i++) stk[++top]=i;
	sort(Cow+1,Cow+1+n,cmp);
	int l=1;
	for(int i=1;i<=n;i++) 
	{
		while(l<i && Cow[l].x+Lim<Cow[i].x) Delete(ro,Cow[l].y),l++;
		int t1=Getpred(Cow[i].y+1),t2=Getsucc(Cow[i].y-1);
		if(t1!=-1 && Cow[i].y-Cow[t1].y<=Lim) father[getfather(t1)]=getfather(i);
		if(t2!=-1 && Cow[t2].y-Cow[i].y<=Lim) father[getfather(t2)]=getfather(i);
		Insert(ro,Cow[i].y,i);
	}
	int Belong[MAXN]={0};
	for(int i=1;i<=n;i++) Belong[getfather(i)]++;
	int ans1=0,ans2=0;
	for(int i=1;i<=n;i++) 
	{
		if(Belong[i]) ans1++;
		ans2=max(ans2,Belong[i]);
	}
	printf("%d %d\n",ans1,ans2);
	
	return 0;
}
