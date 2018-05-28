/*
DATE : 2013-5-21 
RATING : 2
TAG : Enum
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

const int MAXN = 100 + 10;

int n,m,ans;
int map[MAXN][MAXN],maptmp[MAXN][MAXN],cnt;

int check(int l,int r)
{
	memcpy(maptmp,map,sizeof(map));
	int sum=0;
	for(int i=1;i<=n-l+1;i++)
		for(int j=1;j<=m-r+1;j++) 
		{
			int delta=maptmp[i][j];
			sum+=delta;
			if(delta==0) continue;
			for(int i1=i;i1<=i+l-1;i1++)
				for(int j1=j;j1<=j+r-1;j1++)
					if(maptmp[i1][j1]<delta) return 0;
					else maptmp[i1][j1]-=delta;
		}
	return sum;
}

int main()
{
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++) 
		for(int j=1;j<=m;j++) scanf("%d",&map[i][j]),cnt+=map[i][j];
	for(int l=1;l<=n;l++) 
		for(int r=1;r<=m;r++)
		{
			if(l*r<=ans) continue;
			if(cnt%(l*r)) continue;
			if(check(l,r)*l*r==cnt) ans=l*r;
		}
	printf("%d\n",cnt/ans);
	
	return 0;
}
