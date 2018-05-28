/*
DATE : 2013-2-22 
RATING : 3
TAG : ÕÛ°ëËÑË÷ 
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

const int MAXN = 40;

long long Light[MAXN];
int n,m;
int Pow[MAXN];
map <long long,int> HASH;
long long ans;

void dfs1(int p,long long st,int step)
{
	if(p>m)
	{
		if(HASH.count(st)==0 || HASH[st]>step) HASH[st]=step;
		return;
	}
	dfs1(p+1,st,step);
	dfs1(p+1,st^Light[p],step+1);
}

void dfs2(int p,long long st,int step)
{
	if(p>n)
	{
		st^=Pow[n]-1;
		if(HASH.count(st)!=0 && HASH[st]+step<ans) ans=HASH[st]+step;
		return;
	}
	dfs2(p+1,st,step);
	dfs2(p+1,st^Light[p],step+1);
}

int main()
{
	scanf("%d%d",&n,&m);
	Pow[0]=1;
	for(int i=1;i<=n;i++) Pow[i]=Pow[i-1]*2;
	while(m--)
	{
		int a,b;
		scanf("%d%d",&a,&b);
		Light[a]|=Pow[b-1];
		Light[b]|=Pow[a-1];
	}
	if(n==1)
	{
		printf("1\n");
		return 0;
	}
	else m=n/2;
	ans=10000000;
	for(int i=1;i<=n;i++) Light[i]|=Pow[i-1];
	dfs1(1,0,0);
	dfs2(m+1,0,0);
	printf("%lld\n",ans);
	
	return 0;
}
