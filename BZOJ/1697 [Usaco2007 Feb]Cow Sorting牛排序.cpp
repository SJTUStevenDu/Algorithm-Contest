/*
DATE : 2013-2-6 
RATING : 3
TAG : Math
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

const int MAXN = 10000 + 5;
const long long INF = 100000000000LL;

struct Node
{
	int num;
	long long data;
} a[MAXN];

int n;
long long minv=INF,ans,sum;
bool vis[MAXN];

bool cmp(Node a,Node b)
{
	return a.data<b.data;
}

int main()
{
	scanf("%d",&n);
	for(int i=1;i<=n;i++)
	{
		scanf("%lld",&a[i].data);
		a[i].num=i;
		minv=min(minv,a[i].data);
	}
	sort(a+1,a+1+n,cmp);
	for(int i=1;i<=n;i++) if(!vis[i])
	{
		sum=0;
		long long minc=INF;
		int j=i,t=0;
		while(!vis[j])
		{
			vis[j]=1;t++;
			sum+=a[j].data;
			minc=min(minc,a[j].data);
			j=a[j].num;
		}
		ans+=sum;
		ans+=min(minc*(t-2),minc+minv*(t+1));
	}
	printf("%lld\n",ans);
	return 0;
}
