/*
DATE : 2012-12-7 
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

const int MAXN = 105;
const int dirx[4]={1,0,-1,0};
const int diry[4]={0,-1,0,1};

int n,sx,sy,ex,ey;
bool map[MAXN][MAXN];
int step[MAXN][MAXN][4];
int q[5000000][3],head,tail,d,ans=0x7FFFFFFF;

bool check(int x,int y)
{
	return x>0 && x<=n && y>0 && y<=n && !map[x][y];
}

void bfs()
{
	while(head<tail)
	{
		int ux=q[++head][0],uy=q[head][1],d=q[head][2];
		for(int i=0;i<4;i++) 
		{
			int px=ux+dirx[i],py=uy+diry[i];
			int delta;
			if(d==i) delta=0;else delta=1;
			if(check(px,py) && step[px][py][i]>step[ux][uy][d]+delta) 
			{
				q[++tail][0]=px;
				q[tail][1]=py;
				q[tail][2]=i;
				step[px][py][i]=step[ux][uy][d]+delta;
				if(px==ex && py==ey) ans=min(ans,step[px][py][i]);
			}
		}
	}
}

int main()
{
	cin>>n;
	for(int i=1;i<=n;i++) 
		for(int j=1;j<=n;j++)
		{
			char ch;
			cin>>ch;
			if(ch=='x') map[i][j]=1;
			else if(ch=='A') sx=i,sy=j;
			else if(ch=='B') ex=i,ey=j;
		}
	memset(step,25,sizeof(step));
	for(int i=0;i<4;i++) step[sx][sy][i]=0;
	for(int i=0;i<4;i++) q[++tail][0]=sx,q[tail][1]=sy,q[tail][2]=i;
	bfs();
	cout<<ans<<endl;
	return 0;
}
