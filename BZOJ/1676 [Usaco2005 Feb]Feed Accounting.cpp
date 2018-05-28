/*
DATE : 2012-12-14 
RATING : 1
TAG : 
*/

#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <cstdlib>
#include <iomanip>
#include <cmath>
#include <vector>
#include <fstream>
#include <string>

//Orz WJMZBMR && sevenkplus

using namespace std;

const int MAXN = 105;

int n,f1,f2,d,delta,ans;
int a[5000],sum[5000];

int main()
{
	cin>>n>>f1>>f2>>d;
	delta=f1-f2;
	int eaten=0;
	for(int i=1;i<=n;i++)
	{
		int aa,bb;
		cin>>aa>>bb;
		a[aa]++;a[bb+1]--;
	}
	for(int i=1;i<=d;i++) 
		sum[i]=sum[i-1]+a[i];
	for(int i=d;i;i--)
	{
		eaten+=sum[i];
		if(eaten==delta) {ans=i;break;}
	}
	cout<<ans<<endl;
	return 0;
}
