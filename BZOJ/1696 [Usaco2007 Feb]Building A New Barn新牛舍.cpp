/*
DATE : 2013-2-6 
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

//Orz WJMZBMR && sevenkplus

using namespace std;

const int MAXN = 10005;

int x[MAXN],y[MAXN],xx[MAXN],yy[MAXN];
int n,dist,ans;

int main()
{
	scanf("%d",&n);
	for(int i=1;i<=n;i++) scanf("%d",&x[i]),xx[i]=x[i],scanf("%d",&y[i]),yy[i]=y[i];
	sort(xx+1,xx+1+n);
	sort(yy+1,yy+1+n);
	if(n%2==1)
	{
		ans=1;
		for(int i=1;i<=n;i++) if(x[i]==xx[n/2+1] && y[i]==yy[n/2+1]) {ans=0;break;}
		if(ans) for(int i=1;i<=n;i++) dist+=(abs(x[i]-xx[n/2+1])+abs(y[i]-yy[n/2+1]));
		else
		{
			int dist1=0,dist2=0,dist3=0,dist4=0;
			for(int i=1;i<=n;i++) 
			{
				dist1+=(abs(x[i]-xx[n/2+1]+1)+abs(y[i]-yy[n/2+1]));
				dist2+=(abs(x[i]-xx[n/2+1]-1)+abs(y[i]-yy[n/2+1]));
				dist3+=(abs(x[i]-xx[n/2+1])+abs(y[i]-yy[n/2+1]+1));
				dist4+=(abs(x[i]-xx[n/2+1])+abs(y[i]-yy[n/2+1]-1));
			}
			dist=min(dist1,min(dist2,min(dist3,dist4)));
			if(dist1==dist) ans++;if(dist2==dist) ans++;
			if(dist3==dist) ans++;if(dist4==dist) ans++;
		}
	}
	else
	{
		int lx=xx[n/2],ly=yy[n/2],rx=xx[n/2+1],ry=yy[n/2+1];
		ans=(rx-lx+1)*(ry-ly+1);
		for(int i=1;i<=n;i++)
		{
			if(x[i]<=rx && x[i]>=lx && y[i]<=ry && y[i]>=ly) ans--;
			dist+=(abs(x[i]-lx)+abs(y[i]-ly));
		}
	}
	printf("%d %d\n",dist,ans);
	return 0;
}
