#include <iostream>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <cmath>
#include <algorithm>
#include <fstream>

using namespace std;

const int MAXN = 500 + 10;
const int INF = 0x7FFFFFFF>>2;
const double eps = 1e-15;

int n, m, f[MAXN][MAXN], g[MAXN][MAXN], ans;
double a[MAXN][2], b[MAXN][2], ab;

bool check(int j, int i)
{
	double x1, y1, x2, y2;
	x2 = a[i][0] - a[j][0];
	y2 = a[i][1] - a[j][1];
	for (int k = 1; k <= m; ++k)
	{
		x1 = b[k][0] - a[j][0];
		y1 = b[k][1] - a[j][1];
		if (x1 * y2 - x2 * y1 > eps) return false;
	}
	return true;
}

bool can(int j, int i)
{
	double x1, y1, x2, y2;
	if (abs(a[i][0] - a[j][0]) + abs(a[i][1] - a[j][1]) < eps) return false;
	x2 = a[i][0] - a[j][0];
	y2 = a[i][1] - a[j][1];
	for (int k = 1; k <= m; ++k)
	{
		x1 = b[k][0] - a[j][0];
		y1 = b[k][1] - a[j][1];
		if (abs(x1 * y2 - x2 * y1) > eps) return false;
		if (x1 * x2 + y1 * y2 < 0) return false;
		if (abs(x1) + abs(y1) > abs(x2) + abs(y2)) return false;
	}
	return true;
}

int main()
{
	scanf("%d%d", &n, &m);
	for (int i = 1; i <= n; ++i) scanf("%lf%lf%lf", &a[i][0], &a[i][1], &ab);
	for (int i = 1; i <= m; ++i) scanf("%lf%lf%lf", &b[i][0], &b[i][1], &ab);
	bool flag = true;
	for (int i = 1; i <= n; ++i)
	{
		flag = true;
		for (int k = 1; k <= m; ++k) if (abs(a[i][0] - b[k][0]) > eps || abs(a[i][1] - b[k][1]) > eps) {flag = false; break;}
		if (flag)
		{
			puts("1");
			return 0;
		}
	}
	for (int i = 1; i <= n; ++i)
		for (int j = 1; j < i; ++j) if (can(i, j)) 
		{
			puts("2");
			return 0;
		}
	for (int i = 1; i <= n; ++i)
		for (int j = 1; j <= n; ++j) f[i][j] = g[i][j] = INF;
	for (int i = 1; i <= n; ++i)
		for (int j = 1; j <= n; ++j) if (check(i, j)) f[i][j] = g[i][j] = 1;
	ans = INF;
	for (int k = 1; k <= n; ++k)
	{
		for (int i = 1; i < k; ++i)
			for (int j = 1; j < i; ++j) ans = min(ans, g[i][j] + f[j][k] + f[k][i]);
		for (int i = 1; i <= n; ++i)
			for (int j = 1; j <= n; ++j) f[i][j] = min(f[i][j], f[i][k] + f[k][j]);
	}
	if (ans == INF) puts("-1");
	else printf("%d\n", ans);
	
	return 0;
}
