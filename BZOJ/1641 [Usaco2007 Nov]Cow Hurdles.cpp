/*
DATE : 2012-12-6
RATING : 1
TAG : 
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

const int MAXN = 300 + 5;

int n,m,t,map[MAXN][MAXN],a,b;

int main()
{
	//freopen("1.txt","r",stdin);
	scanf("%d%d%d",&n,&m,&t);
	memset(map,25,sizeof(map));
	for(int i=1;i<=m;i++) 
	{
		int x,y,w;
		scanf("%d%d%d",&x,&y,&w);
		map[x][y]=w;
	}
	for(int i=1;i<=n;i++) map[i][i]=0;
	for(int k=1;k<=n;k++) 	
		for(int i=1;i<=n;i++) 
			for(int j=1;j<=n;j++) 
				map[i][j]=min(map[i][j],max(map[i][k],map[k][j]));
	while(t--)
	{
		scanf("%d%d",&a,&b);
		if(map[a][b]<400000000) printf("%d\n",map[a][b]);else printf("-1\n");
	}
	return 0;
}
