#include <iostream>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <algorithm>
#include <cmath>

using namespace std;

const int MAXN = 1000 + 10;
const int MAXM = MAXN * MAXN * 2;
const long long INF = 100000000000000LL;

struct Edge
{
	int next, to;
	long long w;
} g[MAXM];
int gn = 1, start[MAXN];

inline void AddEdge(int a, int b, long long c)
{
	gn++; g[gn].next = start[a]; start[a] = gn; g[gn].to = b; g[gn].w = c;
}

inline void Add(int a, int b, long long c, long long d)
{
	AddEdge(a, b, c);
	AddEdge(b, a, d);
}

int S, T, n, N;
long long e[MAXN][MAXN], sum[MAXN], a[MAXN], ans;
int h[MAXN], vh[MAXN];

long long Aug(int p, long long flow)
{
	if (p == T) return flow;
	long long ret = flow;
	int minnode = N - 1;
	for (int i = start[p]; i; i = g[i].next) if (g[i].w > 0)
	{
		int v = g[i].to;
		if (h[v] + 1 == h[p])
		{
			long long tmp = Aug(v, min(g[i].w, ret));
			ret -= tmp;
			g[i].w -= tmp;
			g[i ^ 1].w += tmp;
			if (h[S] >= N || ret == 0) return flow - ret;
		}
		if (g[i].w > 0) minnode = min(minnode, h[v]);
	}
	if (flow == ret)
	{
		--vh[h[p]];
		if (vh[h[p]] == 0) h[S] = N;
		++vh[h[p] = minnode + 1];
	}
	return flow - ret;
}

int main()
{
	scanf("%d", &n);
	for (int i = 1; i <= n; ++i) scanf("%lld", &a[i]);
	for (int i = 1; i <= n; ++i)
		for (int j = 1; j <= n; ++j) scanf("%lld", &e[i][j]), ans += e[i][j], sum[i] += e[i][j];
	S = n + 1; T = S + 1; N = T;
	for (int i = 1; i <= n; ++i) Add(S, i, sum[i], 0), Add(i, T, a[i], 0);
	for (int i = 1; i <= n; ++i) 
		for (int j = i + 1; j <= n; ++j) Add(i, j, 2 * e[i][j], 2 * e[i][j]);
	vh[0] = N;
	while (h[S] < N) ans -= Aug(S, INF);
	printf("%lld\n", ans);
	
	return 0;
}
