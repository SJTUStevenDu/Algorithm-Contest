/*
DATE : 2013-2-11 
RATING : 1
TAG : STL
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
#include <set>

//Orz WJMZBMR && sevenkplus

using namespace std;

int T;
int n;
set <int> Q;

int main()
{
	scanf("%d",&T);
	while(T--)
	{
		bool first=true;
		Q.clear();
		scanf("%d",&n);
		for(int i=1;i<=n;i++) 
		{
			int a;
			scanf("%d",&a);
			if(Q.count(a)) continue;
			Q.insert(a);
			if(first) printf("%d",a),first=false;
			else printf(" %d",a);
		}
		printf("\n");
	}
	
	return 0;
}
