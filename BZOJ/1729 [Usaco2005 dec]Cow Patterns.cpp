/*
DATE : 2013-2-14 
RATING : 3
TAG : KMP
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

const int MAXN = 100000 + 5;
const int MAXS = 26;

int a[MAXN],b[MAXN];
int amin[MAXN][MAXS],aequal[MAXN][MAXS],bmin[MAXN][MAXS],bequal[MAXN][MAXS];
int next[MAXN];
int ans[MAXN],ansn;
int n,m,s;

int main()
{
	scanf("%d%d%d",&n,&m,&s);
	for(int i=1;i<=n;i++) scanf("%d",&a[i]);
	for(int i=1;i<=m;i++) scanf("%d",&b[i]);
	for(int i=1;i<=n;i++)
		for(int j=1;j<=s;j++)
		{
			amin[i][j]=amin[i-1][j]+(a[i]<j);
			aequal[i][j]=aequal[i-1][j]+(a[i]==j);
		}
	for(int i=1;i<=m;i++)
		for(int j=1;j<=s;j++)
		{
			bmin[i][j]=bmin[i-1][j]+(b[i]<j);
			bequal[i][j]=bequal[i-1][j]+(b[i]==j);
		}
	int i=1,j=0;
	while(i<=m)
	{
		if(!j || (bmin[i][b[i]]-bmin[i-j][b[i]]==bmin[j][b[j]] && bequal[i][b[i]]-bequal[i-j][b[i]]==bequal[j][b[j]])) i++,j++,next[i]=j;
		else j=next[j];
	}
	i=1;j=1;
	while(i<=n)
	{
		if(!j || (amin[i][a[i]]-amin[i-j][a[i]]==bmin[j][b[j]] && aequal[i][a[i]]-aequal[i-j][a[i]]==bequal[j][b[j]]))
		{
			i++;j++;
			if(j>m) ans[++ansn]=i-m,j=next[j];
		}
		else j=next[j];
	}
	printf("%d\n",ansn);
	for(int i=1;i<=ansn;i++) printf("%d\n",ans[i]);
	
	return 0;
}
