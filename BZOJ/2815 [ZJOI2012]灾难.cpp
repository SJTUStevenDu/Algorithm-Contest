#include <iostream>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <cmath>
#include <algorithm>
#include <fstream>

using namespace std;

const int MAXN = 70000 + 10;
const int MAXM = 2000000 + 10;

struct Edge
{
	int next, to;
} g[MAXM];
int gn, start[MAXN];

inline void AddEdge(int a, int b)
{
	gn++; g[gn].to = b; g[gn].next = start[a]; start[a] = gn;
}

int n, stk[MAXN], ind[MAXN], seq[MAXN], q[MAXN], sz[MAXN], Top;
int dep[MAXN], Log[MAXN], fa[20][MAXN], edge[MAXM][2], tot, head, tail;
bool vis[MAXN];

void Toposort()
{
	for (int i = 1; i <= n + 1; ++i) if (!ind[i]) stk[++Top] = i;
	int cnt = 0;
	while (Top)
	{
		int p = seq[++cnt] = stk[Top--];
		for (int i = start[p]; i; i = g[i].next)
		{
			int v = g[i].to;
			--ind[v];
			if (ind[v] == 0) stk[++Top] = v;
		}
	}
}

int getfa(int p, int v)
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
	if (x == y) return x;
	else return fa[0][x];
}

void BFS()
{
	head = 0; tail = 1; vis[n + 1] = 1; q[head] = n + 1;
	while (head != tail)
	{
		int p = q[head++];
		for (int i = start[p]; i; i = g[i].next)
		{
			int v = g[i].to;
			if (!vis[v]) vis[v] = 1, q[tail++] = v;
		}
	}
}

int main()
{
	scanf("%d", &n);
	for (int p, i = 1; i <= n; ++i)
	{
		bool flag = true;
		while (true)
		{
			scanf("%d", &p);
			if (!p) break;
			flag = false;
			edge[++tot][0] = p; edge[tot][1] = i;
		}
		if (flag) edge[++tot][0] = n + 1; edge[tot][1] = i;
	}
	
	for (int i = 1; i <= tot; ++i) AddEdge(edge[i][0], edge[i][1]), ++ind[edge[i][1]];
	Toposort();
	Log[0] = -1;
	for (int i = 1; i <= n + 1; ++i) Log[i] = Log[i >> 1] + 1;
	gn = 0; memset(start, 0, sizeof(start));
	for (int i = 1; i <= tot; ++i) AddEdge(edge[i][1], edge[i][0]);
	tot = 0;
	for (int i = 1; i <= n + 1; ++i)
	{
		int p = seq[i];
		int lca = 0;
		for (int j = start[p]; j; j = g[j].next)
		{
			int v = g[j].to;
			if (!lca) lca = v;
			else lca = LCA(lca, v);
		}
		fa[0][p] = lca;
		dep[p] = dep[lca] + 1;
		edge[++tot][0] = p, edge[tot][1] = lca;
		for (int j = 1; j <= Log[n + 1]; ++j) fa[j][p] = fa[j - 1][fa[j - 1][p]];
	}
	gn = 0; memset(start, 0, sizeof(start));
	for (int i = 1; i <= tot; ++i) if (edge[i][0] && edge[i][1]) AddEdge(edge[i][0], edge[i][1]), AddEdge(edge[i][1], edge[i][0]);
	BFS();
	for (int i = 1; i <= n + 1; ++i) sz[i] = 1;
	for (int i = tail - 1; i >= 0; --i)
	{
		int p = q[i];
		vis[p] = 0;
		for (int i = start[p]; i; i = g[i].next)
		{
			int v = g[i].to;
			if (!vis[v]) sz[p] += sz[v];
		}
	}
	for (int i = 1; i <= n; ++i) printf("%d\n", sz[i] - 1);
	
	return 0;
}
