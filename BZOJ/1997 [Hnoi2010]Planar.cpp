#include <iostream>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <cmath>
#include <algorithm>
#include <fstream>

using namespace std;

const int MAXN = 200 + 10;
const int MAXM = 10000 + 10;

int T, n, m, h[MAXN], rank[MAXN], c[MAXN], e[MAXM][2], tot, e2[MAXM][2];
bool map[MAXN][MAXN], ans;

struct Edge
{
	int next, to;
} g[400000];
int gn, start[MAXM];

inline void AddEdge(int a, int b)
{
	gn++; g[gn].next = start[a]; start[a] = gn; g[gn].to = b;
}

bool Fright(int x1, int y1, int x2, int y2)
{
	if (x1 == x2 || x1 == y2 || x2 == y1 || y1 == y2) return 0;
	x1 = rank[x1]; y1 = rank[y1]; x2 = rank[x2]; y2 = rank[y2];
	if (x1 > y1) swap(x1, y1);
	return (x1 < x2 && x2 < y1) != (x1 < y2 && y2 < y1);
}

void dfs(int p, int flag)
{
	c[p] = flag;
	for (int i = start[p]; i; i = g[i].next)
	{
		int v = g[i].to;
		if (c[v] == flag) ans = false;
		else if (!c[v]) dfs(v, -flag);
		if (!ans) return;
	}
}

int main()
{
	scanf("%d", &T);
	while (T--)
	{
		scanf("%d%d", &n, &m);
		ans = true;
		memset(start, 0, sizeof(start));
		gn = 0;
		memset(map, 0, sizeof(map));
		memset(rank, 0, sizeof(rank));
		for (int i = 1; i <= m; ++i) scanf("%d%d", &e[i][0], &e[i][1]);
		for (int i = 1; i <= n; ++i) scanf("%d", &h[i]), rank[h[i]] = i;
		for (int i = 1; i < n; ++i) map[h[i + 1]][h[i]] = map[h[i]][h[i + 1]] = 1;
		map[h[n]][h[1]] = map[h[1]][h[n]] = 1;
		if (m > 3 * n - 6)
		{
			puts("NO");
			continue;
		}
		tot = 0;
		for (int i = 1; i <= m; ++i) if (!map[e[i][0]][e[i][1]]) e2[++tot][0] = e[i][0], e2[tot][1] = e[i][1];
		for (int i = 1; i <= tot; ++i) 
			for (int j = i + 1; j <= tot; ++j) if (Fright(e2[i][0], e2[i][1], e2[j][0], e2[j][1])) AddEdge(i, j), AddEdge(j, i);
		memset(c, 0, sizeof(c));
		for (int i = 1; i <= tot; ++i) if (!c[i])
		{
			dfs(i, 1);
			if (!ans) break;
		}
		if (ans) puts("YES"); else puts("NO");
	}
	
	return 0;
}
