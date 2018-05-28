/*
DATE : 2013-3-25 
RATING : 2
TAG : Greedy
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

const int MAXN = 150000 + 10;

struct Construction
{
	long long last,en;
} a[MAXN];

bool cmp(Construction A,Construction B)
{
	return A.en<B.en || (A.en==B.en && A.last<B.last);
}

int n,ans;
long long now;
priority_queue <long long> Q;

int main()
{
	scanf("%d",&n);
	for(int i=1;i<=n;i++)  scanf("%lld%lld",&a[i].last,&a[i].en);
	sort(a+1,a+1+n,cmp);
	for(int i=1;i<=n;i++)
	{
		if(a[i].en>=now+a[i].last)
		{
			++ans;
			Q.push(a[i].last);
			now+=a[i].last;
		}
		else if(Q.top()>a[i].last)
		{
			now-=Q.top()-a[i].last;
			Q.pop();
			Q.push(a[i].last);
		}
	}
	printf("%d\n",ans);
	
	return 0;
}
