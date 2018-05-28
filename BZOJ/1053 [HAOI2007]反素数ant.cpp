#include <iostream>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <cmath>
#include <algorithm>
#include <fstream>

using namespace std;

const int INF = 0x7FFFFFFF;
const int prime[11]={0,2,3,5,7,11,13,17,19,23,29};

long long n,best;
int maxx;

void dfs(int pos,int num,long long now,int t)
{
	if(num>maxx) best=INF,maxx=num;
	if(num==maxx) best=min(best,now);
	long long res=now;
	for(int i=1;i<=t;i++)
	{
		res*=prime[pos];
		if(res>n) break;
		dfs(pos+1,num*(t+1),res,i);
	}
}

int main()
{
	scanf("%lld",&n);
	dfs(1,1,1,20);
	printf("%lld\n",best);
	
	return 0;
}
