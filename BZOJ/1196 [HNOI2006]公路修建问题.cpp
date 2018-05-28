/*
DATE : 2013-2-25 
RATING : 1
TAG : Binary
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

const int MAXN = 10000 + 10;
const int MAXM = 20000 + 10;

int n,m,K,father[MAXN];

struct Node 
{
	int from,to,c1,c2;
} e[MAXM];

int getfather(int x)
{
	if(father[x]==x) return x;
	else return father[x]=getfather(father[x]);
}
 
bool check(int x)
{
	int cnt=0;
	for(int i=1;i<=n;i++) father[i]=i;
	for(int i=1;i<m;i++)
		if(e[i].c1<=x) 
		{
			int a=e[i].from,b=e[i].to;
			if(getfather(a)!=getfather(b)) father[getfather(a)]=getfather(b),cnt++;
		}
	if(cnt<K) return false;
	for(int i=1;i<m;i++) 
		if(e[i].c2<=x)
		{
			int a=e[i].from,b=e[i].to;
			if(getfather(a)!=getfather(b)) father[getfather(a)]=getfather(b),cnt++;
		}
	if(cnt==n-1) return true;
	else return false;
}

int main()
{
	scanf("%d%d%d",&n,&K,&m);
	int l=1,r=30000;
	for(int i=1;i<m;i++) 
	{
		scanf("%d%d%d%d",&e[i].from,&e[i].to,&e[i].c1,&e[i].c2);
	}
	while(l<=r)
	{
		int mid=(l+r)>>1;
		if(check(mid)) r=mid-1;
		else l=mid+1;
	}
	printf("%d\n",l);
	
	return 0;
}
