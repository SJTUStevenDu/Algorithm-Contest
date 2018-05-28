/*
DATE : 2013-8-9 
RATING : 2
TAG : Math
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

const int MAXN = 100000 + 10;

int st[MAXN],pre[MAXN],Pow[MAXN];
int n;
long long T;

int main()
{
	scanf("%d",&n);
	scanf("%lld",&T);
	for(int i=1;i<=n;i++) scanf("%d",&st[i]),st[i]--;
	Pow[0]=1;	
	for(int i=1;i<=70;i++) Pow[i]=(Pow[i-1]*2)%n;
	for(int i=0;i<=70;i++)
	{
		if((1LL<<i)>(T>>1)) break;
		if((T>>1)&(1LL<<i))
		{
			memcpy(pre,st,sizeof(st));
			memset(st,0,sizeof(st));
			for(int j=1;j<=n;j++)
				st[j]=(pre[(j+Pow[i]-1)%n+1]^pre[(j-Pow[i]+n-1)%n+1]);
		}
	}
	st[n+1]=st[1];
	for(int i=1;i<n;i++)
	{
		if(T&1) printf("0 %d ",(st[i]^st[i+1])+1);
		else printf("%d 0 ",st[i]+1);
	}
	if(T&1) printf("0 %d\n",(st[n]^st[n+1])+1);
	else printf("%d 0\n",st[n]+1);
	
	return 0;
}
