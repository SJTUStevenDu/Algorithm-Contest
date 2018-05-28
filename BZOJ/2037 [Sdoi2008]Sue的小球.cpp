#include <iostream>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <cmath>
#include <algorithm>
#include <fstream>

using namespace std;

const int MAXN = 1000 + 10;

struct Node
{
	int x,y,v;
} p[MAXN];

int w[MAXN][MAXN],f1[MAXN][MAXN],f2[MAXN][MAXN];
int n,x0,sum[MAXN];
double ans;

int dfs1(int i,int j);
int dfs2(int i,int j);

bool cmp(Node A,Node B)
{
	return A.x<B.x;
}

int dfs1(int i,int j)
{
	if(~f1[i][j]) return f1[i][j];
	return f1[i][j]=p[i].y+max(dfs1(i+1,j)-(p[i+1].x-p[i].x)*w[i+1][j],dfs2(i+1,j)-(p[j].x-p[i].x)*w[i+1][j]);
}

int dfs2(int i,int j)
{
	if(~f2[i][j]) return f2[i][j];
	return f2[i][j]=p[j].y+max(dfs1(i,j-1)-(p[j].x-p[i].x)*w[i][j-1],dfs2(i,j-1)-(p[j].x-p[j-1].x)*w[i][j-1]);
}

int main()
{
	scanf("%d%d",&n,&x0);
	for(int i=1;i<=n;i++) scanf("%d",&p[i].x);
	for(int i=1;i<=n;i++) scanf("%d",&p[i].y);
	for(int i=1;i<=n;i++) scanf("%d",&p[i].v);
	memset(f1,-1,sizeof(f1));memset(f2,-1,sizeof(f2));
	sort(p+1,p+1+n,cmp);
	for(int i=1;i<=n;i++) sum[i]=sum[i-1]+p[i].v;
	for(int i=1;i<=n;i++)
		for(int j=i;j<=n;j++) w[i][j]=sum[n]-(sum[j]-sum[i-1]);
	for(int i=1;i<=n;i++) f1[i][i]=f2[i][i]=p[i].y-sum[n]*abs(p[i].x-x0);
	ans=max(dfs1(1,n),dfs2(1,n));
	ans/=1000;
	printf("%.3lf\n",ans);
	
	return 0;
}
