#include <iostream>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <algorithm>
#include <cmath>

using namespace std;

const int MAXN = 5000 + 10;

struct Edge
{
	int next, to;
} g[MAXN * 2];
int gn, start[MAXN];

inline void AddEdge(int a, int b)
{
	gn++; g[gn].next = start[a]; start[a] = gn; g[gn].to = b;
}

int n, dfn[MAXN], Index, low[MAXN], stk[MAXN], Top, idx[MAXN], m, e[MAXN][2], Belong[MAXN], Bcnt;
bool vis[MAXN];

void Tarjan(int p)
{
	dfn[p] = low[p] = ++Index;
	stk[++Top] = p;
	vis[p] = 1;
	for (int i = start[p]; i; i = g[i].next)
	{
		int v = g[i].to;
		if (!dfn[v])
		{
			Tarjan(v);
			low[p] = min(low[p], low[v]);
		}
		else if (vis[v]) low[p] = min(low[p], dfn[v]);
	}
	if (low[p] == dfn[p])
	{
		++Bcnt;
		int i = -1;
		while (i != p)
		{
			i = stk[Top--];
			vis[i] = 0;
			Belong[i] = Bcnt;
		}
	}
}

bool check(int x)
{
	gn = 0; Top = 0; Bcnt = 0;
	memset(vis, 0, sizeof(vis));
	memset(start, 0, sizeof(start));
	memset(Belong, 0, sizeof(Belong));
	memset(dfn, 0, sizeof(dfn));
	memset(low, 0, sizeof(low));
	for (int i = 1; i <= x; ++i)
	{
		AddEdge((e[i][0] ^ 1), e[i][1]);
		AddEdge((e[i][1] ^ 1), e[i][0]);
	}
	for (int i = 2; i <= 2 * n + 1; ++i) if (!dfn[i]) Tarjan(i);
	for (int i = 2; i <= 2 * n + 1; i += 2) if (Belong[i] == Belong[i + 1]) return false;
	return true;
}

int main()
{
	while (~scanf("%d%d", &n, &m))
	{
		if (!n) break;
		for (int x, y, i = 1; i <= n; ++i) 
		{
			scanf("%d%d", &x, &y);
			idx[x] = 2 * i; idx[y] = 2 * i + 1;
		}
		for (int x, y, i = 1; i <= m; ++i) 
		{
			scanf("%d%d", &x, &y);
			e[i][0] = idx[x]; e[i][1] = idx[y];
		}
		int l = 0, r = m;
		while (l <= r)
		{
			int mid = (l + r) >> 1;
			if (check(mid)) l = mid + 1;
			else r = mid - 1;
		}
		printf("%d\n", r);
	}
	
	return 0;
}
