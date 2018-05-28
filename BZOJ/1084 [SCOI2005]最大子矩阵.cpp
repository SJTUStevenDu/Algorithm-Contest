#include <iostream>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <cmath>
#include <algorithm>
#include <fstream>

using namespace std;

const int MAXN = 100 + 10;
const int MAXK = 10 + 10;

int dp[MAXK][MAXN][MAXN];
int n, m, k, ans;
int a[MAXN][3], s[MAXN],s1[MAXN],s2[MAXN];

int main()
{
	scanf("%d%d%d", &n, &m, &k);
	if (m == 1)
	{
		for (int i = 1; i <= n; ++i) scanf("%d", &s[i]);
		for (int i = 1; i <= n; ++i) s[i] += s[i - 1];
		for (int z = 1; z <= k; ++z)
			for (int i = 1; i <= n; ++i)
			{
				dp[z][i][0] = dp[z][i - 1][0];
				for (int j = 0; j < i; ++j) dp[z][i][0] = max(dp[z][i][0], dp[z - 1][j][0] + s[i] - s[j]);
			}	
		printf("%d\n", dp[k][n][0]);
		return 0;
	}
	for (int i = 1; i <= n; ++i)
		for (int j = 1; j <= m; ++j) scanf("%d", &a[i][j]);
	for (int i = 1; i <= n; ++i) s1[i] = s1[i - 1] + a[i][1];
	for (int i = 1; i <= n; ++i) s2[i] = s2[i - 1] + a[i][2];
	for (int i = 1; i <= n; ++i) s[i] = s1[i] + s2[i];
	for (int z = 1; z <= k; ++z)
		for (int i = 1; i <= n; ++i)
			for (int j = 1; j <= n; ++j)
			{
				dp[z][i][j] = max(dp[z][i - 1][j], dp[z][i][j - 1]);
				for (int x = 0; x < i; ++x) dp[z][i][j] = max(dp[z][i][j], dp[z - 1][x][j] + s1[i] - s1[x]);
				for (int x = 0; x < j; ++x) dp[z][i][j] = max(dp[z][i][j], dp[z - 1][i][x] + s2[j] - s2[x]);
				if (i == j)
					for (int x = 0; x < i; ++x) dp[z][i][j] = max(dp[z][i][j], dp[z - 1][x][x] + s[i] - s[x]);
			}
	printf("%d\n", dp[k][n][n]);
	
	return 0;
}
