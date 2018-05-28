/*
DATE : 2013-3-7 
RATING : 1
TAG : MST
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
#include <queue>
#include <vector>

//Orz WJMZBMR && sevenkplus

using namespace std;

const int MAXN = 1000 + 10;
const int MAXE = MAXN*(MAXN+1);

struct Edge
{
	int from,to,w;
} g[MAXE];
int gn;

void AddEdge(int a,int b,int c)
{
	gn++;g[gn].from=a;g[gn].to=b;g[gn].w=c;
}

bool cmp(Edge A,Edge B)
{
	return A.w<B.w;
}

int n,m,P[MAXN],ans,father[MAXN],X[MAXN],Y[MAXN];
int maxx;

int getfather(int x)
{
	if(father[x]==x) return x;
	else return father[x]=getfather(father[x]);
}

int dist(int x1,int y1,int x2,int y2)
{
	return (x1-x2)*(x1-x2)+(y1-y2)*(y1-y2);
}

int main()
{
	scanf("%d",&m);
	for(int i=1;i<=m;i++) scanf("%d",&P[i]);
	scanf("%d",&n);
	for(int i=1;i<=n;i++) scanf("%d%d",&X[i],&Y[i]);
	for(int i=1;i<=n;i++) 
		for(int j=1;j<i;j++) AddEdge(i,j,dist(X[i],Y[i],X[j],Y[j]));
	sort(g+1,g+1+gn,cmp);
	for(int i=1;i<=n;i++) father[i]=i;
	for(int i=1;i<=gn;i++) 
	{
		int p=g[i].from,v=g[i].to;
		if(getfather(p)!=getfather(v))
		{
			maxx=g[i].w;
			father[getfather(p)]=getfather(v);
		}
	}
//	cout<<maxx<<endl;
	for(int i=1;i<=m;i++) if(P[i]*P[i]>=maxx) ans++;
	printf("%d\n",ans);
	
	return 0;
}
