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

struct Edge
{
	int nex,to,idx;
} g[MAXM];
int gn,start[MAXM];

int n,Q,sum[MAXM],ans[MAXM],c;
int next[MAXM],last[MAXM];

inline void AddEdge(int a,int b,int c)
{
	gn++;g[gn].to=b;g[gn].nex=start[a];start[a]=gn;g[gn].idx=c;
}

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
	scanf("%d%d%d",&n,&c,&Q);
	for(int i=1;i<=n;i++)
	{
		int tmp;
		scanf("%d",&tmp);
		if(last[tmp]) next[i]=last[tmp];
		last[tmp]=i;
	}
	for(int x,y,i=1;i<=Q;i++) 
	{
		scanf("%d%d",&x,&y);
		AddEdge(y,x,i);
	}
	for(int i=1;i<=n;i++)
	{
		Add(next[next[i]]+1,1);Add(next[i]+1,-1);
		for(int j=start[i];j;j=g[j].nex) ans[g[j].idx]=Query(g[j].to);
	}
	for(int i=1;i<=Q;i++) printf("%d\n",ans[i]);
	
	return 0;
}
