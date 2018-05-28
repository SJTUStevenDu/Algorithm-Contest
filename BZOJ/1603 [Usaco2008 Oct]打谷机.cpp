/*
DATE : 2012-11-30 
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
#include <iomanip>
#include <fstream>
#include <string>

//Orz WJMZBMR && sevenkplus

using namespace std;

const int MAXN = 1000 + 5;
int n;
int dir[MAXN],map[MAXN][MAXN];
bool vis[MAXN];

void dfs(int p)
{
	for(int i=1;i<=n;i++) if(map[p][i] && !vis[i])
	{
		if(map[p][i]==2) dir[i]=1^dir[p];
		else dir[i]=dir[p];
		vis[i]=0;
		dfs(i);
	}
}

int main()
{
	scanf("%d",&n);
	for(int i=1;i<n;i++) 
	{
		int a,b,c;
		scanf("%d%d%d",&a,&b,&c);
		map[a][b]=map[a][b]=c+1;
	}
	dir[1]=0;vis[1]=1;
	dfs(1);
	printf("%d\n",dir[n]);
	
	return 0;
}
