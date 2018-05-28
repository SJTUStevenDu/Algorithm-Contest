/*
DATE : 2013-4-21
RATING : 2
TAG : 2
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

const int MAXN = 10000000 + 10;

int a[MAXN],n,A,B,C;
double ans;

int main()
{
	scanf("%d%d%d%d%d",&n,&A,&B,&C,&a[1]);
	for(int i=2;i<=n;i++) a[i]=((long long)a[i-1]*A+B)%100000001;
	for(int i=1;i<=n;i++) a[i]=a[i]%C+1;
	for(int i=1;i<n;i++) ans+=1/(double)max(a[i],a[i+1]);
	ans+=1/(double)max(a[1],a[n]);
	printf("%.3lf\n",ans);
	
	return 0;
}
