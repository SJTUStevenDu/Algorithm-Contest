/*
DATE : 2012-12-4 
RATING : 1
TAG : DP
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

int n,h,p[105],v[105],f[100005],ans=0x7FFFFFFF;

int main()
{
	memset(f,22,sizeof(f));
	f[0]=0;
	cin>>n>>h;
	for(int i=1;i<=n;i++) cin>>v[i]>>p[i];
	for(int i=1;i<=n;i++)
		for(int j=v[i];j<=2*h;j++) f[j]=min(f[j],f[j-v[i]]+p[i]);
	for(int i=h;i<=2*h;i++) ans=min(ans,f[i]);
	cout<<ans<<endl;
	return 0;
}
