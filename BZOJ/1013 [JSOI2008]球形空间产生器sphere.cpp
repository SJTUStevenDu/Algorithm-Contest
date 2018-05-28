/*
DATE : 2013-7-30 
RATING : 2
TAG : Gauss Elimination
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

const int MAXN = 15;
const double eps=1e-7;

double a[MAXN][MAXN],tmp1,tmp2;
int n;
double ans[MAXN],P[MAXN];

int main()
{
	scanf("%d",&n);
	for(int i=1;i<=n;i++) scanf("%lf",&P[i]);
	for(int i=1;i<=n;i++) 
	{
		tmp1=0.0;
		for(int j=1;j<=n;j++)
		{
			scanf("%lf",&tmp2);
			a[i][j]=tmp2-P[j];
			tmp1+=tmp2*tmp2-P[j]*P[j];
		}
		tmp1=tmp1/2;
		a[i][n+1]=tmp1;
	}	
	for(int i=1;i<=n;i++)
	{
		int x=-1;
		for(int j=i;j<=n;j++) if(fabs(a[j][i])>eps) {x=j;break;}
		if(x==-1) continue;
		for(int j=i;j<=n+1;j++) swap(a[i][j],a[x][j]);
		for(int j=i+1;j<=n;j++)
			for(int k=i+1;k<=n+1;k++) 
			{
				a[j][k]-=a[j][i]/a[i][i]*a[i][k];
			}
	}
	for(int i=n;i;i--)
	{
		ans[i]=a[i][n+1];
		for(int j=i+1;j<=n;j++) ans[i]-=ans[j]*a[i][j];
		ans[i]/=a[i][i];
	}
	for(int i=1;i<n;i++) printf("%.3lf ",ans[i]);
	printf("%.3lf\n",ans[n]);
	
	return 0;
}
