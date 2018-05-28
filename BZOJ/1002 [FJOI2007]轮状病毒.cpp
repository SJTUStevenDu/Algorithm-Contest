/*
DATE : 2013-3-31 
RATING : 2
TAG : Math
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

const int MAXN = 100 + 10;
const int MOD = 100000000;

struct BigNum
{
	int a[MAXN],len;
	BigNum(){memset(a,0,sizeof(a));len=1;}
} f[MAXN];


void Print(BigNum A);

BigNum Minus(BigNum A,BigNum B)
{
	BigNum res;
	res.len=max(A.len,B.len);
	for(int i=1;i<=res.len;i++) 
		res.a[i]=A.a[i]-B.a[i];
	for(int i=1;i<=res.len;i++)
	{
		if(res.a[i]<0) res.a[i]+=MOD,--res.a[i+1];
	}
	for(;res.len>0;) if(!res.a[res.len]) --res.len;else break;
	if(!res.len) res.len=1;
	return res;
}

BigNum Multi(BigNum A,int c)
{
	BigNum res;
	res.len=A.len;
	for(int i=1;i<=res.len;i++)
	{
		res.a[i]=A.a[i]*c;
	}
	for(int i=1;i<=res.len;i++)
	{
		res.a[i+1]+=res.a[i]/MOD;
		res.a[i]%=MOD;
		while(res.a[res.len+1]) ++res.len;
	}
	return res;
}

BigNum PlusTwo(BigNum A)
{
	BigNum res;
	res.len=A.len;
	for(int i=1;i<=res.len;i++)
	{
		res.a[i]=A.a[i];
	}
	res.a[1]+=2;
	for(int i=1;i<=res.len;i++)
	{
		res.a[i+1]+=res.a[i]/MOD;
		res.a[i]%=MOD;
		while(res.a[res.len+1]) ++res.len;
	}
	return res;
}

int n;

void Print(BigNum A)
{
	printf("%d",A.a[A.len]);
	for(int i=A.len-1;i;i--) printf("%08d",A.a[i]);
	printf("\n");
}

int main()
{
	scanf("%d",&n);
	f[1].a[1]=1;f[2].a[1]=5;f[1].len=f[2].len=1;
	for(int i=3;i<=n;i++) f[i]=PlusTwo(Minus(Multi(f[i-1],3),f[i-2]));
	Print(f[n]);
	
	return 0;
}
