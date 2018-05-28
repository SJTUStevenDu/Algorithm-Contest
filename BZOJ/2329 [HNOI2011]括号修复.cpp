/*
DATE : 2013-03-22 
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
#include <map>
#include <vector>

//Orz WJMZBMR && sevenkplus

using namespace std;

const int MAXN = 100000 + 10;

struct Splay_Tree
{
	int left,right,fa,data,size,maxl,maxr,minl,minr,sum,same;
	bool rev,flip;
} spl[MAXN];

int n,Q;
int stk[MAXN],top,ro;

inline void Pushup(int p)
{
	spl[p].size=spl[spl[p].left].size+spl[spl[p].right].size+1;
	spl[p].sum=spl[spl[p].left].sum+spl[spl[p].right].sum+spl[p].data;
	spl[p].maxl=max(spl[spl[p].left].maxl,spl[spl[p].left].sum+spl[p].data+spl[spl[p].right].maxl);
	spl[p].maxr=max(spl[spl[p].right].maxr,spl[spl[p].right].sum+spl[p].data+spl[spl[p].left].maxr);
	spl[p].minl=min(spl[spl[p].left].minl,spl[spl[p].left].sum+spl[p].data+spl[spl[p].right].minl);
	spl[p].minr=min(spl[spl[p].right].minr,spl[spl[p].right].sum+spl[p].data+spl[spl[p].left].minr);
}

inline void Pushdown(int p);

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
		else if((spl[spl[p].fa].left==p) ^ (spl[spl[spl[p].fa].fa].left==spl[p].fa))
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

void Rotate_To(int k,int g)
{
	int p=ro;
	while(spl[spl[p].left].size!=k-1)
	{
		Pushdown(p);
		if(spl[spl[p].left].size>k-1) p=spl[p].left;
		else k-=spl[spl[p].left].size+1,p=spl[p].right;
	}
	Splay(p,g);
}

inline void Reverse(int p)
{
	if(!p) return;
	swap(spl[p].left,spl[p].right);
	swap(spl[p].minl,spl[p].minr);
	swap(spl[p].maxl,spl[p].maxr);
	spl[p].rev^=1;
}

inline void FlipNum(int p)
{
	if(!p) return;
	spl[p].sum*=-1;spl[p].data*=-1;
	int tmp;
	tmp=spl[p].maxl;spl[p].maxl=-spl[p].minl;spl[p].minl=-tmp;
	tmp=spl[p].maxr;spl[p].maxr=-spl[p].minr;spl[p].minr=-tmp;
	spl[p].flip^=1;
	if(spl[p].same!=0) spl[p].same*=-1;
}

inline void MakeSame(int p,int v)
{
	if(!p) return;
	spl[p].data=v;spl[p].sum=spl[p].size*v;spl[p].same=v;
	spl[p].maxl=spl[p].maxr=max(0,spl[p].sum);
	spl[p].minl=spl[p].minr=min(0,spl[p].sum);
}

inline void Pushdown(int p)
{
	if(!p) return;
	if(spl[p].rev)
	{
		Reverse(spl[p].left);
		Reverse(spl[p].right);
		spl[p].rev=0;
	}
	if(spl[p].flip)
	{
		FlipNum(spl[p].left);
		FlipNum(spl[p].right);
		spl[p].flip=0;
	}
	if(spl[p].same)
	{
		MakeSame(spl[p].left,spl[p].same);
		MakeSame(spl[p].right,spl[p].same);
		spl[p].same=0;
	}
}

char ch,opr[20];
int tmpa,tmpb;

int main()
{
	scanf("%d%d",&n,&Q);
	for(int i=2;i<=n+1;i++)
	{
		ch=0;
		while(ch!='(' && ch!=')') ch=getchar();
		if(ch=='(') spl[i].data=1;else spl[i].data=-1;
	}
	spl[n+2].size=1;
	for(int i=n+1;i;i--)
	{
		spl[i].right=i+1;spl[i+1].fa=i;
		Pushup(i);
	}
	ro=1;
	while(Q--)
	{
		scanf("%s",&opr);
		scanf("%d%d",&tmpa,&tmpb);
		Rotate_To(tmpa,0);
		Rotate_To(tmpb+2,ro);
		if(opr[0]=='Q') 
		{
			printf("%d\n",(spl[spl[spl[ro].right].left].maxr+1)/2-(spl[spl[spl[ro].right].left].minl-1)/2);
		}
		else if(opr[0]=='I')
		{
			FlipNum(spl[spl[ro].right].left);
		}
		else if(opr[0]=='S')
		{
			Reverse(spl[spl[ro].right].left);
		}
		else 
		{
			char tmpc;
			for(tmpc=getchar();tmpc!='(' && tmpc!=')';tmpc=getchar());
			MakeSame(spl[spl[ro].right].left,tmpc=='(' ? 1 : -1);
		}
	}	
	return 0;
}
