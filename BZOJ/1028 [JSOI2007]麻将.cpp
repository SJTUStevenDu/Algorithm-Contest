/*
DATE : 2013-4-4 
RATING : 2
TAG : Enum
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

const int MAXN = 500 + 10;

int a[MAXN],b[MAXN],n,m;
bool flag=false;

bool check()
{
	for(int i=1;i<=n;i++) if(a[i]>=2)
	{
		bool ok=true;
		memcpy(b,a,sizeof(a));
		b[i]-=2;
		for(int j=1;j<=n;j++) 
		{
			if(b[j]==0) continue;
			b[j]%=3;
			if(b[j]==0) continue;
			if(j>n-2)
			{
				ok=false;
				break;
			}
			if(b[j]>b[j+1] || b[j]>b[j+2]) 
			{
				ok=false;
				break;
			}
			b[j+1]-=b[j];
			b[j+2]-=b[j];
			b[j]=0;
		}
		if(ok) return true;
	}
	return false;
}

int main()
{
	scanf("%d%d",&n,&m);
	m=m*3+1;
	for(int tmp,i=1;i<=m;i++)
	{
		scanf("%d",&tmp);
		a[tmp]++;
	}
	for(int i=1;i<=n;i++) 
	{
		a[i]++;
		if(check())
		{
			if(!flag) 
			{
				printf("%d",i);
				flag=true;
			}
			else printf(" %d",i);
		}
		a[i]--;
	}
	if(!flag) printf("NO\n");else printf("\n");
	
	return 0;
}
