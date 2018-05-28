/*
DATE : 2012-12-3
RATING : 1
TAG : DFS
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

const int gx[4]={0,1,0,-1};
const int gy[4]={1,0,-1,0};

long long f[105][105][20],n,m,t,r1,c1,r2,c2;
char map[105][105];

long long dfs(long long x,long long y,long long t)
{
	long long sum=0;
	if(t==0) 
	{
		if(x==r1 && y==c1) return 1;
		else return 0; 
	}
	for(int i=0;i<4;i++) 
	{
		long long px=x+gx[i],py=y+gy[i];
		if(px>0 && px<=n && py>0 && py<=m && map[px][py]!='*')
		{
			if(f[px][py][t-1]==-1) f[px][py][t-1]=dfs(px,py,t-1);
			sum+=f[px][py][t-1];
		}
	}
	return sum;
}

int main()
{
	cin>>n>>m>>t;
	for(int i=1;i<=n;i++) 
		for(int j=1;j<=m;j++) cin>>map[i][j];
	for(int i=1;i<=n;i++) 
		for(int j=1;j<=m;j++) 
			for(int k=0;k<=t;k++) f[i][j][k]=-1;
	cin>>r1>>c1>>r2>>c2;
	cout<<dfs(r2,c2,t)<<endl;
	return 0;
}
