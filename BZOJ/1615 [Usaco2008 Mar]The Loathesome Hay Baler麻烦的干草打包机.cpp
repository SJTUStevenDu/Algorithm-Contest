/*
DATE : 2012-12-3 
RATING : 1
TAG : DFS
*/

#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <cstdlib>
#include <iomanip>
#include <cmath>
#include <fstream>
#include <string>
#include <vector>

//Orz WJMZBMR && sevenkplus

using namespace std;

const int MAXN = 1050 + 5;
int x[MAXN],y[MAXN],r[MAXN],n,a[MAXN],xx,yy,pos;
bool map[MAXN][MAXN],ff=0,vis[MAXN];
double s[MAXN];

bool check(int i,int j)
{
	if((x[i]-x[j])*(x[i]-x[j])+(y[i]-y[j])*(y[i]-y[j])==(r[i]+r[j])*(r[i]+r[j])) return true;
	else return false;
}

void dfs(int deep)
{
	if(ff) return;
	if(x[a[deep-1]]==0 && y[a[deep-1]]==0)
	{
		ff=1;
		s[deep-1]=-10000;
		for(int i=deep-2;i>=0;i--) s[i]=-s[i+1]*r[a[i+1]]/r[a[i]];
		double ans=0;
		for(int i=deep-1;i>=0;i--) ans+=fabs(s[i]);
		long long k=(long long)ans;
		printf("%lld\n",k);
	}
	for(int i=1;i<=n;i++) if(!vis[i] && map[a[deep-1]][i])
	{
		vis[i]=1;
		a[deep]=i;
		dfs(deep+1);
		vis[i]=0;
	}
}

int main()
{
	scanf("%d%d%d",&n,&xx,&yy);
	for(int i=1;i<=n;i++) 
	{
		scanf("%d%d%d",&x[i],&y[i],&r[i]);
		if(x[i]==xx && y[i]==yy) pos=i;
	}
	for(int i=1;i<=n;i++) 
	{
		for(int j=1;j<i;j++) if(check(i,j)) map[i][j]=map[j][i]=1;
	}
	vis[pos]=1;a[0]=pos;
	dfs(1);
	
	return 0;
}
