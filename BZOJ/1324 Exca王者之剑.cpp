#include <iostream>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <cmath>
#include <fstream>
#include <algorithm>

using namespace std;

const int MAXC = 100 + 10;
const int MAXN = 10000 + 10;
const int MAXM = 200000 + 10;
const int INF = 0x7FFFFFFF >> 2;
const int gx[4] = {-1, 0, 1, 0};
const int gy[4] = {0, -1, 0, 1};

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

int n, m, N, S, T, h[MAXN], vh[MAXN], val[MAXC][MAXC], ans;

int Aug(int p, int flow)
{
	if (p == T) return flow;
	int ret = flow, minnode = N - 1;
	for (int i = start[p]; i; i = g[i].next) if (g[i].w > 0)
	{
		int v = g[i].to;
		if (h[v] + 1 == h[p])
		{
			int tmp = Aug(v, min(g[i].w, ret));
			ret -= tmp;
			g[i].w -= tmp;
			g[i ^ 1].w += tmp;
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

inline int f(int i, int j)
{
	return (i - 1) * m + j;
}

int main()
{
	gn = 1;
	scanf("%d%d", &n, &m);
	for (int i = 1; i <= n; ++i) 
		for (int j = 1; j <= m; ++j) scanf("%d", &val[i][j]), ans += val[i][j];
	S = f(n, m) + 1; T = S + 1; N = T;
	for (int i = 1; i <= n; ++i) 
		for (int j = 1; j <= m; ++j) if ((i + j) & 1)
		{
			AddEdge(S, f(i, j), val[i][j]);
			for (int k = 0; k < 4; ++k) 
			{
				int x = i + gx[k], y = j + gy[k];
				if (x > 0 && x <= n && y > 0 && y <= m) AddEdge(f(i, j), f(x, y), INF);
			}
		}
		else AddEdge(f(i, j), T, val[i][j]);
	vh[0] = N;
	while (h[S] < N) ans -= Aug(S, INF);
	printf("%d\n", ans);
	
	return 0;
}
