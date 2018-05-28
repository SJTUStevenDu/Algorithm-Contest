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
#include <map>

//Orz WJMZBMR && sevenkplus

using namespace std;

const int MAXN = 5002;

int f[MAXN][MAXN],n,R,ans;

int main()
{
	scanf("%d",&n);
	scanf("%d",&R);
	while(n--)
	{
		int x,y,d;
		scanf("%d%d%d",&x,&y,&d);
		++x;++y;
		f[x][y]+=d;
	}
	for(int i=1;i<MAXN;i++)
		for(int j=1;j<MAXN;j++) f[i][j]=f[i-1][j]+f[i][j-1]-f[i-1][j-1]+f[i][j];
	for(int i=0;i+R<MAXN;i++) 
		for(int j=0;j+R<MAXN;j++) 
			if(f[i+R][j+R]+f[i][j]-f[i+R][j]-f[i][j+R]>ans) ans=f[i+R][j+R]+f[i][j]-f[i+R][j]-f[i][j+R];
	printf("%d\n",ans);
	
	return 0;
}
