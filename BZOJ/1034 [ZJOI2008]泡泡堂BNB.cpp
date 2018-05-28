/*
DATE : 2013-4-21
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
#include <map>
#include <vector>

//Orz WJMZBMR && sevenkplus

using namespace std;

const int MAXN = 100000 + 10;

int n,a[MAXN],b[MAXN],tmp[MAXN];

int calc()
{
	int re=0;
	int i=1,j=1,p=n,q=n;
	while(i<=p && j<=q)
	{
		if(a[i]>b[j]) re+=2,i++,j++;
		else if(a[p]>b[q]) re+=2,p--,q--;
		else if(a[i]==b[q]) re+=1,q--,i++;
		else q--,i++;
	}
	return re;
}

int main()
{
	scanf("%d",&n);
	for(int i=1;i<=n;i++) scanf("%d",&a[i]);
	for(int i=1;i<=n;i++) scanf("%d",&b[i]);
	sort(a+1,a+1+n);
	sort(b+1,b+1+n);
	printf("%d ",calc());
	memcpy(tmp,a,sizeof(a));
	memcpy(a,b,sizeof(a));
	memcpy(b,tmp,sizeof(b));
	printf("%d\n",2*n-calc());
	
	return 0;
}
