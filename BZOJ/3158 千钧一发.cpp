#include <iostream>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <cmath>
#include <fstream>
#include <algorithm>

using namespace std;

const int MAXN = 1000 + 10;
const int MAXM = 555555;
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

int n, num[MAXN], val[MAXN], h[MAXN], vh[MAXN], S, T, N, ans;

int Aug(int p, int flow)
{
	if (p == T) return flow;
	int ret = flow, minnode = N - 1;
	for (int i = start[p]; i; i = g[i].next) if (g[i].w > 0)
	{
		int v = g[i].to;
		if (h[p] == h[v] + 1)
		{
			int tmp = Aug(v, min(g[i].w, ret));
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

inline int gcd(int n, int m)
{
	int tmp;
	while (m)
	{
		tmp = n % m;
		n = m; 
		m = tmp;
	}
	return n;
}

bool check(int x, int y)
{
	long long z = (long long)x * x + (long long)y * y;
	long long kk = (long long)sqrt(z * 1.0);
	if (kk * kk != z) return false;
	if (gcd(x, y) > 1) return false;
	return true;
}

int main()
{
	gn = 1;
	scanf("%d", &n);
	for (int i = 1; i <= n; ++i) scanf("%d", &num[i]);
	for (int i = 1; i <= n; ++i) scanf("%d", &val[i]), ans += val[i];
	S = n + 1; T = S + 1; N = T;
	for (int i = 1; i <= n; ++i) if (num[i] & 1)
	{
		AddEdge(S, i, val[i]);
		for (int j = 1; j <= n; ++j) if (!(num[j] & 1) && check(num[i], num[j])) AddEdge(i, j, INF);
	} else AddEdge(i, T, val[i]);
	vh[0] = N;
	while (h[S] < N) ans -= Aug(S, INF);
	printf("%d\n", ans);
	
	return 0;
}
