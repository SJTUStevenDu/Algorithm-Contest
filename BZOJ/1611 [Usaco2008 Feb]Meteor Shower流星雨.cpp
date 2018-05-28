/*
DATE : 2012-11-30 
RATING : 1
TAG : BFS
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

using namespace std;

const int dir[5][2]={{0,1},{1,0},{0,-1},{-1,0},{0,0}};
int m,map[405][405];//step[405][405];
int q[405*405][3],head,tail,ans=0;
bool vis[405][405],ff;

int main()
{
//	freopen("1.txt","r",stdin);
	scanf("%d",&m);
	memset(map,20,sizeof(map));
	while(m--)
	{
		int x,y,t;
		scanf("%d%d%d",&x,&y,&t);
		for(int i=0;i<5;i++)
		{
			int px=dir[i][0]+x,py=dir[i][1]+y;
			if(px>=0 && py>=0) map[px][py]=min(map[px][py],t);
		}
	}
//	for(int i=0;i<=5;i++) {for(int j=0;j<=5;j++) cout<<map[i][j]<<" ";cout<<endl;}
	q[++tail][0]=q[tail][1]=0;
	vis[0][0]=1;ff=0;
	while(head<tail && !ff)
	{
		int ux=q[++head][0],uy=q[head][1],tt=q[head][2];
		for(int i=0;i<5;i++)
		{
			int px=dir[i][0]+ux,py=dir[i][1]+uy;
			if(px>=0 && py>=0 && map[px][py]>tt+1 && !vis[px][py]) 
			{
				vis[px][py]=1,q[++tail][0]=px,q[tail][1]=py,q[tail][2]=tt+1;
				if(map[px][py]>30000000) ans=tt+1,ff=1;
			}
		}
	}
	if(!ff) printf("-1\n");
	else printf("%d\n",ans);
	
	return 0;
}
