#include <iostream>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <cmath>
#include <algorithm>
#include <fstream>

using namespace std;

const int MAXN = 2000 + 10;

int dp[MAXN][MAXN], dpmax[MAXN], a[MAXN][MAXN];
int n, m, d, x, y;

inline void checkmax(int &x, int y)
{
	if (x < y) x = y;
}

int main()
{
	scanf("%d%d%d", &n, &m, &d);
	for (int i = 1; i <= n; ++i) 
	{
		scanf("%d", &x);
		for (int j = 1; j <= x; ++j) scanf("%d", &y), a[y][i]++;
	}
	for (int i = 1; i <= n; ++i)
	{
		dp[m][i] = a[m][i];
		checkmax(dpmax[m], dp[m][i]);
	}
	for (int i = m - 1; i >= 0; --i)
		for (int j = 1; j <= n; ++j)
		{
			dp[i][j] = dp[i + 1][j] + a[i][j];
			checkmax(dp[i][j], dpmax[i + d] + a[i][j]);
			checkmax(dpmax[i], dp[i][j]);
		}
	printf("%d\n", dpmax[0]);
	
	return 0;
}
