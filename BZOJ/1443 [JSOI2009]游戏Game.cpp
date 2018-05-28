#include <iostream>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <cmath>
#include <fstream>
#include <algorithm>

using namespace std;

const int MAXN = 10000 + 10;
const int MAXM = 800000 + 10;
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

int n, m, N, S, T;
bool map[MAXN], vis[MAXN], avl[MAXN], ans = false;
int h[MAXN], vh[MAXN];

inline int f(int i, int j) {return (i - 1) * m + j;}

int Aug(int p, int flow)
{
	if (p == T) return flow;
	int ret = flow, minnode = N - 1;
	for (int i = start[p]; i; i = g[i].next) if (g[i].w)
	{
		int v = g[i].to;
		if (h[p] == h[v] + 1)
		{
			int tmp = Aug(v, min(g[i].w, ret));
			g[i].w -= tmp;
			g[i ^ 1].w += tmp;
			ret -= tmp;
			if (ret == 0 || h[S] >= N) return flow - ret;
		}
		if (g[i].w) minnode = min(minnode, h[v]);
	}
	if (flow == ret)
	{
		--vh[h[p]];
		if (vh[h[p]] == 0) h[S] = N;
		++vh[h[p] = minnode + 1];
	}
	return flow - ret;
}

void dfs(int p, int flag)
{
	vis[p] = 1;
	if (((p - 1) / m + (p - 1) % m) % 2 == flag) avl[p] = 1;
	for (int i = start[p]; i; i = g[i].next) 
	{
		int v = g[i].to;
		if (g[i].w == flag && !vis[v]) dfs(v, flag);
	}
}

char SS[200];

int main()
{
	gn = 1;
	scanf("%d%d", &n, &m);
	for (int i = 1; i <= n; ++i) 
	{
		scanf("%s", SS + 1);
		for (int j = 1; j <= m; ++j) map[f(i, j)] = (SS[j] == '.');
	}
	N = n * m + 2; T = N; S = N - 1;
	for (int i = 1; i <= n; ++i) 
		for (int j = 1; j <= m; ++j) if (map[f(i, j)])
		{
			if ((i + j) & 1)
			{
				AddEdge(S, f(i, j), 1);
				if (i > 1 && map[f(i - 1, j)]) AddEdge(f(i, j), f(i - 1, j), 1);
				if (j > 1 && map[f(i, j - 1)]) AddEdge(f(i, j), f(i, j - 1), 1);
				if (i < n && map[f(i + 1, j)]) AddEdge(f(i, j), f(i + 1, j), 1);
				if (j < m && map[f(i, j + 1)]) AddEdge(f(i, j), f(i, j + 1), 1);
			} 
			else AddEdge(f(i, j), T, 1);
		}
	vh[0] = N;
	while (h[S] < N) Aug(S, INF);
	memset(vis, 0, sizeof(vis));
	dfs(S, 1);
	memset(vis, 0, sizeof(vis));
	dfs(T, 0);
	for (int i = 1; i < S; ++i) if (avl[i]) ans = true;
	if (ans) puts("WIN");
	else puts("LOSE");
	for (int i = 1; i <= n; ++i)
		for (int j = 1; j <= m; ++j) if (avl[f(i, j)]) printf("%d %d\n", i, j);
	return 0;
}
