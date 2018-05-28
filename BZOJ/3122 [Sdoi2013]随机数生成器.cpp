#include <iostream>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <cmath>
#include <algorithm>
#include <fstream>

using namespace std;

const int MOD = 999983;
const int MAXN = 40000 + 10;

int p[MAXN],r[MAXN],nxt[MAXN],h[MOD],tot;
int t,a,b,x1,xn,CaseNum;

inline int gcd(int n,int m)
{
	while(m!=0)
	{
		int tmp=n%m;
		n=m;
		m=tmp;
	}
	return n;
}

void ex_gcd(int a,int b,int c,long long &x,long long &y)
{
	if(!b) 
	{
		x=c/a;
		y=0;
		return;
	}
	long long tx,ty;
	ex_gcd(b,a%b,c,tx,ty);
	x=ty;y=tx-a/b*ty;
}

inline int Find(int x)
{
	for(int i=h[x%MOD];i;i=nxt[i]) if(p[i]==x) return i;
	return -1;
}

inline void Insert(int x,int y)
{
	if(~Find(x)) return;
	tot++;p[tot]=x;r[tot]=y;nxt[tot]=h[x%MOD];h[x%MOD]=tot;
}

inline int calc1(int a,int b,int c)
{
	int d=abs(gcd(a,b));
	if(c%d) return -2;
	long long x,y;
	ex_gcd(a,b,c,x,y);
	b/=d;
	return (x%b+b)%b;
}

inline int calc2(int a,int b,int c,int d)
{
	if(!d && !b) return 0;
	memset(h,tot=0,sizeof(h));
	long long t=1%c,e=t;
	int m=(int)ceil(sqrt(c));
	for(int i=0;i<m;i++,e=e*a%c) Insert(e,i);
	for(int i=0;i<=m;i++,t=t*e%c)
	{
		int q=calc1(t*d%c,c,b);
		if(q!=-2)
		{
			int k=Find(q);
			if(~k) return i*m+r[k];
		}
	}
	return -2;
}

int main()
{
	scanf("%d",&CaseNum);
	while(CaseNum--)
	{
		scanf("%d%d%d%d%d",&t,&a,&b,&x1,&xn);
		if(a==1) printf("%d\n",calc1(b,t,xn-x1)+1);
		else printf("%d\n",calc2(a,((long long)(a-1)*xn+b)%t,t,((long long)(a-1)*x1+b)%t)+1);
	}
	
	return 0;
}
