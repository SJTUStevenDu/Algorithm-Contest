#include <iostream>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <cmath>
#include <fstream>
#include <algorithm>

using namespace std;

const int MAXN = 50 + 10;
const int MAXM = 6000 + 10;
const int INF = 0x7FFFFFFF >> 2;

struct Edge
{
	int next, to, w;
} g[MAXM];
int gn, start[MAXN];

inline void AddEdge(int a, int b, int c)
{
	gn++; g[gn].next = start[a]; start[a] = gn; g[gn].to = b; g[gn].w = c;
	gn++; g[gn].next = start[b]; start[b] = gn; g[gn].to = a; g[gn].w = 0;
}

char map[MAXN][MAXN];
int n, S, T, N, h[MAXN], vh[MAXN], a1, a2, an, b1, b2, bn, ans;

int Aug(int p, int flow)
{
	if (p == T) return flow;
	int minnode = N - 1, ret = flow;
	for (int i = start[p]; i; i = g[i].next) if (g[i].w > 0)
	{
		int v = g[i].to;
		if (h[v] + 1 == h[p])
		{
			int tmp = Aug(v, min(g[i].w, ret));
			ret -= tmp;
			g[i].w -= tmp;
			g[i ^ 1]. w += tmp;
			if (ret == 0 || h[S] >= N) return flow - ret;
		}
		if (g[i].w > 0) minnode = min(minnode, h[v]);
	}
	if (flow == ret)
	{
		--vh[h[p]];
		if (vh[h[p]] == 0) h[S] = N;
		vh[h[p] = minnode + 1]++;
	}
	return flow - ret;
}

int main()
{
	while (~scanf("%d", &n))
	{
		scanf("%d%d%d%d%d%d", &a1, &a2, &an, &b1, &b2, &bn);
		++a1; ++a2; ++b1; ++b2;
		for (int i = 1; i <= n; ++i) scanf("%s", map[i] + 1);
		ans = 0;
		S = n + 1; T = S + 1; N = T;
		gn = 1;
		memset(start, 0, sizeof(start));
		memset(h, 0, sizeof(h));
		memset(vh, 0, sizeof(vh));
		vh[0] = N;
		for (int i = 1; i <= n; ++i)
			for (int j = 1; j <= n; ++j)
				if (map[i][j] == 'N') AddEdge(i, j, INF);
				else if (map[i][j] == 'O') AddEdge(i, j, 1);
		AddEdge(S, a1, an); AddEdge(a2, T, an);
		AddEdge(S, b1, bn); AddEdge(b2, T, bn);
		while (h[S] < N) ans += Aug(S, INF);
		if (ans < an + bn)
		{
			puts("No");
			continue;
		}
		ans = 0;
		gn = 1;
		memset(start, 0, sizeof(start));
		memset(h, 0, sizeof(h));
		memset(vh, 0, sizeof(vh));
		vh[0] = N;
		for (int i = 1; i <= n; ++i)
			for (int j = 1; j <= n; ++j)
				if (map[i][j] == 'N') AddEdge(i, j, INF);
				else if (map[i][j] == 'O') AddEdge(i, j, 1);
		AddEdge(S, a1, an); AddEdge(a2, T, an);
		AddEdge(S, b2, bn); AddEdge(b1, T, bn);
		while (h[S] < N) ans += Aug(S, INF);
		if (ans < an + bn)
		{
			puts("No");
			continue;
		}
		puts("Yes");
	}
	
	return 0;
}
