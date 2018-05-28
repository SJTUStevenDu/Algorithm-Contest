#include <iostream>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <algorithm>
#include <cmath>

using namespace std;

const int MAXN = 300 + 10;
const int MAXM = 100000 + 10;
const int INF = 0x7FFFFFFF >> 2;

struct Edge
{
	int next, to, w, cost;
} g[MAXM];
int gn, start[MAXN];

inline void AddEdge(int a, int b, int c, int d)
{
	gn++; g[gn].next = start[a]; start[a] = gn; g[gn].to = b; g[gn].w = c; g[gn].cost = d;
	gn++; g[gn].next = start[b]; start[b] = gn; g[gn].to = a; g[gn].w = 0; g[gn].cost = -d;
}

int n, map[MAXN][MAXN], m, K, S, T, SS, ans;
int dist[MAXN], q[MAXN], head, tail, path[MAXN];
bool vis[MAXN];

bool SPFA()
{
	memset(dist, 63, sizeof(dist));
	memset(vis, 0, sizeof(vis));
	head = 0; tail = 1; q[head] = S; vis[S] = 1; dist[S] = 0;
	while (head != tail)
	{
		int p = q[head++];
		vis[p] = 0;
		if (head == MAXN) head = 0;
		for (int i = start[p]; i; i = g[i].next) if (g[i].w)
		{
			int v = g[i].to;
			if (dist[v] > dist[p] + g[i].cost)
			{
				dist[v] = dist[p] + g[i].cost;
				path[v] = i;
				if (!vis[v])
				{
					vis[v] = 1;
					if (dist[q[head]] > dist[v])
					{
						--head; if (head == -1) head += MAXN;
						q[head] = v;
					}
					else 
					{
						q[tail++] = v;
						if (tail == MAXN) tail = 0;
					}
				}
			}
		}
	}
	return dist[T] < INF;
}

void Aug()
{
	int now = T, delta = INF;
	while (now != S)
	{
		int i = path[now];
		delta = min(delta, g[i].w);
		now = g[i ^ 1].to;
	}
	now = T;
	ans += delta * dist[T];
	while (now != S)
	{
		int i = path[now];
		g[i].w -= delta;
		g[i ^ 1].w += delta;
		now = g[i ^ 1].to;
	}
}

int main()
{
	scanf("%d%d%d", &n, &m, &K);
	for (int i = 0; i <= n; ++i)
		for (int j = 0; j <= n; ++j) map[i][j] = INF;
	for (int i = 0; i <= n; ++i) map[i][i] = 0;
	for (int a, b, c, i = 1; i <= m; ++i) 
	{
		scanf("%d%d%d", &a, &b, &c);
		map[a][b] = min(map[a][b], c);
		map[b][a] = min(map[b][a], c);
	}
	gn = 1;
	for (int k = 0; k <= n; ++k)
		for (int i = 0; i <= n; ++i)
			for (int j = 0; j <= n; ++j) 
				if (max(i, j) >= k) map[i][j] = min(map[i][j], map[i][k] + map[k][j]);
	T = 2 * n + 3; S = T - 1; SS = S - 1;
	AddEdge(S, SS, K, 0);
	for (int i = 1; i <= n; ++i)
	{
		AddEdge(SS, i, 1, map[0][i]);
		AddEdge(i, T, 1, 0);
		AddEdge(S, i + n, 1, 0);
	}
	for (int i = 1; i <= n; ++i) 
		for (int j = i + 1; j <= n; ++j) if (map[i][j] != INF) AddEdge(i + n, j, 1, map[i][j]);
	while (SPFA()) Aug();
	printf("%d\n", ans);
	
	return 0;
}
