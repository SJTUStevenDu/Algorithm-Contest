#include <iostream>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <cmath>
#include <fstream>
#include <algorithm>

using namespace std;

const int MAXN = 50 + 10;

struct Edge
{
	int next, to;
} g[MAXN * 2];
int gn, start[MAXN];

inline void AddEdge(int a, int b)
{
	gn++; g[gn].next = start[a]; start[a] = gn; g[gn].to = b;
}

int n, k1, k2, father[MAXN];
double w[MAXN], f[MAXN][MAXN][MAXN], ss[MAXN], INF;

inline void checkmin(double &x, double y) {if (x > y) x = y;}

void dfs(int p)
{
	for (int i = start[p]; i; i = g[i].next)
	{
		int v = g[i].to;
		if (v == father[p]) continue;
		father[v] = p;
		dfs(v);
	}
	ss[p] = INF;
	for (int j = k1; j <= k2; ++j)
	{
		for (int i = 1; i <= k2; ++i) f[p][j][i] = INF;
		f[p][j][1] = w[p] / j;
		for (int i = start[p]; i; i = g[i].next)
		{
			int v = g[i].to;
			if (v == father[p]) continue;
			for (int k = j; k; --k)
			{
				f[p][j][k] += ss[v];
				for (int l = 1; l < k; ++l) checkmin(f[p][j][k], f[p][j][l] + f[v][j][k - l]);
			}
		}
		checkmin(ss[p], f[p][j][j]);
	}
}

int main()
{
	scanf("%d%d%d", &n, &k1, &k2);
	for (int i = 1; i <= n; ++i) scanf("%lf", &w[i]);
	for (int a, b, i = 1; i < n; ++i)
	{
		scanf("%d%d", &a, &b);
		AddEdge(a, b); AddEdge(b, a);
	}
	for (int i = 1; i <= n; ++i) INF += w[i] * 2;
	dfs(1);
	printf("%.2lf\n", ss[1]);
	
	return 0;
}
