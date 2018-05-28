#include <iostream>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <cmath>
#include <algorithm>
#include <fstream>

using namespace std;

const int MAXN = 15;
const double INF = 1e10;

int n, m, k;
double sumb;
double a[MAXN][MAXN], sum[MAXN][MAXN];
double f[MAXN][MAXN][MAXN][MAXN][MAXN];

double DP(int x1, int x2, int y1, int y2, int t)
{
	double &res = f[x1][x2][y1][y2][t];
	if (res < INF) return res;
	if (t == 0) 
	{
		res = sum[x2][y2] - sum[x1 - 1][y2] - sum[x2][y1 - 1] + sum[x1 - 1][y1 - 1] - sumb;
		res = res * res;
		return res;	
	}
	for (int x = x1; x < x2; ++x) 
		for (int j = 0; j < t; ++j) res = min(res, DP(x1, x, y1, y2, j) + DP(x + 1, x2, y1, y2, t - j - 1));
	for (int y = y1; y < y2; ++y)
		for (int j = 0; j < t; ++j) res = min(res, DP(x1, x2, y1, y, j) + DP(x1, x2, y + 1, y2, t - j - 1));
	return res;
}

int main()
{
	scanf("%d%d%d", &n, &m, &k);
	for (int i = 1; i <= n; ++i)
		for (int j = 1; j <= m; ++j) scanf("%lf", &a[i][j]);
	for (int i = 1; i <= n; ++i)
		for (int j = 1; j <= m; ++j) sum[i][j] = sum[i - 1][j] + sum[i][j - 1] - sum[i - 1][j - 1] + a[i][j];
	sumb = sum[n][m] / k;
	for (int x1 = 1; x1 <= n; ++x1)
		for (int x2 = 1; x2 <= n; ++x2)
			for (int y1 = 1; y1 <= m; ++y1)
				for (int y2 = 1; y2 <= m; ++y2) 
					for (int i = 0; i <= k; ++i) f[x1][x2][y1][y2][i] = INF;
	printf("%.2lf\n", sqrt(DP(1, n, 1, m, k - 1) / k));
	
	
	return 0;
}
