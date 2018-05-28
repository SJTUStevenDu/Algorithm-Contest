/*
DATE : 2013-2-10 
RATING : 1
TAG : Binary
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

//Orz WJMZBMR && sevenkplus

using namespace std;

int n,ans=1;

int main()
{
	scanf("%d",&n);
	int k=1,m=1;
	while(m<n)
	{
		ans++;
		k*=2;
		m+=k;
	}
	printf("%d\n",ans);
	
	return 0;
}
