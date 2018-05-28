/*
DATE : 2012-12-22 
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

const int MAXN = 100 + 5;

struct Node
{
	int cost,num;
} a[MAXN];

bool cmp(Node a,Node b)
{
	return a.cost<b.cost;
}

int sum,e,n,ans;

int main()
{
	scanf("%d%d%d",&sum,&e,&n);
	for(int i=1;i<=n;i++)
	{
		int aa,b,c;
		scanf("%d%d%d",&aa,&b,&c);
		a[i].cost=(e-aa+c);
		a[i].num=b;
	}
	sort(a+1,a+1+n,cmp);
	int i=1;
	while(sum>0)
	{
		int d=min(sum,a[i].num);
		sum-=d;
		ans+=(d*a[i].cost);
		i++;
	}
	printf("%d\n",ans);
	
	return 0;
}
