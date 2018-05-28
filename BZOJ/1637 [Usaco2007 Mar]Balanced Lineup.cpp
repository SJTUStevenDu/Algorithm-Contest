/*
DATE : 2012-12-5 
RATING : 1
TAG : 
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

//Orz WJMZBMR && sevenkplus

using namespace std;

const int MAXN  = 50000 + 5;

struct Node
{
	int c,p;
} a[MAXN];

int n,sum[MAXN],last[MAXN<<1],ans;

bool cmp(Node a,Node b)
{
	return a.p<b.p;
}

int main()
{
	scanf("%d",&n);
	for(int i=1;i<=n;i++) 
	{
		scanf("%d%d",&a[i].c,&a[i].p);
		if(a[i].c==0) a[i].c=-1;
	}
	memset(last,-1,sizeof(last));
	sort(a+1,a+1+n,cmp);
	for(int i=1;i<=n;i++) sum[i]=sum[i-1]+a[i].c;
	for(int i=1;i<=n;i++)
	{
		if(last[sum[i]+MAXN]==-1) last[sum[i]+MAXN]=i;
		else ans=max(ans,a[i].p-a[last[sum[i]+MAXN]+1].p);
	}
	printf("%d\n",ans);
	
	return 0;
}
