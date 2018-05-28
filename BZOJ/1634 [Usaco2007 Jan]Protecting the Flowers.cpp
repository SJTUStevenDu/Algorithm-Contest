/*
DATE : 2012-11-29 
RATING : 1
TAG : Greedy
*/

#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <cstdlib>
#include <iomanip>
#include <cmath>
#include <iomanip>
#include <fstream>
#include <string>

//Orz WJMZBMR && sevenkplus

using namespace std;

struct cow
{
	long long t,f;
} c[100005];
int n;
long long ans;
long long sum;

int cmp(cow a,cow b)
{
	return (double)a.t/a.f<(double)b.t/b.f; 
}

int main()
{
	cin>>n;
	for(int i=1;i<=n;i++) cin>>c[i].t>>c[i].f;
	sort(c+1,c+1+n,cmp);
	for(int i=1;i<=n;i++) sum+=c[i].f;
	for(int i=1;i<=n;i++) 
	{
		sum-=c[i].f;
		ans+=(c[i].t*2*sum);
	}
	cout<<ans<<endl;
	
	return 0;
}
