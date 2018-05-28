#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cmath>
#include <string>
#include <fstream>
#include <algorithm>

using namespace std;

//By StevenKlose

const int MAXN = 60;
const double eps=1e-6;

int n,m;
int a[MAXN];
double dp[MAXN][MAXN];

double f(int i,int j)
{
	if(i==1) return 1.0;
	if(dp[i][j]>-eps) return dp[i][j];
	double res=0.0;
	int l,newz,newj;
	for(int x=1;x<=m;x++)
	{
		l=(a[x]-1)%i+1;
		if(l==j) continue;
		newz=(l+1)%i;
		if(newz==0) newz=i;
		newj=(j-newz+i+1)%i;
		newj%=(i-1);
		if(newj==0) newj=i-1;
		res+=(1.0/(double)m)*f(i-1,newj);
	}
	return dp[i][j]=res;
}

int main()
{
	scanf("%d%d",&n,&m);
	for(int i=1;i<=m;i++) scanf("%d",&a[i]);
	for(int i=1;i<=n;i++) 
		for(int j=1;j<=n;j++) dp[i][j]=-1.0;
	for(int i=1;i<=n;i++)
	{
		printf("%.2lf",f(n,i)*100);
		printf("%%");
		if(i==n) printf("\n");
		else printf(" ");
	}
	return 0;
}
