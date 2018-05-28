#include <iostream>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <cmath>
#include <fstream>
#include <algorithm>

using namespace std;

const int MAXN = 100000 + 10;
const int MAXT = 2000000 + 10;

struct Edge
{
	int next, to;
} g[MAXN * 2];
int gn, start[MAXN];

inline void AddEdge(int a, int b)
{
	gn++; g[gn].next = start[a]; start[a] = gn; g[gn].to = b;
}

int w[MAXN], b[MAXN], l[MAXT], r[MAXT], n, Q, m, tot, fa[20][MAXN], s[MAXT], dep[MAXN], q[MAXN], head, tail, root[MAXN], Log[MAXN], ans;
bool vis[MAXN];

void BFS()
{
	head = 0; tail = 1; q[head] = 1; vis[1] = 1; dep[1] = 1;
	while (head != tail)
	{
		int p = q[head++];
		vis[p] = 1;
		for (int i = start[p]; i; i = g[i].next)
		{
			int v = g[i].to;
			if (vis[v]) continue;
			q[tail++] = v;
			vis[v] = 1;
			dep[v] = dep[p] + 1;
			fa[0][v] = p;
		}
	}
	for (int i = 1; i <= Log[n]; ++i)
		for (int j = 1; j <= n; ++j) fa[i][j] = fa[i - 1][fa[i - 1][j]];
}

inline int getfa(int p, int v)
{
	while (v) p = fa[Log[v]][p], v -= (1 << Log[v]);
	return p;
}

int LCA(int x, int y)
{
	if (dep[x] < dep[y]) swap(x, y);
	x = getfa(x, dep[x] - dep[y]);
	int u = 0;
	for (; fa[u][x] != fa[u][y]; ++u);
	for (; u >= 0; --u) if (fa[u][x] != fa[u][y]) x = fa[u][x], y = fa[u][y];
	if (x != y) return fa[0][x]; else return x;
}

void Insert(int x, int &y, int L, int R, int v)
{
	s[y = ++tot] = s[x] + 1;
	if (L == R) return;
	int mid = (L + R) >> 1;
	if (v <= mid) 
	{
		r[y] = r[x];
		Insert(l[x], l[y], L, mid, v);
	}
	else 
	{
		l[y] = l[x];
		Insert(r[x], r[y], mid + 1, R, v);
	}
}

int Query(int x, int y, int z, int z1, int L, int R, int v)
{
	if (L == R) return L;
	int mid = (L + R) >> 1, cur = s[l[x]] + s[l[y]] - s[l[z]] - s[l[z1]];
	if (v <= cur) return Query(l[x], l[y], l[z], l[z1], L, mid, v);
	else return Query(r[x], r[y], r[z], r[z1], mid + 1, R, v - cur);
}

int main()
{
	scanf("%d%d", &n, &Q);
	for (int i = 2; i <= n; ++i) Log[i] = Log[i >> 1] + 1;
	for (int i = 1; i <= n; ++i) scanf("%d", &w[i]);
	for (int aa, bb, i = 1; i < n; ++i) 
	{
		scanf("%d%d", &aa, &bb);
		AddEdge(aa, bb); AddEdge(bb, aa);
	}
	BFS();
	memcpy(b, w, sizeof(w));
	sort(b + 1, b + 1 + n);
	m = unique(b + 1, b + 1 + n) - b - 1;
	for (int i = 1; i <= n; ++i) w[i] = lower_bound(b + 1, b + 1 + m, w[i]) - b;
	for (int i = 0; i < tail; ++i) Insert(root[fa[0][q[i]]], root[q[i]], 1, m, w[q[i]]);
	while (Q--)
	{
		int x, y, z;
		scanf("%d%d%d", &x, &y, &z);
		x = x ^ ans;
		int lca = LCA(x, y);
		printf("%d", ans = b[Query(root[x], root[y], root[lca], root[fa[0][lca]], 1, m, z)]);
		if (Q) putchar('\n');
	}
	
	return 0;
}
