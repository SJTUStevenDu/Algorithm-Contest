#include <iostream>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <cmath>
#include <algorithm>
#include <fstream>

using namespace std;

const int MAXN = 16;
const int MAXC = 6;
const int MOD = 1000000007;

long long dp[MAXN][MAXN][MAXN][MAXN][MAXN][MAXC];
int n, x, D[MAXC];

long long DP(int a1, int a2, int a3, int a4, int a5, int v)
{
	if (~dp[a1][a2][a3][a4][a5][v]) return dp[a1][a2][a3][a4][a5][v];
	long long ret = 0;
	if (a1 == 0 && a2 == 0 && a3 == 0 && a4 == 0 && a5 == 0) return ret = 1;
	if (a1) ret = (ret + (a1 - (v == 2)) * DP(a1 - 1, a2, a3, a4, a5, 1)) % MOD;
	if (a2) ret = (ret + (a2 - (v == 3)) * DP(a1 + 1, a2 - 1, a3, a4, a5, 2)) % MOD;
	if (a3) ret = (ret + (a3 - (v == 4)) * DP(a1, a2 + 1, a3 - 1, a4, a5, 3)) % MOD;
	if (a4) ret = (ret + (a4 - (v == 5)) * DP(a1, a2, a3 + 1, a4 - 1, a5, 4)) % MOD;
	if (a5) ret = (ret + a5 * DP(a1, a2, a3, a4 + 1, a5 - 1, 5)) % MOD;
	return dp[a1][a2][a3][a4][a5][v] = ret;
}

int main()
{
	scanf("%d", &n);
	memset(dp, -1, sizeof(dp));
	for (int i = 1; i <= n; ++i) scanf("%d", &x), D[x]++;
	printf("%d\n", DP(D[1], D[2], D[3], D[4], D[5], 0));
	
	return 0;
}
