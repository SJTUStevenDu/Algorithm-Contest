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
	scanf("%d%d",&n,&m);
	for(int i=min(n,m);i;--i)
	{
		f[i]=(long long)(n/i)*(m/i);
		for(int j=2;j<=min(n,m)/i;++j)
			f[i]-=f[i*j];
		ans+=f[i]*(2*i-1);
	}
	printf("%lld\n",ans);
	
	return 0;
}
