/*
DATE : 2013-5-16 
RATING : 3
TAG : DFS
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
#include <map>

//Orz WJMZBMR && sevenkplus

using namespace std;

const int MAXN = 3000 + 10;

bool flag[MAXN];
long long luck[MAXN];
int cnt;
long long a,b,Limit,res,ans;

inline long long gcd(long long m,long long n)
{
	long long tmp;
	while(n)
	{
		tmp=n;
		n=m%n;
		m=tmp;
	}
	return m;
}

void ddfs(long long num)
{
	if(num>Limit) return;
	luck[++cnt]=num;
	ddfs(num*10+6);
	ddfs(num*10+8);
}

void dfs(int step,long long lcm,int tot)
{
	if(step>cnt)
	{
		if(tot)
		{
			long long tmp=Limit/lcm;
			if(tot&1) res+=tmp;
			else res-=tmp;
		}
		return;
	}
	long long tmp=gcd(lcm,luck[step]);
	if((double)lcm/tmp>(double)Limit/luck[step])return;
	tmp=lcm*luck[step]/tmp;
	for(int i=step;i<=cnt;i++) dfs(i+1,tmp,tot+1);
}

long long Query(long long x)
{
	if(x<6) return 0;
	res=0;
	cnt=0;Limit=x;
	ddfs(6);ddfs(8);
	sort(luck+1,luck+1+cnt);
	for(int i=1;i<=cnt;i++)
		for(int j=1;j<i;j++) if(luck[i]%luck[j]==0) {flag[i]=1;break;}
	int ttttmp=cnt;
	cnt=0;
	for(int i=1;i<=ttttmp;i++) if(!flag[i]) luck[++cnt]=luck[i];
	sort(luck+1,luck+1+cnt);
	for(int i=1;i<=cnt/2;i++) swap(luck[i],luck[cnt-i+1]);
	for(int i=1;i<=cnt;i++) dfs(i,1,0);
	return res;
}

int main()
{
	scanf("%lld%lld",&a,&b);
	printf("%lld\n",Query(b)-Query(a-1));
	
	return 0;
}
