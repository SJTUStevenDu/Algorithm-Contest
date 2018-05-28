/*
DATE : 2012-12-4 
RATING : 1
TAG : Floyd
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

const int MAXN = 100 + 5 ;
const int MAXM = 10000 + 5;

int n,m,a[MAXM],map[MAXN][MAXN],ans;

int main()
{
	cin>>n>>m;
	for(int i=1;i<=m;i++) cin>>a[i];
	memset(map,22,sizeof(map));
	for(int i=1;i<=n;i++) 
		for(int j=1;j<=n;j++) cin>>map[i][j];
	for(int k=1;k<=n;k++)
		for(int i=1;i<=n;i++)
			for(int j=1;j<=n;j++) map[i][j]=min(map[i][j],map[i][k]+map[k][j]);
	for(int i=1;i<m;i++) ans+=map[a[i]][a[i+1]];
	cout<<ans<<endl;
	
	return 0;
}
