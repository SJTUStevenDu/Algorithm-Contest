/*
DATE : 2012-12-15 
RATING : 1
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

using namespace std;

int n,m,ans;

struct Node
{
	int p,c;
} a[30];

bool cmp(Node a,Node b)
{
	return a.p>b.p;
}

int main()
{
	cin>>n>>m;
	for(int i=1;i<=n;i++) cin>>a[i].p>>a[i].c;
	sort(a+1,a+1+n,cmp);
	bool flag=1;
	while(flag)
	{
		flag=0;
		int now=m;
		for(int i=1;i<=n;i++) while(now>0 && a[i].p<=now && a[i].c) a[i].c--,now-=a[i].p;
		if(now>0) for(int i=n;i;i--) while(now>0 && a[i].c) now-=a[i].p,a[i].c--;
		if(now<=0) ans++,flag=1;
	}
	cout<<ans<<endl;
	
	return 0;
}
