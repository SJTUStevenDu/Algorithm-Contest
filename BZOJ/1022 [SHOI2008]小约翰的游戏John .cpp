/*
DATE : 2013-3-18 
RATING : 3
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

int cnt,ans;
bool flag;
int T,n,a;

int main()
{
	scanf("%d",&T);
	while(T--)
	{
		cnt=ans=0;flag=0;
		scanf("%d",&n);
		for(int i=0;i<n;i++) 
		{
			scanf("%d",&a);
			if(a==1) cnt++;
			else flag=true;
			ans^=a;
		}
		if(flag) 
		{
			if(ans==0) printf("Brother\n");
			else printf("John\n");
		}
		else 
		{
			if(cnt%2==0) printf("John\n");
			else printf("Brother\n");
		}
	}
	
	return 0;
}
