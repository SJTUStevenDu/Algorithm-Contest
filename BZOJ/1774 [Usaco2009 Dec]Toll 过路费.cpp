/*
DATE : 2013-2-22 
RATING : 2
TAG : Floyd
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

//Orz WJMZBMR && sevenkplus

using namespace std;

const int MAXN = 250 + 5;

int n,m,Q;

struct Node
{
	int pos,c;
} Cow[MAXN];

bool cmp(Node a,Node b)
{
	return a.c<b.c;
}

int map[MAXN][MAXN],cc[MAXN],ans[MAXN][MAXN];

int main()
{
	scanf("%d%d%d",&n,&m,&Q);
	memset(map,60,sizeof(map));
	for(int i=1;i<=n;i++) scanf("%d",&Cow[i].c),Cow[i].pos=i,cc[i]=Cow[i].c;
	sort(Cow+1,Cow+1+n,cmp);
	while(m--)
	{
		int a,b,c;
		scanf("%d%d%d",&a,&b,&c);
		map[a][b]=min(map[a][b],c);
		map[b][a]=min(map[b][a],c);
	}
	for(int i=1;i<=n;i++) 
		for(int j=1;j<=n;j++) ans[i][j]=map[i][j]+max(cc[i],cc[j]);
	for(int l=1;l<=n;l++) 
	{
		int k=Cow[l].pos;
		for(int i=1;i<=n;i++) 
			for(int j=1;j<=n;j++) 
				map[i][j]=min(map[i][j],map[i][k]+map[k][j]);
		for(int i=1;i<=n;i++) 
			for(int j=1;j<=n;j++) 
				ans[i][j]=min(ans[i][j],map[i][j]+max(cc[k],max(cc[i],cc[j])));
	}
	while(Q--)
	{
		int a,b;
		scanf("%d%d",&a,&b);
		printf("%d\n",ans[a][b]);
	}
	
	return 0;
}
