/*
DATE : 2013-3-18 
RATING : 1
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
#include <map>
#include <vector>

//Orz WJMZBMR && sevenkplus

using namespace std;

int n,m;
long long ans,f[100000 + 10];

int main()
{
	scanf("%d",&n);--n;
	for(int i=n;i;--i)
	{
		f[i]=(long long)(n/i)*(n/i);
		for(int j=2;j<=n/i;++j)
			f[i]-=f[i*j];
	}
	printf("%lld\n",f[1]+2);
	
	return 0;
}
