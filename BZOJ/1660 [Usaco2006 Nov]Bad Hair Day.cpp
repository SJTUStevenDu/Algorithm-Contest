/*
DATE : 2012-12-12 
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
#include <stack>

//Orz WJMZBMR && sevenkplus

using namespace std;

const int MAXN = 80000 + 10;

stack <int> s;
long long ans;
int a[MAXN],n;

int main()
{
	scanf("%d",&n);
	for(int i=1;i<=n;i++) scanf("%d",&a[i]);
	for(int i=1;i<=n;i++)
	{
		while(!s.empty() && s.top()<=a[i]) s.pop();
		ans+=s.size();
		s.push(a[i]);
	}
	printf("%lld\n",ans);
	
	return 0;
}
