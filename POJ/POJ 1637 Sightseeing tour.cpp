#include <iostream>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <algorithm>
#include <cmath>

using namespace std;

const int MAXN = 200 + 10;
const int MAXM = 3000 + 10;
const int INF = 0x7FFFFFFF >> 2;

struct Edge
{
	int next, to, w;
} g[MAXM];
int gn, start[MAXN], now[MAXN];

inline void AddEdge(int a, int b, int c)
{
	gn++; g[gn].next = start[a]; start[a] = gn; g[gn].to = b; g[gn].w = c;
	gn++; g[gn].next = start[b]; start[b] = gn; g[gn].to = a; g[gn].w = 0;
}

int tst;
int n, m, ind[MAXN], outd[MAXN], d[MAXN], S, T, h[MAXN], vh[MAXN], ans, N;

int Aug(int p, int flow)
{
	if (p == T) return flow;
	int ret = 0;
	for (int i = now[p]; i; now[p] = i = g[i].next)
	{
		int v = g[i].to;
		if (g[i].w > 0 && h[p] == h[v] + 1)
		{
			int tmp = Aug(v, min(g[i].w, flow - ret));
			ret += tmp;
			g[i].w -= tmp;
			g[i ^ 1].w += tmp;
			if (ret == flow) return flow;
		}
	}
	--vh[h[p]]; if (!vh[h[p]]) h[S] = N;
	++h[p]; ++vh[h[p]]; now[p] = start[p];
	return ret;
}

void Init()
{
	gn = 1; ans = 0;
	memset(start, 0, sizeof(start));
	memset(h, 0, sizeof(h));
	memset(vh, 0, sizeof(vh));
	memset(ind, 0, sizeof(ind));
	memset(outd, 0, sizeof(outd));
	scanf("%d%d", &n, &m);
	for (int a, b, c, i = 1; i <= m; ++i)
	{
		scanf("%d%d%d", &a, &b, &c);
		++ind[b]; ++outd[a];
		if (c == 0) AddEdge(a, b, 1);
	}
}

void Solve()
{
	for (int i = 1; i <= n; ++i) d[i] = outd[i] - ind[i];
	for (int i = 1; i <= n; ++i) 
		if (d[i] % 2 != 0) {puts("impossible"); return;}
		else d[i] /= 2;
	S = n + 1; T = S + 1; N = T;
	for (int i = 1; i <= n; ++i) 
		if (d[i] > 0) AddEdge(S, i, d[i]), ans += d[i];
		else AddEdge(i, T, -d[i]);
	vh[0] = N;
	for (int i = 1; i <= N; ++i) now[i] = start[i];
	while (h[S] < N) ans -= Aug(S, INF);
	if (ans == 0) puts("possible"); else puts("impossible");
}

int main()
{
	scanf("%d", &tst);
	while (tst--)
	{
		Init();
		Solve();
	}
	
	return 0;
}
