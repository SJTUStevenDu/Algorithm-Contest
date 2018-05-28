#include <iostream>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <cmath>
#include <fstream>
#include <algorithm>

using namespace std;

const int MAXN = 2500 + 10;
const int MAXM = 50 + 10;

int dp[MAXN][MAXM][MAXM];
int T, m, n, sum[MAXM][MAXM];
char c;

inline int Query(int i, int j1, int j2)
{
	return max(sum[i][j2] - sum[i][j1 - 1], j2 - j1 + 1 - sum[i][j2] + sum[i][j1 - 1]);
}

int main()
{
	scanf("%d%d%d", &n, &m, &T);
	for (int i = 1; i <= n; ++i) 
	{
		for (; c != '0' && c != '1'; c = getchar());
		for (int j = 1; j <= m; ++j, c = getchar()) sum[i][j] = sum[i][j - 1] + c - '0';
	}
	for (int k = 1; k <= T; ++k)
		for (int i = 1; i <= n; ++i) 
		{
			dp[k][i][0] = dp[k][i - 1][m];
			for (int j = 1; j <= m; ++j) 
				for (int j1 = 0; j1 < j; ++j1) dp[k][i][j] = max(dp[k][i][j], dp[k - 1][i][j1] + Query(i, j1 + 1, j));
		}
	printf("%d\n", dp[T][n][m]);
	
	return 0;
}
