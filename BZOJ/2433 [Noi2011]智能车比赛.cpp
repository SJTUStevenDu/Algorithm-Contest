#include <iostream>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <cmath>
#include <algorithm>
#include <fstream>

using namespace std;

const int MAXN = 2000 + 10;
const double INF = 1e50;

struct Point
{
	long long x,y;
} S,T;

struct Rec
{
	Point a,b,c,d;
} rec[MAXN];

int n;
double f[MAXN*4];
double v,ans=INF;

inline void checkmin(double &x,double y) {if(x>y) x=y;}

double dist(Point A,Point B)
{
	return sqrt((double)(A.x-B.x)*(A.x-B.x)+(double)(A.y-B.y)*(A.y-B.y));
}

long long crossPro(Point A,Point B,Point C,Point D)
{
	return (B.x-A.x)*(D.y-C.y)-(B.y-A.y)*(D.x-C.x);
}

bool check(Point A,Point B,Point upper,Point lower)
{
	if(B.x<A.x) return false;
	if(crossPro(A,upper,A,B)>0) return false;
	if(crossPro(A,lower,A,B)<0) return false;
	return true;
}

void init()
{
	scanf("%d",&n);
	for(int i=1;i<=n;i++)
	{
		long long a1,a2,a3,a4;
		scanf("%lld%lld%lld%lld",&a1,&a2,&a3,&a4);
		rec[i].a.x=a1;rec[i].a.y=a2;
		rec[i].b.x=a1;rec[i].b.y=a4;
		rec[i].c.x=a3;rec[i].c.y=a2;
		rec[i].d.x=a3;rec[i].d.y=a4;
	}
	scanf("%lld%lld%lld%lld",&S.x,&S.y,&T.x,&T.y);
	if(S.x>T.x) swap(S,T);
	for(int i=1;i<=n*4;i++) f[i]=INF;
	scanf("%lf",&v);
}

void Work(Point St,int now,double d)
{
	if(d>=INF) return;
	Point lower,upper;
	lower.x=upper.x=St.x;
	lower.y=St.y-1;upper.y=St.y+1;
	for(int i=now;i<=n;i++)
	{
		if(check(St,rec[i].a,upper,lower)) checkmin(f[(i-1)*4+1],d+dist(St,rec[i].a));
		if(check(St,rec[i].b,upper,lower)) checkmin(f[(i-1)*4+2],d+dist(St,rec[i].b));
		if(check(St,rec[i].c,upper,lower)) checkmin(f[(i-1)*4+3],d+dist(St,rec[i].c));
		if(check(St,rec[i].d,upper,lower)) checkmin(f[(i-1)*4+4],d+dist(St,rec[i].d));
		if(rec[i].a.x<=T.x && rec[i].d.x>=T.x && rec[i].a.y<=T.y && rec[i].d.y>=T.y)
			{if(check(St,T,upper,lower)) checkmin(ans,d+dist(St,T));}
		if(i<n)
		{
			Point l,r;
			l.x=r.x=rec[i].d.x;
			l.y=max(rec[i].c.y,rec[i+1].a.y);r.y=min(rec[i].d.y,rec[i+1].b.y);
			if(l.x==St.x)
			{
				if(St.y<l.y || St.y>r.y)
				{
					checkmin(f[i*4+1],d+dist(St,rec[i+1].a));
					checkmin(f[i*4+2],d+dist(St,rec[i+1].b));
					return;
				}
			}
			else 
			{
				if(crossPro(St,lower,St,l)>0) lower=l;
				if(crossPro(St,upper,St,r)<0) upper=r;
				if(crossPro(St,upper,St,lower)>0) return;
			}
		}
	}
}

void Solve()
{
	int i;
	for(i=1;i<=n;i++) if(rec[i].a.x<=S.x && rec[i].d.x>=S.x && rec[i].a.y<=S.y && rec[i].d.y>=S.y) break;
	Work(S,i,0);
	for(;i<=n;i++)
	{
		Work(rec[i].a,i,f[(i-1)*4+1]);
		Work(rec[i].b,i,f[(i-1)*4+2]);
		Work(rec[i].c,i,f[(i-1)*4+3]);
		Work(rec[i].d,i,f[(i-1)*4+4]);
	}
	printf("%.10lf\n",ans/v);
}

int main()
{
	init();
	Solve();
	
	return 0;
}
