/*
DATE : 2013-3-4 
RATING : 2
TAG : Math
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
#include <map>
#include <queue>

//Orz WJMZBMR && sevenkplus

using namespace std;

int n,k;
long long ans;

int main()
{
	scanf("%d%d",&n,&k);
	ans=(long long)n*k;
	for(int i=1;i<=n;)
	{
		int l=i,r=n;
		while(l<=r)
		{
			int mid=(l+r)/2;
			if(k/mid<k/i) r=mid-1;
			else l=mid+1;
		}
		ans-=(long long)(i+r)*(r-i+1)/2*(k/i);
		i=r+1;
	}
	printf("%lld\n",ans);
	
	return 0;
}
