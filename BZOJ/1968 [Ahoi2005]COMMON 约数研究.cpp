/*
DATE : 2013-4-4 
RATING : 2
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

int n,ans;

int main()
{
	scanf("%d",&n);
	for(int i=1;i<=n;i++) ans+=n/i;
	printf("%d\n",ans);
	
	return 0;
}
