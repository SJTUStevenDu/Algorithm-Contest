/*
DATE : 2012-11-30 
RATING : 2
TAG : enumeration
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

const int MAXN = 200+10;

struct point{
	int x;int y;
} P[MAXN],Line[MAXN*MAXN];

int n,cnt,ans=1;

int main()
{
	scanf("%d",&n);
	for(int i=1;i<=n;i++) scanf("%d%d",&P[i].x,&P[i].y);
	for(int i=1;i<n;i++)
		for(int j=i+1;j<=n;j++) Line[++cnt].x=P[j].x-P[i].x,Line[cnt].y=P[j].y-P[i].y;
	for(int i=2;i<=cnt;i++) 
	{
		bool flag=1;
		for(int j=1;j<i;j++) if(Line[i].x*Line[j].y==Line[i].y*Line[j].x) {flag=0;break;}
		if(flag) ans++;
	}
	cout<<ans<<endl;
	
	return 0;
}
