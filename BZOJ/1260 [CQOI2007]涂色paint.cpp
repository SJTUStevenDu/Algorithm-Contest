#include <iostream>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <cmath>
#include <algorithm>
#include <fstream>

using namespace std;

const int MAXN = 100 + 10;
const int INF = 0x7FFFFFFF>>2;

char c[MAXN];
int dp[MAXN][MAXN];
int n;

inline int checkmin(int &x,int y) {if(x>y) x=y;}

int dfs(int l,int r)
{
	if(~dp[l][r]) return dp[l][r];
	if(l==r) return dp[l][r]=1;
	if(l>r) return dp[l][r]=0;
	int res=INF;
	if(c[l]==c[r]) checkmin(res,dfs(l+1,r-1)+1);
	for(int i=l;i<r;i++) checkmin(res,dfs(l,i)+dfs(i+1,r));
	if(c[l]!=c[r]) return dp[l][r]=res;
	for(int i=l+1;i<r;i++) if(c[i]==c[l]) checkmin(res,dfs(l,i)+dfs(i+1,r-1));
	return dp[l][r]=res;
}

int main()
{
	memset(dp,-1,sizeof(dp));
	scanf("%s",c);
	n=strlen(c)-1;
	printf("%d\n",dfs(0,n));
	
	return 0;
}
