/*
DATE : 2013-3-8 
RATING : 3
TAG : DP + –±¬ ”≈ªØ 
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
#include <queue>

//Orz WJMZBMR && sevenkplus

using namespace std;

const int MAXN = 50000 + 10;

struct Point
{
	long long x;long long y;
} P[MAXN];

bool cmp(Point A,Point B)
{
	return A.y<B.y || (A.y==B.y && A.x<B.x);
}

long long dp[MAXN];
int n;
int q[MAXN],head,tail;

int main()
{
	scanf("%d",&n);
	for(int i=1;i<=n;i++)
	{
		scanf("%lld%lld",&P[i].x,&P[i].y);
	}
	sort(P+1,P+1+n,cmp);
	tail=1;
	for(int i=2;i<=n;i++)
	{
		while(tail>0 && P[i].x>=P[tail].x) tail--;
		P[++tail]=P[i];
	}
	n=tail;
	head=tail=0;
	for(int i=1;i<=n;i++)
	{
		while(head<tail && P[i].y*(P[q[head]+1].x-P[q[head+1]+1].x)>dp[q[head+1]]-dp[q[head]]) head++;
		dp[i]=dp[q[head]]+P[i].y*P[q[head]+1].x;
		while(head<tail && (dp[i]-dp[q[tail-1]])*(P[q[tail]+1].x-P[i+1].x)>=(dp[i]-dp[q[tail]])*(P[q[tail-1]+1].x-P[i+1].x)) tail--;
		q[++tail]=i;
	}
	printf("%lld\n",dp[n]);
	
	return 0;
}
