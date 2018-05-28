/*
DATE : 2013-3-24 
RATING : 2
TAG : ??DP 
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
#include <map>
#include <vector>

//Orz WJMZBMR && sevenkplus

using namespace std;

const int MAXN = 15;
const int MAXM = 600;

int n,K;
long long dp[2][MAXM][MAXN*MAXN],ans;
int pre,now,num[MAXM],maxx;
bool able1[MAXM],able2[MAXM][MAXM];

void PreDo()
{
	int cnt;
	for(int i=0;i<=maxx;i++) if((i&(i>>1))==0) 
	{
		able1[i]=1;
		int tmp=i;
		cnt=0;
		for(;tmp;tmp>>=1) cnt+=(tmp&1);
		num[i]=cnt;
	}
	for(int i=0;i<=maxx;i++) if(able1[i])
		for(int j=0;j<=maxx;j++) if(able1[j])
			if(((i&j)==0) && ((i&(j>>1))==0) && ((j&(i>>1))==0)) able2[i][j]=1;
}

int main()
{
	scanf("%d%d",&n,&K);
	maxx=(1<<n)-1;
	PreDo();
	for(int i=0;i<=maxx;i++) if(able1[i]) dp[0][i][num[i]]=1;
	for(int i=2;i<=n;i++)
	{
		now=pre^1;
		memset(dp[now],0,sizeof(dp[now]));
		for(int j=0;j<=maxx;j++) if(able1[j])
		{
			for(int k=0;k<=maxx;k++) if(able1[k])
			{
				if(able2[j][k])
				{
					for(int l=num[j];l+num[k]<=K;++l) {dp[now][k][l+num[k]]+=dp[pre][j][l];}
				}
			}
		}
		pre=now;
	}
	for(int i=0;i<=maxx;i++) ans+=dp[now][i][K];
	printf("%lld\n",ans);
	
	return 0;
}
