/*
DATE : 2013-2-9 
RATING : 3
TAG : Floyd + ±¶Ôö 
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

const int MAXV = 100 + 5;
const int MAXN = 1000 + 5;
const int INF = 1000000000;
const int MAXT = 20;

int dist[MAXT][MAXV][MAXV];
int point[MAXN],tot;
int tt[MAXV],tf[MAXV];
int n,m,S,T;

void check(int &b)
{
	if(!point[b]) point[b]=++tot;
	b=point[b];
}

int main()
{
	scanf("%d%d%d%d",&n,&m,&S,&T);
	check(S);check(T);
	memset(dist,63,sizeof(dist));
	for(int a,b,c,i=1;i<=m;i++)
	{
		scanf("%d%d%d",&a,&b,&c);
		check(b);check(c);
		dist[0][b][c]=min(dist[0][b][c],a);
		dist[0][c][b]=min(dist[0][c][b],a);
	}
	for(int z=1;(1<<z)<=n;z++)
	{
		for(int i=1;i<=tot;i++)
			for(int j=1;j<=tot;j++)
				for(int k=1;k<=tot;k++)
					dist[z][i][k]=min(dist[z][i][k],dist[z-1][i][j]+dist[z-1][j][k]);
	}
	memset(tt,63,sizeof(tt));
	tt[S]=0;
	for(int k=0;(1<<k)<=n;k++) if(n&(1<<k))
	{
		memset(tf,63,sizeof(tf));
		for(int i=1;i<=tot;i++) 
			for(int j=1;j<=tot;j++)
				tf[j]=min(tf[j],tt[i]+dist[k][i][j]);
		memcpy(tt,tf,sizeof(tt));
	}
	printf("%d\n",tt[T]);
	
	return 0;
}
