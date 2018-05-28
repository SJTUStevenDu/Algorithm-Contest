/*
DATE : 2012-08-14
RATING : 1
TAG : DP
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

//Orz WJMZBMR && sevenkplus

using namespace std;

int n,v;
int f[12885],w[3405],d[3405];
int ans=0;

int main()
{
	scanf("%d%d",&n,&v);
	for(int i=1;i<=n;i++) scanf("%d %d",&w[i],&d[i]);
	for(int i=1;i<=n;i++)
		for(int j=v;j>=w[i];j--)
			f[j]=max(f[j],f[j-w[i]]+d[i]);
	for(int i=1;i<=v;i++) ans=max(ans,f[i]);
	printf("%d\n",ans);
	return 0;
}
