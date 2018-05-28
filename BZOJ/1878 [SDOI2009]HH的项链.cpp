/*
DATE : 2013-4-5 
RATING : 2
TAG : BIT
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

const int MAXM = 1000000 + 10;
const int MAXN = 50000 + 10;

struct Node
{
	int st,en,idx;
} a[MAXM];

bool cmp(Node A,Node B)
{
	return A.st<B.st;
}

int n,Q,sum[MAXM],ans[MAXM];
int next[MAXM],last[MAXM];

inline int lowbit(int x) {return x&(-x);}

inline void Add(int x,int v)
{
	for(;x<=n;x+=lowbit(x)) sum[x]+=v;
}

inline int Query(int x)
{
	int re=0;
	for(;x>0;x-=lowbit(x)) re+=sum[x];
	return re;
}

int main()
{
	scanf("%d",&n);
	for(int i=1;i<=n;i++)
	{
		int tmp;
		scanf("%d",&tmp);
		if(!last[tmp])
		{
			last[tmp]=i;
			Add(i,1);
		}
		else
		{
			next[last[tmp]]=i;
			last[tmp]=i;
		}
	}
	scanf("%d",&Q);
	for(int i=1;i<=Q;i++) scanf("%d%d",&a[i].st,&a[i].en),a[i].idx=i;
	sort(a+1,a+1+Q,cmp);
	for(int j=1,i=1;i<=n;i++)
	{
		while(j<=Q && a[j].st==i)
		{
			ans[a[j].idx]=Query(a[j].en)-Query(a[j].st-1);
			++j;
		}
		Add(i,-1);
		if(next[i]) Add(next[i],1); 
	}
	for(int i=1;i<=Q;i++) printf("%d\n",ans[i]);
	
	return 0;
}
