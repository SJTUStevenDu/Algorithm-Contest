/*
DATE : 2013-3-24 
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

long long r,ans;

inline long long gcd(long long n,long long m)
{
	long long tmp;
	while(m)
	{
		tmp=n%m;
		n=m;
		m=tmp;
	}
	return n;
}

bool IsSquare(long long p)
{
	long long b=(long long)(sqrt(p)+0.5);
	return b*b==p;
}

bool Work(long long p)
{
	long long u;
	for(u=1;u*u<p;++u)
	{
		long long v=p-u*u;
		if(u*u>=v) break;
		if(!IsSquare(v)) continue;
		if(gcd(u,v)==1) ++ans;
	}
}

int main()
{
	cin>>r;r<<=1;
	long long i;
	for(i=1;i*i<r;++i)
	{
		if(r%i) continue;
		Work(i);Work(r/i);
	}
	if(i*i==r) Work(i);
	cout<<ans*4+4<<endl;
	
	return 0;
}
