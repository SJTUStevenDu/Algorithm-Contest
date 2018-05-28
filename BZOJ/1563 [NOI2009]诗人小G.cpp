/*
DATE : 2013-4-25 
RATING : 3
TAG : DP + 四边形不等式 
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

//Orz WJMZBMR && sevenkplus

using namespace std;

const int MAXN = 100000 + 10;
const long long INF = 1000000000000000000LL;

struct Interval
{
	int s,t,deci;
} di[MAXN];

int len[MAXN],n,T,L,P,head,tail,deci[MAXN];
long long sum[MAXN];
char s[40];
long long g[MAXN];
double f[MAXN];

void Init()
{
	scanf("%d%d%d",&n,&L,&P);
	for(int i=1;i<=n;i++)
	{
		scanf("%s",s);
		len[i]=strlen(s);
		sum[i]=sum[i-1]+len[i];
	}
}

double dPower(double a)
{
	double res=1.0;
	if(a<0) a=-a;
	for(int i=1;i<=P;i++) res*=a;
	return res;
}

long long Power(long long a)
{
	long long res=1;
	double ress=1.0;
	if(a<0) a=-a;
	for(int i=1;i<=P;i++)
	{
		ress*=a;
		if(ress>INF) return INF+1;
		res*=a;
	}
	return res;
}

double GetF(int i,int j)
{
	return f[j]+dPower(sum[i]-sum[j]+i-j-1-L);
}

long long GetG(int i,int j)
{
	long long tmp=Power(sum[i]-sum[j]+i-j-1-L);
	if(f[j]+tmp<=INF) return g[j]+tmp;
	else return INF+1;
}

void Update(int i)
{
	while(di[tail].s>i && GetF(di[tail].s,di[tail].deci)>GetF(di[tail].s,i)) {di[tail-1].t=di[tail].t;tail--;}
	int l=di[tail].s,r=di[tail].t;
	if(l<i+1) l=i+1;
	while(l+1<r)
	{
		int mid=(l+r)/2;
		if(GetF(mid,di[tail].deci)<GetF(mid,i)) l=mid;
		else r=mid-1;
	}
	if(l<r && GetF(r,di[tail].deci)<GetF(r,i)) l=r;
	if(l+1<=di[tail].t)
	{
		di[tail+1].s=l+1;
		di[tail+1].t=di[tail].t;
		di[tail].t=l;
		di[tail+1].deci=i;
		tail++;
	}
}

void Solve()
{
	head=1;tail=1;
	di[tail].s=1;di[tail].t=n;
	for(int i=1;i<=n;i++)
	{
		if(i>di[head].t) head++;
		deci[i]=di[head].deci;
		f[i]=GetF(i,deci[i]);
		Update(i);
	}
	for(int i=1;i<=n;i++) g[i]=GetG(i,deci[i]);
	if(g[n]<=INF) printf("%lld\n",g[n]);
	else printf("Too hard to arrange\n");
	printf("--------------------\n");
}

int main()
{
	scanf("%d",&T);
	while(T--)
	{
		Init();
		Solve();
	}
	
	return 0;
}
