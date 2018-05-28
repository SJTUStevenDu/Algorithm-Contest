/*
DATE : 2012-12-23 
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

using namespace std;

int gcd(int n,int m)
{
	if(n%m==0) return m;
	else return gcd(m,n%m);
}

int n,m,a,b;
double ans=100000000,s;

int main()
{
	cin>>n>>m;
	s=n*1.0/m;
	for(int i=1;i<=32767;i++)
	{
		if(i==m) continue;
		int x=i*n/m;
		if(x>0 && gcd(i,x)==1 && fabs(s-x*1.0/i)<ans) ans=fabs(s-x*1.0/i),a=x,b=i;
		x++;
		if(gcd(i,x)==1 && fabs(s-x*1.0/i)<ans) ans=fabs(s-x*1.0/i),a=x,b=i;
		x-=2;
		if(x>0 && gcd(i,x)==1 && fabs(s-x*1.0/i)<ans) ans=fabs(s-x*1.0/i),a=x,b=i;
	}
	cout<<a<<' '<<b<<endl;
	
	return 0;
}
