#include <iostream>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <cmath>
#include <algorithm>
#include <fstream>

using namespace std;

const int MAXN = 18*9 + 10;
const int MAXS = 18 + 2;

long long dp[2][MAXS][MAXN][MAXN];
int vis[2][MAXS][MAXN][MAXN];
int a[MAXS],cur,idx;

long long calc(bool les,int dep,int sum,int rem)
{
	if(dep==0) return (sum==0 && rem==0);
	if(vis[les][dep][sum][rem]==idx) return dp[les][dep][sum][rem];
	vis[les][dep][sum][rem]=idx;
	dp[les][dep][sum][rem]=0;
	int ed;
	long long re=0;
	if(les) ed=9;else ed=a[dep];
	ed=min(ed,sum);
	for(int i=max(sum-9*(dep-1),0);i<=ed;i++)
		re+=calc(les || i<a[dep],dep-1,sum-i,(rem*10+i)%cur);
	return dp[les][dep][sum][rem]=re;
}

long long Solve(long long x)
{
	memset(a,0,sizeof(a));
	while(x)
	{
		a[++a[0]]=x%10;
		x/=10;
	}
	long long res=0;
	for(cur=1;cur<=a[0]*9;cur++)
	{
		++idx;
		res+=calc(0,a[0],cur,0);
	}
	return res;
}

int main()
{
	long long x,y;
	scanf("%lld%lld",&x,&y);
	printf("%lld\n",Solve(y)-Solve(x-1));
	
	
	return 0;
}
