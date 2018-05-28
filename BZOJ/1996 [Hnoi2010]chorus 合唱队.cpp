#include <iostream>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <algorithm>

using namespace std;

const int MAXN = 1010;
const int MOD = 19650827;

int n;
int h[MAXN];
int f[MAXN][MAXN][3];

int Solve(int l,int r,int last)
{
	if(f[l][r][last]!=-1) return f[l][r][last];
	int re=0;
	if(last==1)
	{
		if(h[l]<h[r]) re+=Solve(l+1,r,2);
		re%=MOD;
		if(h[l]<h[l+1]) re+=Solve(l+1,r,1);
		re%=MOD;
	}
	else 
	{
		if(h[r]>h[r-1]) re+=Solve(l,r-1,2);re%=MOD;
		if(h[r]>h[l]) re+=Solve(l,r-1,1);re%=MOD;
	}
	f[l][r][last]=re;
	return re;
}

int main()
{
	scanf("%d",&n);
	for(int i=1;i<=n;i++) scanf("%d",&h[i]);	
	memset(f,-1,sizeof(f));
	for(int i=2;i<=n;i++)
		if(h[i]>h[i-1]) f[i-1][i][1]=f[i-1][i][2]=1;
		else f[i-1][i][1]=f[i-1][i][2]=0;
	if(n!=1) printf("%d\n",(Solve(1,n,1)+Solve(1,n,2))%MOD);
	else printf("1\n");
	
	return 0;
}
