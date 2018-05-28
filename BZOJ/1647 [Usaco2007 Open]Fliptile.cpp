/*
DATE : 2012-12-9 
RATING : 1
TAG : 
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

const int MAXN = 20;
const int gx[5]={1,0,-1,0,0};
const int gy[5]={0,1,0,-1,0};

int n,m,map[MAXN][MAXN],maptmp[MAXN][MAXN],flip[MAXN][MAXN],ans[MAXN][MAXN],anscnt=0x7FFFFFFF;

void fliptail(int x,int y)
{
	for(int i=0;i<5;i++)
	{
		int px=gx[i]+x,py=gy[i]+y;
		if(px>0 && px<=m && py>0 && py<=n) maptmp[px][py]^=1;
	}
	return;
}

void Solve()
{
	
	for(int i=1;i<=n;i++) if(flip[1][i]) fliptail(1,i);
	for(int i=2;i<=m;i++)
	{
		for(int j=1;j<=n;j++) if(maptmp[i-1][j]) flip[i][j]=1;
		for(int j=1;j<=n;j++) if(flip[i][j]) fliptail(i,j);
	}
	bool flag=1;
	for(int i=1;i<=n;i++) if(maptmp[m][i]) {flag=false;break;}
	if(flag) 
	{
		int cnt=0;
		for(int i=1;i<=m;i++)
			for(int j=1;j<=n;j++) if(flip[i][j]) cnt++;
		if(cnt<anscnt)
		{
			anscnt=cnt;
			memcpy(ans,flip,sizeof(flip));
		}
	}
}

int main()
{
	cin>>m>>n;
	for(int i=1;i<=m;i++) 
	{
		for(int j=1;j<=n;j++) cin>>map[i][j];
	}
	for(int i=0;i<(1<<n);i++) 
	{
		int k=i;
		memset(flip,0,sizeof(flip));
		for(int j=1;j<=n;j++) flip[1][j]=k&1,k=(k>>1);
		memcpy(maptmp,map,sizeof(map));
		Solve();
	}
	if(anscnt>100000000) cout<<"IMPOSSIBLE"<<endl;
	else for(int i=1;i<=m;i++) 
	{
		for(int j=1;j<n;j++) cout<<ans[i][j]<<" ";
		cout<<ans[i][n]<<endl;
	}
	
	return 0;
}
