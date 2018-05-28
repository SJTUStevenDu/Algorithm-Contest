/*
DATE : 2012-12-5 
RATING : 1
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

//Orz WJMZBMR && sevenkplus

using namespace std;

const int MAXN = 50000 + 5;

struct Node
{
	int w,s,sum;
} a[MAXN];
int n,ans=-210000000,d;

bool cmp(Node a,Node b)
{
	return a.sum<b.sum;
}

int main()
{
	scanf("%d",&n);
	for(int i=1;i<=n;i++) scanf("%d%d",&a[i].w,&a[i].s);
	for(int i=1;i<=n;i++) a[i].sum=a[i].w+a[i].s;
	sort(a+1,a+1+n,cmp);
	for(int i=1;i<=n;i++) 
	{
		d+=a[i-1].w;
		ans=max(ans,d-a[i].s);
	}
	cout<<ans<<endl;
	
	return 0;
}
