/*
DATE : 2013-5-29 
RATING : 3
TAG : 2D-BIT
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

const int MAXN = 2048 + 10;

inline int lowbit(int x) {return x&(-x);}

int n,m;

struct BIT 
{
	int s[MAXN][MAXN];
	BIT() {memset(s,0,sizeof(s));}
	inline void Add(int x,int y,int c)
	{
		for(int ix=x;ix<=n;ix+=lowbit(ix))
			for(int iy=y;iy<=m;iy+=lowbit(iy)) s[ix][iy]+=c;
	}
	inline int Sum(int x,int y)
	{
		int res=0;
		for(int ix=x;ix;ix-=lowbit(ix))
			for(int iy=y;iy;iy-=lowbit(iy)) res+=s[ix][iy];
		return res;
	}
} b1,b2,b3,b4;

void Update(int x,int y,int c)
{
	if(!x || !y) return;
	b1.Add(1,1,c);b1.Add(1,y,-c);b1.Add(x,1,-c);b1.Add(x,y,c);
	b2.Add(x,1,c*x);b2.Add(x,y,-c*x);
	b3.Add(1,y,c*y);b3.Add(x,y,-c*y);
	b4.Add(x,y,x*y*c);
}

int Query(int x,int y) 
{
	if(!x || !y) return 0;
	return b1.Sum(x,y)*x*y+b2.Sum(x,y)*y+b3.Sum(x,y)*x+b4.Sum(x,y);
}

char ch[20];

int main()
{
	scanf("%s",ch);
	scanf("%d%d",&n,&m);
	while(scanf("%s",ch)!=EOF)
	{
		int a,b,c,d,delta;
		if(ch[0]=='L')
		{
			scanf("%d%d%d%d%d",&a,&b,&c,&d,&delta);
			a--;b--;
			Update(c,d,delta);Update(a,b,delta);
			Update(a,d,-delta);Update(c,b,-delta);
		}
		else
		{
			scanf("%d%d%d%d",&a,&b,&c,&d);
			--a;--b;
			printf("%d\n",Query(c,d)+Query(a,b)-Query(a,d)-Query(c,b));
		}
	}
	
	return 0;
}
