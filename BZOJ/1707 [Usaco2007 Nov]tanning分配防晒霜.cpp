/*
DATE : 2013-2-10 
RATING : 2
TAG : Greedy
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

const int MAXN = 2500 + 5;

struct Cow
{
	int mins,maxs;
} c[MAXN];

bool cmp1(Cow a,Cow b)
{
	return a.maxs<b.maxs;
}

struct SPF
{
	int num,data;
} s[MAXN];

bool cmp2(SPF a,SPF b)
{
	return a.data<b.data;
}

int n,m,ans;

int main()
{
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++) scanf("%d%d",&c[i].mins,&c[i].maxs);
	sort(c+1,c+1+n,cmp1);
	for(int i=1;i<=m;i++) scanf("%d%d",&s[i].data,&s[i].num);
	sort(s+1,s+1+m,cmp2);
	for(int i=1;i<=n;i++)
	{
		for(int j=1;j<=m;j++)
			if(s[j].data>=c[i].mins && s[j].data<=c[i].maxs && s[j].num)
			{
				ans++;
				s[j].num--;
				break;
			}
	}
	printf("%d\n",ans);
	
	return 0;
}
