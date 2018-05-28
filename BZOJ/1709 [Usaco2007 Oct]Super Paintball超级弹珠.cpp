/*
DATE : 2013-1-24 
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

const int MAXN = 100 + 5;

int n,m,ans;
int num[MAXN][MAXN],cross[MAXN],line[MAXN],Left[MAXN*2],Right[MAXN*2];

int main()
{
	scanf("%d%d",&n,&m);
	for(int a,b,i=1;i<=m;i++) 
	{
		scanf("%d%d",&a,&b);	
		line[a]++;
		cross[b]++;
		Left[a+b]++;
		Right[n+a-b]++;
		num[a][b]++;
	}
	for(int i=1;i<=n;i++)
	{
		for(int j=1;j<=n;j++)
			if(line[i]+cross[j]+Left[i+j]+Right[n+i-j]-num[i][j]*3==m) ans++;
	}
	printf("%d\n",ans);
	return 0;
}
