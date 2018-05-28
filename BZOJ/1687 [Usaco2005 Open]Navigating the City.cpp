/*
DATE : 2012-12-16 
RATING : 3
TAG : BFS
*/

#include <iostream>
#include <cstdio>
#include <cstring>
#include <string>
#include <cstdlib>
#include <vector>
#include <algorithm>

using namespace std;

const int MAXN=45;
const int MAXV=1605;
int n,m;
bool map[MAXV][MAXV];
char tmp[MAXN<<1][MAXN<<1];

inline int f(int i,int j)
{
	return (i-1)*m+j;
}

inline bool check(int x,int y)
{
	if (tmp[x][y]=='S'||tmp[x][y]=='E'||tmp[x][y]=='+') return true;
	return false;
}

void Init()
{
	scanf("%d%d",&n,&m);
	for (int i=1;i<=2*n-1;i++) scanf("%s",tmp[i]+1);
}

int sx,sy,ex,ey;

void Makegraph()
{
	for(int i=1;i<=n;i++)
		for(int j=1;j<=m;j++)
		{
			int dx=2*i-1;
			int dy=2*j-1;
			if(i!=1&&check(dx,dy)&&check(dx-2,dy)&&tmp[dx-1][dy]=='|') map[f(i,j)][f(i-1,j)]=true;
			if(i!=n&&check(dx,dy)&&check(dx+2,dy)&&tmp[dx+1][dy]=='|') map[f(i,j)][f(i+1,j)]=true;
			if(j!=1&&check(dx,dy)&&check(dx,dy-2)&&tmp[dx][dy-1]=='-') map[f(i,j)][f(i,j-1)]=true;
			if(j!=m&&check(dx,dy)&&check(dx,dy+2)&&tmp[dx][dy+1]=='-') map[f(i,j)][f(i,j+1)]=true;
			if(tmp[dx][dy]=='S') sx=i,sy=j;
			if(tmp[dx][dy]=='E') ex=i,ey=j;
		}
}

int dx[4]={0,0,1,-1};
int dy[4]={1,-1,0,0};
bool vis[MAXN][MAXN];
int qu[MAXV][3];
int ans[MAXV][2];
int ansn;

void Solve()
{
	int head=0,tail=1;
	qu[0][0]=sx;
	qu[0][1]=sy;
	qu[0][2]=-1;
	vis[sx][sy]=true;
	bool found=false;
	int end=0;
	while(head!=tail&&!found)
	{
		int tx=qu[head][0];
		int ty=qu[head][1];
		int tf=head++;
		for(int i=0;i<4;i++)
		{
			int nowx=tx-dx[i];
			int nowy=ty-dy[i];
			if(nowx>=1&&nowx<=n&&nowy>=1&&nowy<=m&&!vis[nowx][nowy]&&map[f(tx,ty)][f(nowx,nowy)])
			{
				vis[nowx][nowy]=true;
				qu[tail][0]=nowx;
				qu[tail][1]=nowy;
				qu[tail][2]=tf;
				if(nowx==ex&&nowy==ey)
				{
					end=tail;
					found=true;
					break;
				}
				tail++;
			}
		}
	}
	while(end!=-1)
	{
		ansn++;
		ans[ansn][0]=qu[end][0];
		ans[ansn][1]=qu[end][1];
		end=qu[end][2];
	}
	int p=0;
	string pr="";
	for(int i=ansn-1;i;i--)
	{
		if (ans[i][0]==ans[i+1][0]&&ans[i][1]==ans[i+1][1]+1) pr[++p]='E';
		if (ans[i][0]==ans[i+1][0]&&ans[i][1]==ans[i+1][1]-1) pr[++p]='W';
		if (ans[i][0]==ans[i+1][0]+1&&ans[i][1]==ans[i+1][1]) pr[++p]='S';
		if (ans[i][0]==ans[i+1][0]-1&&ans[i][1]==ans[i+1][1]) pr[++p]='N';
	}
	int cnt=1;
	printf("%c",pr[1]);
	for(int i=2;i<ansn;i++)
	{
		if(pr[i]==pr[i-1]) cnt++;
		else
		{
			printf(" %d\n%c",cnt,pr[i]);
			cnt=1;
		}
	}
	printf(" %d\n",cnt);
}

int main()
{
	Init();
	Makegraph();
	Solve();
	return 0;
}
