/*
DATE : 2013-3-7 
RATING : 2
TAG : MST
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

const int MAXN = 100000 + 5;
const int MAXE = 2000000 + 10;

struct Edge
{
	int from,to,w,next;
} g[MAXE];
int start[MAXN],gn;
int n,m;
int H[MAXN],father[MAXN],cnt;
long long ans;

bool cmp(Edge A,Edge B)
{
	return H[A.to]>H[B.to] || (H[A.to]==H[B.to] && A.w<B.w);
}

void AddEdge(int a,int b,int c)
{
	gn++;g[gn].to=b;g[gn].from=a;g[gn].w=c;g[gn].next=start[a];start[a]=gn;
}

int q[MAXN],head,tail;
bool vis[MAXN];

void BFS()
{
	q[head=0]=1;tail=1;vis[1]=1;
	while(head!=tail)
	{
		int p=q[head++];
		for(int i=start[p];i;i=g[i].next)
		{
			int v=g[i].to;
			if(!vis[v])
			{
				vis[v]=1;
				q[tail++]=v;
			}
		}
	}
}

int getfather(int x)
{
	if(father[x]==x) return x;
	else return father[x]=getfather(father[x]);
}

int main()
{
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++) scanf("%d",&H[i]);
	for(int i=1;i<=m;i++) 
	{
		int a,b,c;
		scanf("%d%d%d",&a,&b,&c);
		if(H[a]>=H[b]) AddEdge(a,b,c);
		if(H[b]>=H[a]) AddEdge(b,a,c);
	}
	BFS();
	printf("%d ",tail);
	sort(g+1,g+1+gn,cmp);
	for(int i=1;i<=n;i++) father[i]=i;
	for(int i=1;i<=gn;i++)
	{
		int p=g[i].from,v=g[i].to;
		if(!vis[p] || !vis[v]) continue;
		if(getfather(p)!=getfather(v))
		{
			ans+=(long long)g[i].w;
			father[getfather(p)]=getfather(v);
		}
	}
	printf("%lld\n",ans);
	
	return 0;
}
