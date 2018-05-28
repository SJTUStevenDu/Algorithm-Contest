/*
DATE : 2013-2-17 
RATING : 3
TAG : DP
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

//Orz WJMZBMR && sevenkplus

using namespace std;

const int MAXN = 10000 + 5;
const int MAXK = 100 + 5;

int n,k;
int large[MAXN][MAXK],small[MAXN][MAXK];
int Original_ans,Blank_num,ans=0x7FFFFFFF;
int f[MAXN][MAXK];
int a[MAXN],pos[MAXN];

int main()
{
	scanf("%d%d",&n,&k);
	for(int i=1;i<=n;i++) scanf("%d",&a[i]);
	for(int i=2;i<=n;i++) 
	{
		for(int j=1;j<=k;j++) large[i][j]=large[i-1][j];
		if(a[i-1]!=-1) for(int j=1;j<a[i-1];j++) large[i][j]++;
	}
	for(int i=n-1;i;i--)
	{
		for(int j=1;j<=k;j++) small[i][j]=small[i+1][j];
		if(a[i+1]!=-1) for(int j=a[i+1]+1;j<=k;j++) small[i][j]++;
	}
	for(int i=1;i<=n;i++) 
		if(a[i]!=-1) Original_ans+=large[i][a[i]];
	memset(f,63,sizeof(f));
	for(int i=1;i<=n;i++) if(a[i]==-1) pos[++Blank_num]=i;
	for(int i=1;i<=k;i++) f[1][i]=large[pos[1]][i]+small[pos[1]][i];
	for(int i=2;i<=Blank_num;i++)
		for(int j=1;j<=k;j++)
			for(int w=1;w<=j;w++) f[i][j]=min(f[i][j],f[i-1][w]+large[pos[i]][j]+small[pos[i]][j]);
	for(int i=1;i<=k;i++) ans=min(ans,f[Blank_num][i]);
	if(ans>10000000) ans=0;
	printf("%d\n",ans+Original_ans);
	
	return 0;
}
