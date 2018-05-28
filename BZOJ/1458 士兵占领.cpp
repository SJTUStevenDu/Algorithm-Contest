#include <iostream>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <cmath>
#include <fstream>
#include <algorithm>

using namespace std;

const int MAXN = 200 + 10;
const int MAXM = 30000 + 10;
const int INF = 0x7FFFFFFF >> 2;

struct Edge
{
	int next, to, w;
} g[MAXM];
int gn = 1, start[MAXN];

inline void AddEdge(int a, int b, int c)
{
	gn++; g[gn].next = start[a]; start[a] = gn; g[gn].to = b; g[gn].w = c;
	gn++; g[gn].next = start[b]; start[b] = gn; g[gn].to = a; g[gn].w = 0;
}

bool able[MAXN][MAXN];
int n, m, c1[MAXN], c2[MAXN], h[MAXN], vh[MAXN], S, T, k, ans, N;

bool check()
{
	int re;
	for (int i = 1; i <= n; ++i)
	{
		re = 0;
		for (int j = 1; j <= m; ++j) if (!able[i][j]) re++;
		if (re < c1[i]) return false;
		c1[i] = re - c1[i];
	}
	for (int i = 1; i <= m; ++i)
	{
		re = 0;
		for (int j = 1; j <= n; ++j) if (!able[j][i]) re++;
		if (re < c2[i]) return false;
		c2[i] = re - c2[i];
	}
	return true;
}

int Aug(int p, int flow)
{
	if (p == T) return flow;
	int minnode = N - 1, ret = 0;
	for (int i = start[p]; i; i = g[i].next) if (g[i].w)
	{
		int v = g[i].to;
		if (h[v] + 1 == h[p])
		{
			int tmp = Aug(v, min(flow - ret, g[i].w));
			ret += tmp;
			g[i].w -= tmp;
			g[i ^ 1].w += tmp;
			if (h[S] == N || ret == flow) return flow;
		}
		minnode = min(minnode, h[v]);
	}
	if (ret == 0)
	{
		--vh[h[p]];
		if (!vh[h[p]]) h[S] = N;
		h[p] = minnode + 1;
		vh[h[p]]++;
	}
	return ret;
}

int main()
{
	scanf("%d%d%d", &n, &m, &k);
	for (int i = 1; i <= n; ++i) scanf("%d", &c1[i]);
	for (int i = 1; i <= m; ++i) scanf("%d", &c2[i]);
	while (k--)
	{
		int x, y;
		scanf("%d%d", &x, &y);
		if (!able[x][y]) --ans, able[x][y] = 1;
	}
	if (!check())
	{
		puts("JIONG!");
		return 0;
	}
	ans += n * m;
	N = n + m + 2; T = N; S = T - 1;
	for (int i = 1; i <= n; ++i) AddEdge(S, i, c1[i]);
	for (int i = 1; i <= m; ++i) AddEdge(i + n, T, c2[i]);
	for (int i = 1; i <= n; ++i)
		for (int j = 1; j <= m; ++j) if (!able[i][j]) AddEdge(i, j + n, 1);
	vh[0] = N;
	while (h[S] < N) ans -= Aug(S, INF);
	printf("%d\n", ans);
	
	return 0;
}
