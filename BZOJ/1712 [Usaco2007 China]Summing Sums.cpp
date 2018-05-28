/*
DATE : 2013-5-25 
RATING : 3
TAG : dp + Matrix
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

const int MAXN = 50000 + 10;
const int MOD = 98765431;

struct Matrix
{
	long long a[5][5];
	Matrix() {memset(a,0,sizeof(a));}
};

Matrix Multi(Matrix A,Matrix B)
{
	Matrix C;
	for(int i=1;i<=3;i++) 
		for(int j=1;j<=3;j++) 
			for(int k=1;k<=3;k++) 
				C.a[i][j]=(C.a[i][j]+A.a[i][k]*B.a[k][j]%MOD)%MOD;
	return C;
}

Matrix QuickPow(Matrix A,int t)
{
	Matrix res;
	if(t==1) return A;
	res=QuickPow(A,t/2);
	res=Multi(res,res);
	if(t&1) res=Multi(A,res);
	return res;
}

int n,T;
long long sum;
long long a[MAXN],ans[MAXN];
Matrix Base1;

int main()
{
	scanf("%d%d",&n,&T);
	for(int i=1;i<=n;i++) scanf("%lld",&a[i]),sum=(sum+a[i])%MOD;
	Base1.a[1][1]=n-1;Base1.a[2][1]=1;Base1.a[3][2]=n-1;Base1.a[3][3]=-1;
	Matrix Tmp;
	Tmp=QuickPow(Base1,T);
	Base1.a[1][1]=1;Base1.a[1][2]=1-n;Base1.a[1][3]=1;
	Tmp=Multi(Base1,Tmp);
	long long j=Tmp.a[1][1];
	int k=(T&1) ? 1 : -1;
	for(int i=1;i<=n;i++) ans[i]=((j*(long long)a[i])%MOD+(j+k)*(long long)(sum-a[i])%MOD)%MOD;
	for(int i=1;i<=n;i++) printf("%lld\n",(ans[i]+MOD)%MOD);
	
	return 0;
}
