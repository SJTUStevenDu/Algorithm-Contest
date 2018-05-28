#include <iostream>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <cmath>
#include <algorithm>
#include <fstream>

using namespace std;

const int MAXN = 1000 + 20;
const int BASE = 1000000;

int m,n,d[MAXN],sum;

struct BigNum
{
	int a[505];
	int len;
	BigNum() {len=1;memset(a,0,sizeof(a));}
};

BigNum Mul(BigNum A,int B)
{
	BigNum C;
	int lena=A.len;
	int lenc=lena;
	for(int i=1;i<=lena;i++) C.a[i]=A.a[i]*B;
	for(int i=1;i<=lenc;i++)
	{
		C.a[i+1]+=C.a[i]/BASE;
		C.a[i]%=BASE;
		if(C.a[lenc+1]) lenc++;
	}
	C.len=lenc;
	return C;
}

BigNum Div(BigNum A,int x)
{
	int lena=A.len,res=0,lenc=0;
	BigNum C;
	for(int i=lena;i;i--)
	{
		res*=BASE;res+=A.a[i];
		if(res<x && i==lena) continue;
		C.a[++lenc]=res/x;res%=x;
	}
	for(int i=1;i<=lenc/2;i++) swap(C.a[i],C.a[lenc-i+1]);
	C.len=lenc;
	return C;
}

void Print(BigNum A)
{
	printf("%d",A.a[A.len]);
	for(int i=A.len-1;i;i--) printf("%06d",A.a[i]);
	printf("\n");
}

int main()
{
	scanf("%d",&n);
	if (n == 1)
	{
		int x;
		scanf("%d", &x);
		if (x == 0) puts("1");
		else puts("0");
		return 0;
	}
	for(int x, i = 1; i <= n; ++i)
	{
		scanf("%d",&x);
		x--; d[++m] = x; sum += x;
		if (d[i] <= -1 && i != 1) 
		{
			puts("0");
			return 0;
		}
	}
	if (sum != n - 2)
	{
		puts("0");
		return 0;
	}
	BigNum ans;
	ans.a[1]=1;
	for(int i=2;i<=n-2;i++) ans=Mul(ans,i);
	for(int i=1;i<=m;i++)
		for(int j=2;j<=d[i];j++) ans=Div(ans,j);
	Print(ans);
	
	return 0;
}
