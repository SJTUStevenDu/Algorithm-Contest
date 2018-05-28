/*
DATE : 2012-12-12 
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

int n,m;
short int map[5005][5005];
short int d1[5005],d2[5005];
int ans1[5005],ans2[5005],ans,a,b;

int main()
{
	scanf("%d%d",&n,&m);
	for(int i=1;i<=m;i++)
	{
		scanf("%d%d",&a,&b);
		if(a>b) swap(a,b);
		map[a][b]++;
		d1[b]++;d2[a]++;
	}
	for(int i=1;i<=n;i++)
	{
		if(!d1[i]) ans1[i]=1;
		if(!d2[i]) ans2[i]=1;
	}
	for(int i=1;i<=n;i++)
		for(int j=i+1;j<=n;j++) ans1[j]+=map[i][j]*ans1[i];
	for(int i=n;i;i--)
		for(int j=i-1;j;j--) ans2[j]+=map[j][i]*ans2[i];
	for (int i=1;i<=n;i++)
		for (int j=i+1;j<=n;j++)
			if (map[i][j]) ans=max(ans,ans1[i]*ans2[j]);
	printf("%d\n",ans);
	return 0;
}
