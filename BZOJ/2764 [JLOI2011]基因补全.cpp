/*
DATE : 2013-2-12 
RATING : 2
TAG : DP
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

//Orz WJMZBMR && sevenkplus

using namespace std;

const int MAXN = 2000 + 5;
const int MOD = 100000000;

struct BIGNUM
{
	int a[100];
	int len;
	BIGNUM(){memset(a,0,sizeof(a));len=0;}
} dp[2][MAXN];

void Plus(BIGNUM &A,BIGNUM B)
{
	A.len=max(A.len,B.len);
	for(int i=1;i<=A.len;i++) A.a[i]+=B.a[i];
	for(int i=1;i<=A.len;i++)
	{
		A.a[i+1]+=A.a[i]/MOD;
		A.a[i]%=MOD;
		if(A.a[A.len+1]) A.len++;
	}
}

int n,m;
char s[MAXN],t[MAXN];

int main()
{
	scanf("%d%d",&n,&m);
	scanf("%s%s",s+1,t+1);
	for(int i=1;i<=m;i++)
	{
		if(t[i]=='A') t[i]='T';
		else if(t[i]=='C') t[i]='G';
		else if(t[i]=='G') t[i]='C';
		else t[i]='A';
	}
	int tag=0;
	for(int i=0;i<=n;i++) dp[tag][i].len=dp[tag][i].a[1]=1;
	for(int i=1;i<=m;i++) 
	{
		tag^=1;
		memset(dp[tag],0,sizeof(dp[tag]));
		for(int j=1;j<=n;j++)
		{
			dp[tag][j]=dp[tag][j-1];
			if(s[j]==t[i]) Plus(dp[tag][j],dp[tag^1][j-1]);
		}
	}
	BIGNUM A=dp[tag][n];
	printf("%d",A.a[A.len]);
	for(int i=A.len-1;i;i--) printf("%08d",A.a[i]);
	printf("\n");
	
	return 0;
}
