/*
DATE : 2013-5-22 
RATING : 2
TAG : Disjoint Set
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

//Orz WJMZBMR && sevenkplus

using namespace std;

const int MAXN = 1000 + 10;

struct DIST 
{
	double dist;
	int from,to;
} g[MAXN * MAXN];
int gn;

inline void Add(int a,int b,double c)
{
	gn++;g[gn].from=a;g[gn].to=b;g[gn].dist=c;
}

bool cmp(DIST A , DIST B){ return A.dist<B.dist;}

int father[MAXN],n,T,x[MAXN],y[MAXN];

int getfather(int x) {return father[x]==x ? x : father[x]=getfather(father[x]);}
inline double getdist(int x1,int x2,int y1,int y2) {return sqrt((x1-x2)*(x1-x2)+(y1-y2)*(y1-y2));}

int main()
{
	scanf("%d%d",&n,&T);
	for(int i=1;i<=n;i++) scanf("%d%d",&x[i],&y[i]);
	for(int i=1;i<=n;i++) 
		for(int j=1;j<i;j++) Add(i,j,getdist(x[i],x[j],y[i],y[j]));
	sort(g+1,g+1+gn,cmp);
	for(int i=1;i<=n;i++) father[i]=i;
	for(int i=1;i<=gn;i++) 
	{
		int p=g[i].from,q=g[i].to;
		if(getfather(p)!=getfather(q))
		{
			father[getfather(p)]=getfather(q);
			if(T==n)
			{
				printf("%.2lf\n",g[i].dist);
				return 0;
			}
			T++;
		}
	}
	
	return 0;
}
