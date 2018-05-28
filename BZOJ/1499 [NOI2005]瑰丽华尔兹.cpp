/*
DATE : 2013-6-9 
RATING : 3
TAG : Dp
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

const int gx[4]={-1,1,0,0};
const int gy[4]={0,0,-1,1};
const int MAXN = 200 + 10;

char map[MAXN][MAXN];
int f[2][MAXN][MAXN];
int n,m,x,y,K,st,en,d,ans;
int q[MAXN],v[MAXN],head,tail,tmp;
int pre,now=1;

void Solve(int x,int y,int w,int l,int d)
{
	head=1;tail=0;
	for(int i=1;i<=w;i++)
	{
		if(map[x][y]=='.')
		{
			tmp=f[pre][x][y]+w-i;
			while(head<=tail && v[tail]<tmp) --tail;
			v[++tail]=tmp;
			q[tail]=i;
			while(i-q[head]>l) ++head;
			f[now][x][y]=v[head]-w+i;
		}
		else head=tail+1,f[now][x][y]=-2000000000;
		x+=gx[d];
		y+=gy[d];
	}
}

int main()
{
	scanf("%d%d%d%d%d",&n,&m,&x,&y,&K);
	for(int i=1;i<=n;i++) 
		for(int j=1;j<=m;j++) f[now][i][j]=-2000000000;
	f[now][x][y]=0;
	for(int i=1;i<=n;i++) scanf("%s",map[i]+1);
	while(K--)
	{
		now^=1;pre^=1;
		scanf("%d%d%d",&st,&en,&d);
		--d;
		if(d==0) for(int i=1;i<=m;i++) Solve(n,i,n,en-st+1,d);
		if(d==1) for(int i=1;i<=m;i++) Solve(1,i,n,en-st+1,d);
		if(d==2) for(int i=1;i<=n;i++) Solve(i,m,m,en-st+1,d);
		if(d==3) for(int i=1;i<=n;i++) Solve(i,1,m,en-st+1,d);
	}
	for(int i=1;i<=n;i++) 
		for(int j=1;j<=m;j++) ans=max(ans,f[now][i][j]);
	printf("%d\n",ans);
	
	return 0;
}
