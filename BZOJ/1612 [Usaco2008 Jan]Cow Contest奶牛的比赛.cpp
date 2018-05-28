/*
DATE : 2012-12-2 
RATING : 1
TAG : FLOYD
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

bool map[105][105];
int n,ans,t,m;

int main()
{
	scanf("%d%d",&n,&m);
	while(m--)
	{
		int a,b;
		scanf("%d%d",&a,&b);
		map[a][b]=1;
	}
	for(int k=1;k<=n;k++)
		for(int i=1;i<=n;i++) 
			for(int j=1;j<=n;j++) map[i][j]=map[i][j] || (map[i][k] && map[k][j]);
	for(int i=1;i<=n;i++)
	{
		t = 0;
		for(int j=1;j<=n;j++) if((map[i][j] || map[j][i]) && i!=j) t++;
		if( t == n-1) ans++;
	}
	printf("%d\n",ans);
	
	return 0;
}
