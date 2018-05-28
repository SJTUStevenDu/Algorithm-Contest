#include <iostream>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <cmath>
#include <algorithm>
#include <fstream>

using namespace std;

const int MAXN = 100 + 10;
const int INF = 0x7FFFFFFF>>2;

long long f[MAXN][MAXN],g[MAXN][MAXN];
int n,m;
double ans[MAXN];

int main()
{
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++)
		for(int j=1;j<=n;j++) f[i][j]=INF;
	for(int a,b,c,i=1;i<=m;i++) 
	{
		scanf("%d%d%d",&a,&b,&c);
		f[a][b]=f[b][a]=c;
		g[a][b]=g[b][a]=1;
	}
	for(int k=1;k<=n;k++)
		for(int i=1;i<=n;i++) if(i!=k)
			for(int j=1;j<=n;j++) if(j!=k && i!=j)
			{
				if(f[i][j]>f[i][k]+f[k][j]) f[i][j]=f[i][k]+f[k][j],g[i][j]=g[i][k]*g[k][j];
				else if(f[i][j]==f[i][k]+f[k][j]) g[i][j]+=g[i][k]*g[k][j];
			}
	for(int k=1;k<=n;k++) 
		for(int i=1;i<=n;i++) if(i!=k)
			for(int j=1;j<=n;j++) if(j!=k && i!=j && f[i][j]==f[i][k]+f[k][j]) ans[k]+=(double)(g[i][k]*g[k][j])/(double)g[i][j];
	for(int i=1;i<=n;i++) printf("%.3lf\n",ans[i]);
	
	return 0;
}
