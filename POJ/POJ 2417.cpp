#include <iostream>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <cmath>
#include <algorithm>
#include <fstream>

using namespace std;

const int MOD = 999983;
const int MAXN = 60000 + 10;

int h[MOD],nxt[MAXN],p[MAXN],r[MAXN];
int a,b,c,tot,ans;

inline int Find(int x)
{
	for(int i=h[x%MOD];i;i=nxt[i]) if(p[i]==x) return i;
	return -1;
}

inline void Add(int x,int y)
{
	if(~Find(x)) return;
	++tot;p[tot]=x;r[tot]=y;nxt[tot]=h[x%MOD];h[x%MOD]=tot;
}

void Ex_gcd(int a,int b,int c,long long &x,long long &y)
{
	if(b==0) 
	{
		x=c/a;
		y=1;
		return;
	}
	long long tx,ty;
	Ex_gcd(b,a%b,c,tx,ty);
	x=ty;y=tx-a/b*ty;
}

int calc(int a,int b,int c)
{
	long long t=1%c,e=t;
	int m=(int)(ceil(sqrt((double)c)));
	for(int i=0;i<m;++i,e=e*a%c) Add(e,i);
	for(int i=0;i<=m;++i,t=t*e%c)
	{
		long long x,y;
		Ex_gcd(t,c,b,x,y);
		int k=Find((x%c+c)%c);
		if(~k) return i*m+r[k];
	}
	return -1;
}

int main()
{
	while(~scanf("%d%d%d",&c,&a,&b))
	{
		memset(h,tot=0,sizeof(h));
		ans=calc(a,b,c);
		if(~ans) printf("%d\n",ans);
		else printf("no solution\n");
	}
	
	return 0;
}
