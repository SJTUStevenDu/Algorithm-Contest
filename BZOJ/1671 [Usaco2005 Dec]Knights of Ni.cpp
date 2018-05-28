/*
DATE : 2012-12-13 
RATING : 1
TAG : BFS
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

const int MAXN = 1000 + 5;
const int gx[4]={1,0,-1,0};
const int gy[4]={0,-1,0,1};

int n,m,sx,sy,ex,ey,ans=0x7FFFFFFF;
int head,tail,q[MAXN*MAXN][2];
int map[MAXN][MAXN];
int dist1[MAXN][MAXN],dist2[MAXN][MAXN];

bool check(int x,int y)
{
	return x>0 && x<=n && y>0 && y<=m && map[x][y]!=1;
}

int main()
{
	scanf("%d%d",&m,&n);
	for(int i=1;i<=n;i++) 
		for(int j=1;j<=m;j++)
		{
			scanf("%d",&map[i][j]);
			if(map[i][j]==2) sx=i,sy=j;
			else if(map[i][j]==3) ex=i,ey=j;
		}
	memset(dist1,20,sizeof(dist1));
	memset(dist2,20,sizeof(dist2));
	q[++tail][0]=sx,q[tail][1]=sy;dist1[sx][sy]=0;
	while(head!=tail)
	{
		int px=q[++head][0];
		int py=q[head][1];
		for(int i=0;i<4;i++) 
		{
			int ux=px+gx[i];
			int uy=py+gy[i];
			if(check(ux,uy) && dist1[ux][uy]>10000000) 
			{
				q[++tail][0]=ux;q[tail][1]=uy;
				dist1[ux][uy]=dist1[px][py]+1;
			}
		}
	}
	memset(q,0,sizeof(q));
	head=0;tail=1;
	q[tail][0]=ex,q[tail][1]=ey;dist2[ex][ey]=0;
	while(head!=tail)
	{
		int px=q[++head][0];
		int py=q[head][1];
		for(int i=0;i<4;i++) 
		{
			int ux=px+gx[i];
			int uy=py+gy[i];
			if(check(ux,uy) && dist2[ux][uy]>10000000) 
			{
				q[++tail][0]=ux;q[tail][1]=uy;
				dist2[ux][uy]=dist2[px][py]+1;
			}
		}
	}
	for(int i=1;i<=n;i++) 
		for(int j=1;j<=m;j++) 
			if(map[i][j]==4) ans=min(ans,dist1[i][j]+dist2[i][j]);
	printf("%d\n",ans);
		
	return 0;
}
