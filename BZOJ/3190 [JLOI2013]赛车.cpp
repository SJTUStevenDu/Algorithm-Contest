#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cmath>
#include <string>
#include <fstream>
#include <algorithm>

using namespace std;

// By StevenKlose

const int MAXN = 10000 + 10;
const double INF = 1e20;
const double eps = 1e-11;

int v[MAXN],g[MAXN];
bool able[MAXN];
int ans,n;

inline double MIN(double a,double b)
{
	if(a<b) return a;
	else return b;
}

inline double MAX(double a,double b)
{
	if(a>b) return a;
	else return b;
}

int main()
{
	freopen("race.in","r",stdin);
	freopen("race.out","w",stdout);
	scanf("%d",&n);
	for(int i=1;i<=n;i++) scanf("%d",&g[i]);
	for(int i=1;i<=n;i++) scanf("%d",&v[i]);
	for(int i=1;i<=n;i++)
	{
		double maxt=0.0,mint=INF;
		bool flag=true;
		for(int j=n;j>=0;j--)
		{
			if(maxt>mint) 
			{
				flag=false;
				break;
			}
			if(j==i || j==0) continue;
			if(g[i]>g[j])
			{
				double t=(double)(g[j]-g[i])/(double)(v[i]-v[j]);
				if(t<=eps) continue;
				else mint=MIN(mint,t);
			}
			else if(g[i]<g[j])
			{
				double t=(double)(g[j]-g[i])/(double)(v[i]-v[j]);
				if(t<=eps) {maxt=INF*2;continue;}
				else maxt=MAX(maxt,t);
			}
			else 
			{
				if(v[i]<v[j]) {mint=0.0;continue;}
			}
		}
		if(flag) ++ans;
		able[i]=flag;
	}
	printf("%d\n",ans);
	bool first=true;
	for(int i=1;i<=n;i++)
	{
		if(!able[i]) continue;
		if(first) first=false;
		else printf(" ");
		printf("%d",i);
	}
	printf("\n");
	
	return 0;
}
