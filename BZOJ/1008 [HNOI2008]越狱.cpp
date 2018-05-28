/*
DATE : 2013-3-30 
RATING : 1
TAG : QuickPow
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

const int MOD = 100003;

long long QuickPow(long long a,long long b,int c)
{
	long long re=1;
	while(b)
	{
		if(b&1) re=(re*a)%c;
		a=(a*a)%c;
		b>>=1;
	}
	return re;
}

long long n,m;

int main()
{
	scanf("%lld%lld",&m,&n);
	printf("%lld\n",(QuickPow(m,n,MOD)-(m*QuickPow(m-1,n-1,MOD))%MOD+MOD)%MOD);
	
	return 0;
}
