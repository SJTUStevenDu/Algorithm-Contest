/*
DATE : 2012-11-23 
RATING : 1
TAG : Longest Increase/Decrease Sequence
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

const int MAXN=30005;
int n,a[MAXN],f[MAXN],ans;

int main()
{
	cin>>n;
	for(int i=1;i<=n;i++) cin>>a[i];
	for(int i=1;i<=n;i++)
	{
		for(int j=1;j<i;j++) if(a[i]>=a[j]) f[i]=max(f[i],f[j]);
		f[i]++;
		ans=max(ans,f[i]);
	}
	memset(f,0,sizeof(f));
	for(int i=1;i<=n;i++)
	{
		for(int j=1;j<i;j++) if(a[i]<=a[j]) f[i]=max(f[i],f[j]);
		f[i]++;
		ans=max(ans,f[i]);
	}
	cout<<n-ans<<endl;
	
	return 0;
}
