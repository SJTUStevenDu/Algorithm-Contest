#include <iostream>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <algorithm>
#include <cmath>

using namespace std;

const int MAXN = 400 + 10;
const int MAXM = 100000 + 10;
const int INF = 0x7FFFFFFF >> 2;
const long long INFL = 2000000000000LL;

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

int n, m, S, T, N, h[MAXN], vh[MAXN], xa[MAXN], xb[MAXN], flow, sum;
long long dist[MAXN][MAXN];

void Init()
{
	scanf("%d%d", &n, &m);
	S = 2 * n + 1; T = 2 * n + 2; N = T;
	for (int i = 1; i <= n; ++i) scanf("%d%d", &xa[i], &xb[i]);
	for (int i = 1; i <= n; ++i) 
		for (int j = i + 1; j <= n; ++j) dist[i][j] = dist[j][i] = INFL;
	for (int a, b, i = 1; i <= m; ++i) 
	{
		long long c;
		scanf("%d%d%lld", &a, &b, &c);
		dist[a][b] = min(dist[a][b], c);
		dist[b][a] = dist[a][b];
	}
	for (int k = 1; k <= n; ++k)
		for (int i = 1; i <= n; ++i)
			for (int j = 1; j <= n; ++j) dist[i][j] = min(dist[i][j], dist[i][k] + dist[k][j]);
	for (int i = 1; i <= n; ++i) sum += xa[i];
}

int Aug(int p, int flow)
{
	if (p == T) return flow;
	int ret = 0;
	for (int i = now[p]; i; now[p] = i = g[i].next)
	{
		int v = g[i].to;
		if (g[i].w > 0 && h[p] == h[v] + 1)
		{
			int tmp = Aug(v, min(flow - ret, g[i].w));
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

bool check(long long x)
{
	gn = 1; flow = 0;
	memset(h, 0, sizeof(h));
	memset(vh, 0, sizeof(vh));
	memset(start, 0, sizeof(start));
	for (int i = 1; i <= n; ++i) if (xa[i]) AddEdge(S, i, xa[i]);
	for (int i = 1; i <= n; ++i) if (xb[i]) AddEdge(i + n, T, xb[i]);
	for (int i = 1; i <= n; ++i)
		for (int j = 1; j <= n; ++j) if (dist[i][j] <= x) AddEdge(i, j + n, INF);
	vh[0] = N;
	for (int i = 1; i <= N; ++i) now[i] = start[i];
	while (h[S] < N) flow += Aug(S, INF);
	return flow == sum;
}

void Solve()
{
	long long l = 0, r = INFL;
/*	for (int i = 1; i <= n; ++i) 
		for (int j = i + 1; j <= n; ++j) if (dist[i][j] < INFL) r = max(dist[i][j], r);*/
	while (l <= r)
	{
		long long mid = (l + r) >> 1;
		if (check(mid)) r = mid - 1;
		else l = mid + 1;
	}
	printf("%lld\n", l >= INFL ? -1 : l);
}

int main()
{
	Init();
	Solve();
	
	return 0;
}
