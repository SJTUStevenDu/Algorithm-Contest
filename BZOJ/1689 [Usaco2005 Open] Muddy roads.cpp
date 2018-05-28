/*
DATE : 2012-12-16 
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

int n,ans,now,l;

struct Node
{
	int st,en;
} a[10005];

bool cmp(Node a,Node b)
{
	return a.st<b.st;
}

int main()
{
	cin>>n>>l;
	for(int i=1;i<=n;i++) cin>>a[i].st>>a[i].en;
	sort(a+1,a+1+n,cmp);
	for(int i=1;i<=n;i++)
	{
		if(now>=a[i].en) continue;
		if(now<a[i].st) now=a[i].st;
		int num=(int)ceil((a[i].en-now)*1.0/l);
		now+=l*num;ans+=num;
	}
	cout<<ans<<endl;
	
	return 0;
}
