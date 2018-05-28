/*
DATE : 2013-3-25 
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

inline int Ex_gcd(int a,int b,int &x,int &y,int c)
{
	if(b==0)
	{
		x=c/a;
		y=0;
		return a;
	}
	int d=Ex_gcd(b,a%b,x,y,c);
	int tmp=y;
	y=x-a/b*y;x=tmp;
	return d;
}

int n,m;
int P[20],C[20],L[20];
bool flag=false;

int main()
{
	scanf("%d",&n);
	int maxc=0;
	for(int i=1;i<=n;i++) scanf("%d%d%d",&C[i],&P[i],&L[i]),maxc=max(maxc,C[i]);
	for(m=maxc;!flag;++m)
	{
		flag=true;
		for(int i=1;i<=n;i++) 
		{
			if(!flag) break;
			for(int j=i+1;j<=n;j++) 
			{
				int a=P[i]-P[j];
				int c=C[j]-C[i];
				int x,y;
				int dd=Ex_gcd(a,m,x,y,c);
				if(c%dd==0)
				{
					int TT=abs(m/dd);
					x=(x%TT+TT)%TT;
					if(x<=min(L[i],L[j])) {flag=false;break;}
				}
			}
		}
	}
	printf("%d\n",m-1);
	
	return 0;
}
