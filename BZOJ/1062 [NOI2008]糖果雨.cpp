#include <iostream>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <cmath>
#include <algorithm>
#include <fstream>

using namespace std;

const int MAXN = 1000 + 100;
const int MAXM = 1000000 + 10;

typedef int arr[MAXN*2][MAXN*4];
arr a,b;
struct Cloud
{
	int x,y;
} cloud[MAXM];
int n,m,len,T;

inline int lowbit(int x) {return x&(-x);}

int Add(arr a,int x,int y,int d)
{
	++x;++y;
	for(int i=x;i<=n+1;i+=lowbit(i))
		for(int j=y;j<=m+1;j+=lowbit(j)) a[i][j]+=d;
}

void Update(int color,int d)
{
	Add(a,cloud[color].x,cloud[color].y-cloud[color].x+n,d);
	Add(b,cloud[color].x,cloud[color].y+cloud[color].x,d);
}

int Query(arr a,int x,int y)
{
	if(x<0 || y<0) return 0;
	x=(x>=n) ? n+1 : x+1;
	y=(y>=m) ? m+1 : y+1;
	int res=0;
	for(int i=x;i;i-=lowbit(i))
		for(int j=y;j;j-=lowbit(j)) res+=a[i][j];
	return res;
}

int Sum(arr a,int x1,int x2,int y1,int y2)
{
	return Query(a,x2,y2)+Query(a,x1-1,y1-1)-Query(a,x1-1,y2)-Query(a,x2,y1-1);
}

int Get_ans(int t,int l,int r)
{
	int d=(r==len);
	return Sum(a,t-r,t,l+n-t,m)+Sum(b,t+1,t+r,l+t,m)+Sum(a,t-r+d+n,n,l-t,m)+Sum(b,0,t+r-d-n,l+t-n,m);
}

int main()
{
	scanf("%d%d",&T,&len);n=len*2;m=len*4;
	int opr,t,l,r,d,c;
	while(T--)
	{
		scanf("%d",&opr);scanf("%d",&t);t%=n;
		if(opr==1)
		{
			scanf("%d%d%d%d",&c,&l,&r,&d);
			cloud[c].x=(t-l*d+n)%n;
			cloud[c].y=r-l;
			Update(c,1);
		}
		else if(opr==2)
		{
			scanf("%d%d",&l,&r);
			printf("%d\n",Get_ans(t,l,r));
		}
		else
		{
			scanf("%d",&c);
			Update(c,-1);
		}
	}
	
	return 0;
}
