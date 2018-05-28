/*
DATE : 2013-4-4 
RATING : 2
TAG : Disjoint Set
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

const int MAXN = 400000 + 10;

int n,m,father[MAXN],ans[MAXN],P[MAXN],T,cnt;
bool unable[MAXN];

struct Edge
{
	int next,to;
} g[MAXN];
int gn,start[MAXN];

inline void AddEdge(int a,int b)
{
	gn++;g[gn].to=b;g[gn].next=start[a];start[a]=gn;
}

int getfather(int x)
{
	if(father[x]==x) return x;
	else return father[x]=getfather(father[x]);
}

int main()
{
	scanf("%d%d",&n,&m);
	for(int a,b,i=1;i<=m;i++)
	{
		scanf("%d%d",&a,&b);
		++a;++b;
		AddEdge(a,b);AddEdge(b,a);
	}
	scanf("%d",&T);
	for(int i=1;i<=T;i++) 
	{
		scanf("%d",&P[i]);
		++P[i];
		unable[P[i]]=1;
	}
	for(int i=1;i<=n;i++) father[i]=i;
	for(int p=1;p<=n;p++) if(!unable[p])
	{
		for(int i=start[p];i;i=g[i].next)
		{
			int v=g[i].to;
			if(unable[v]) continue;
			if(getfather(p)!=getfather(v)) father[getfather(p)]=getfather(v);
		}
	}
	for(int i=1;i<=n;i++) if(!unable[i] && father[i]==i) cnt++;
	ans[T+1]=cnt;
	for(int k=T;k;k--)
	{
		int p=P[k];
		unable[p]=0;
		for(int i=start[p];i;i=g[i].next)
		{
			int v=g[i].to;
			if(unable[v]) continue;
			if(getfather(p)!=getfather(v))
			{
				cnt--;
				father[getfather(p)]=getfather(v);
			}
		}
		++cnt;
		ans[k]=cnt;
	}
	for(int i=1;i<=T+1;i++) printf("%d\n",ans[i]);
	
	return 0;
}
