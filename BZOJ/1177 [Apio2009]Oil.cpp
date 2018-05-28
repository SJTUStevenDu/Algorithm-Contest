/*
DATE : 2013-4-29
RATING : 2
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

const int MAXN = 2000 + 10;

int map[MAXN][MAXN],sum[MAXN][MAXN],K;
int X[MAXN],Y[MAXN],LL[MAXN][MAXN],LR[MAXN][MAXN],RL[MAXN][MAXN],RR[MAXN][MAXN];
int n,m,ans;

int main()
{
	scanf("%d%d",&n,&m);
	scanf("%d",&K);
	for(int i=1;i<=n;++i)
		for(int j=1;j<=m;++j) scanf("%d",&map[i][j]);
	for(int i=1;i<=n;++i)
		for(int j=1;j<=m;++j) sum[i][j]=sum[i-1][j]+sum[i][j-1]-sum[i-1][j-1]+map[i][j];
	K--;
	n-=K;m-=K;
	for(int i=1;i<=n;++i)
		for(int j=1;j<=m;++j) map[i][j]=sum[i+K][j+K]-sum[i+K][j-1]-sum[i-1][j+K]+sum[i-1][j-1];
	for(int i=1;i<=n;++i)
		for(int j=1;j<=m;++j)
			LL[i][j]=max(map[i][j],max(LL[i-1][j],LL[i][j-1]));
	for(int i=n;i;--i)
		for(int j=1;j<=m;++j)
			RL[i][j]=max(map[i][j],max(RL[i+1][j],RL[i][j-1]));
	for(int i=1;i<=n;++i)
		for(int j=m;j;--j)
			LR[i][j]=max(map[i][j],max(LR[i-1][j],LR[i][j+1]));
	for(int i=n;i;--i)
		for(int j=m;j;--j)
			RR[i][j]=max(map[i][j],max(RR[i+1][j],RR[i][j+1]));
	for(int i=1;i<=n;++i)
		for(int j=1;j<=m;++j) X[i]=max(X[i],map[i][j]);
	for(int j=1;j<=m;j++)
		for(int i=1;i<=n;++i) Y[j]=max(Y[j],map[i][j]);
	for(int i=n-K;i;--i)
		for(int j=m-K;j;--j)
		{
			ans=max(ans,LL[i][j]+LR[i][j+K+1]+RR[i+K+1][1]);
			ans=max(ans,LL[i][j]+RL[i+K+1][j]+RR[1][j+K+1]);
		}
	for(int i=K+1;i<=n;++i)
		for(int j=K+1;j<=m;++j)
		{
			ans=max(ans,RR[i][j]+LR[i-K-1][j]+LL[n][j-K-1]);
			ans=max(ans,RR[i][j]+RL[i][j-K-1]+LL[i-K-1][m]);
		}
	for(int i=1,tmp=X[i];i<=n-K;++i,tmp=max(tmp,X[i])) 
		for(int j=i+K+1,cur=X[j];j<=n-K;++j,cur=max(cur,X[j]))
			ans=max(ans,tmp+cur+RR[j+K+1][1]);
	for(int i=1,tmp=Y[i];i<=m-K;++i,tmp=max(tmp,Y[i]))
		for(int j=i+K+1,cur=Y[j];j<=m-K;++j,cur=max(cur,Y[j]))
			ans=max(ans,tmp+cur+RR[1][j+K+1]);
	printf("%d\n",ans);
	
	return 0;
}
