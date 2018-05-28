#include <iostream>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <algorithm>

using namespace std;

const int MAXN = 700 + 5;
const int gx[8]={1,0,-1,0,1,1,-1,-1};
const int gy[8]={0,1,0,-1,-1,1,1,-1};

struct Node
{
	int x,y,h;
} a[MAXN*MAXN];


int map[MAXN][MAXN];
int col[MAXN][MAXN];
int n,m,color,cnt;

bool cmp(Node a,Node b)
{
	return a.h>b.h;
}

void dfs(int x,int y)
{
	col[x][y]=color;
	for(int i=0;i<8;i++) 
	{
		int px=x+gx[i];
		int py=y+gy[i];
		if(px>0 && px<=n && py>0 && py<=m && !col[px][py] && map[x][y]>=map[px][py]) dfs(px,py);
	}
}

int main()
{
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++) 
		for(int j=1;j<=m;j++) scanf("%d",&map[i][j]);
	for(int i=1;i<=n;i++)
		for(int j=1;j<=m;j++) 
		{
			a[++cnt].x=i;a[cnt].y=j;a[cnt].h=map[i][j];
		}
	sort(a+1,a+1+cnt,cmp);
//	for(int i=1;i<=cnt;i++) cout<<a[i].x<<' '<<a[i].y<<' '<<a[i].h<<endl;
	for(int i=1;i<=cnt;i++) 
	if(!col[a[i].x][a[i].y]) 
		{
			color++;
			dfs(a[i].x,a[i].y);
		}
	printf("%d\n",color);
/*	for(int i=1;i<=n;i++) 
	{
		for(int j=1;j<=m;j++) cout<<col[i][j]<<' ';
		cout<<endl;
	}*/
	return 0;
}

