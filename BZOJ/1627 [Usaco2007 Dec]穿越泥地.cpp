/*
DATE : 2012-11-30 
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
#include <iomanip>
#include <fstream>
#include <string>

//Orz WJMZBMR && sevenkplus

using namespace std;

const int dir[4][2]={{0,1},{1,0},{-1,0},{0,-1}};
const int MAXN = 1000 + 5;
int step[MAXN][MAXN],n,x,y;
int q[MAXN*MAXN][2],head,tail;

int main()
{
	scanf("%d %d %d",&x,&y,&n);
	x+=501;y+=501;
	while(n--)
	{
		int a,b;
		scanf("%d%d",&a,&b);
		a+=501;b+=501;
		step[a][b]=-1;
	}
	for(int i=1;i<MAXN;i++) step[i][0]=step[0][i]=step[MAXN-1][i]=step[i][MAXN-1]=-1;
	step[501][501]=1;
	q[++tail][0]=501;q[tail][1]=501;
	while(head<tail)
	{
		int px=q[++head][0],py=q[head][1];
		for(int i=0;i<4;i++) 
		{
			int ux=px+dir[i][0];
			int uy=py+dir[i][1];
			if(ux==x && uy==y) 
			{
				printf("%d\n",step[px][py]);
				return 0;
			}
			if(step[ux][uy]==0) step[ux][uy]=step[px][py]+1,q[++tail][0]=ux,q[tail][1]=uy;
		}
	}
	
	
	return 0;
}
