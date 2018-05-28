/*
DATE : 2013-5-20 
RATING : 2
TAG : DP
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

const int MAXN = 50;

char p[7][3];
int g[4][MAXN],n;
long long f[4][MAXN];
//g记录编号f记录步数 

int main()
{
	scanf("%d",&n);
	char ch=getchar();
	for(int i=1;i<=6;i++)
	{
		for(;ch!='A' && ch!='B' && ch!='C';ch=getchar());
		for(int j=0;j<3;j++) p[i][j]=ch,ch=getchar();
	}
	for(int i=1;i<=3;i++)
	{
		for(int j=1;j<=6;j++) 
		{
			if(p[j][0]==i-1+'A')
			{
				f[i][1]=1;
				g[i][1]=p[j][1]-'A'+1;
				break;
			}
		}
	}
	for(int i=2;i<=n;i++)
		for(int x=1;x<=3;x++)
		{
			int y=g[x][i-1];
			int z=6-x-y;
			f[x][i]=f[x][i-1]+1;
			if(g[y][i-1]==z)
			{
				f[x][i]+=f[y][i-1];
				g[x][i]=z;
			}
			else
			{
				f[x][i]+=f[y][i-1]+1+f[x][i-1];
				g[x][i]=y;
			}
		}
	printf("%lld\n",f[1][n]);
	
	return 0;
}
