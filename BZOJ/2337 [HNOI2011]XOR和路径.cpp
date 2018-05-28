#include <iostream>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <cmath>
#include <algorithm>

using namespace std;

const int MAXN = 100 + 10;
const int MAXM = 10000 + 10;
const double eps = 1e-13;

struct Edge
{
	int next, to, w;
} g[MAXM * 2];
int gn, start[MAXN];

inline void AddEdge(int a, int b, int c)
{
	gn++; g[gn].next = start[a]; start[a] = gn; g[gn].to = b; g[gn].w = c;
}

int n, m, d[MAXN];
double a[MAXN][MAXN], ans, x[MAXN];

int checkdouble(double x)
{
	if (fabs(x) < eps) return 0;
	return 1;
}

double solve(int sx)
{
	for (int i = 1; i <= n + 1; ++i) 
		for (int j = 1; j <= n + 1; ++j) a[i][j] = 0.0;
	for (int p = 1; p < n; ++p)
	{
		a[p][p] = 1.0;
		for (int i = start[p]; i; i = g[i].next)
		{
			int v = g[i].to;
			if (g[i].w & sx) a[p][n + 1] += 1.0 / d[p], a[p][v] += 1.0 / d[p];
			else a[p][v] -= 1.0 / d[p];
		}
	}
	a[n][n + 1] = 0.0;
	a[n][n] = 1.0;
	for (int j, i = 1; i <= n; ++i)
	{
		for (j = i; !checkdouble(a[j][i]); ++j);
		for (int k = i; k <= n + 1; ++k) swap(a[i][k], a[j][k]);
		for (j = i + 1; j <= n; ++j)
		{
			double dx = a[j][i] / a[i][i];
			if (!checkdouble(a[j][i])) continue;
			for (int k = i; k <= n + 1; ++k) a[j][k] -= a[i][k] * dx;
		}
	}
	for (int i = n; i; --i)
	{
		x[i] = a[i][n + 1];
		for (int j = i + 1; j <= n; ++j) x[i] -= a[i][j] * x[j];
		x[i] /= a[i][i];
	}
	return x[1];
}

int main()
{
	scanf("%d%d", &n, &m);
	for (int a, b, c, i = 1; i <= m; ++i)
	{
		scanf("%d%d%d", &a, &b, &c);
		AddEdge(a, b, c); ++d[a]; 
		if (a != b) {AddEdge(b, a, c); ++d[b];}
	}
	for (int i = 0; i < 30; ++i) ans += solve(1 << i) * (1 << i);
	printf("%.3lf\n", ans);
	
	return 0;
}
