#include <iostream>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <algorithm>
#include <cmath>

using namespace std;

const int MAXN = 200000 + 10;
const int MAXL = 22;

struct Edge
{
	int next, to;
	long long w;
} g[MAXN * 2];
int gn, start[MAXN];

inline void AddEdge(int a, int b, long long c)
{
	gn++; g[gn].next = start[a]; start[a] = gn; g[gn].to = b; g[gn].w = c;
}

long long dist[MAXN], ans;
int n, p1, p2, q[MAXN], head, tail, root, Log[MAXN], fa[MAXL][MAXN], dep[MAXN], m;
bool vis[MAXN];

void BFS()
{
	memset(vis, 0, sizeof(vis));
	head = 0; tail = 1; vis[root] = 1; q[head] = root; dep[root] = 1; fa[0][root] = dist[root] = 0;
	while (head != tail)
	{
		int p = q[head++];
		for (int i = start[p]; i; i = g[i].next)
		{
			int v = g[i].to;
			if (!vis[v]) 
			{
				dist[v] = dist[p] + g[i].w;
				dep[v] = dep[p] + 1;
				vis[v] = 1;
				q[tail++] = v;
				fa[0][v] = p;
			}
		}
	}
}

inline int getfa(int p, int v)
{
	while (v) p = fa[Log[v]][p], v -= (1 << Log[v]);
	return p;
}

int LCA(int a, int b)
{
	if (dep[a] < dep[b]) swap(a, b);
	a = getfa(a, dep[a] - dep[b]);
	int u = 0;
	for (; fa[u][a] != fa[u][b]; ++u);
	for (; u >= 0; --u) if (fa[u][a] != fa[u][b]) a = fa[u][a], b = fa[u][b];
	if (a == b) return a;
	else return fa[0][a];
}

long long Getdist(int a, int b)
{
	return dist[a] + dist[b] - 2 * dist[LCA(a, b)];
}

int main()
{
	scanf("%d%d", &n, &m);
	for (int a, b, i = 1 ; i < n; ++i)
	{
		long long c;
		scanf("%d%d%lld", &a, &b, &c);
		AddEdge(a, b, c);
		AddEdge(b, a, c);
	}
	Log[0] = -1;
	for (int i = 1; i <= n; ++i) Log[i] = Log[i >> 1] + 1;
	root = 1;
	BFS();
	for (int i = 1; i <= n; ++i) if (dist[p1] < dist[i]) p1 = i;
	root = p1; 
	BFS();
	for (int i = 1; i <= n; ++i) if (dist[p2] < dist[i]) p2 = i;
	for (int i = 1; i <= Log[n]; ++i)
		for (int j = 1; j <= n; ++j) fa[i][j] = fa[i - 1][fa[i - 1][j]];
	for (int i = 1; i <= n; ++i) ans = max(ans, min(Getdist(i, p1), Getdist(i, p2)));
	ans += dist[p2];
	printf("%lld\n", ans);
	
	return 0;
}
