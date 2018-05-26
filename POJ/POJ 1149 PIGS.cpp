#include <iostream>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <algorithm>
#include <cmath>

using namespace std;

const int MAXN = 100 + 10;
const int MAXM = 1000 + 10;
const int MAXE = 300000 + 10;
const int INF = 0x7FFFFFFF >> 2;

struct Edge
{
	int next, to, w;
} g[MAXE];
int gn, start[MAXN], now[MAXN];

inline void AddEdge(int a, int b, int c)
{
	gn++; g[gn].next = start[a]; start[a] = gn; g[gn].to = b; g[gn].w = c;
	gn++; g[gn].next = start[b]; start[b] = gn; g[gn].to = a; g[gn].w = 0;
}

int n, m, ans, S, T, h[MAXN], vh[MAXN], N;
int val[MAXN], xx[MAXM][MAXN], bas[MAXM];

int Aug(int p, int flow)
{
	if (p == T) return flow;
	int ret = flow;
	for (int i = now[p]; i; now[p] = i = g[i].next)
	{	
		int v = g[i].to;
		if (g[i].w > 0 && h[p] == h[v] + 1)
		{
			int tmp = Aug(v, min(ret, g[i].w));
			ret -= tmp;
			g[i].w -= tmp;
			g[i ^ 1].w += tmp;
			if (ret == 0) return flow - ret;
		}
	}
	--vh[h[p]]; if (vh[h[p]] == 0) h[S] = N;
	++h[p]; ++vh[h[p]]; now[p] = start[p];
	return flow - ret;
}

int main()
{
	gn = 1;
	scanf("%d%d", &m, &n);
	for (int i = 1; i <= m; ++i) scanf("%d", &bas[i]);
	S = n + 1; T = n + 2; N = T;
	for (int i = 1; i <= n; ++i)
	{
		int num;
		scanf("%d", &num);
		for (int j = 1; j <= num; ++j)
		{
			int x;
			scanf("%d", &x);
			if (xx[x][0] == 0) val[i] += bas[x];
			++xx[x][0]; xx[x][xx[x][0]] = i;
		}
		scanf("%d", &num);
		AddEdge(i, T, num);
	}
	for (int i = 1; i <= n; ++i) if (val[i]) AddEdge(S, i, val[i]);
	for (int i = 1; i <= m; ++i) 
		for (int j = 1; j < xx[i][0]; ++j) AddEdge(xx[i][j], xx[i][j + 1], INF);
	for (int i = 1; i <= N; ++i) now[i] = start[i];
	vh[0] = N;	
	while (h[S] < N) ans += Aug(S, INF);
	printf("%d\n", ans);
	
	return 0;
}
