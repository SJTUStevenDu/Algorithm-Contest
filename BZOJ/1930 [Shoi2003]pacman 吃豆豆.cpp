#include <iostream>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <algorithm>

using namespace std;

const int MAXN = 4000 + 10;
const int INF = 0x7FFFFFFF >> 2;

struct Edge
{
	int next, to, w, cost;
} g[MAXN / 4 * MAXN];
int gn, start[MAXN];

inline void AddEdge(int a, int b, int c, int d)
{
	gn++; g[gn].next = start[a]; start[a] = gn; g[gn].to = b; g[gn].w = c; g[gn].cost = d;
	gn++; g[gn].next = start[b]; start[b] = gn; g[gn].to = a; g[gn].w = 0; g[gn].cost = -d;
}

int n, x[MAXN], y[MAXN], ans, S, T;
int dist[MAXN], q[MAXN], path[MAXN], head, tail;
bool vis[MAXN];

bool SPFA()
{
	memset(vis, 0, sizeof(vis));
	memset(dist, 63, sizeof(dist));
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
					if (dist[q[head]] < dist[v]) 
					{
						q[tail++] = v;
						if (tail == MAXN) tail = 0;
					}
					else 
					{
						--head; if (head == -1) head += MAXN;
						q[head] = v;
					}
				}
			}
		}
	}
	return dist[T] < INF;
}

void Aug()
{
	int delta = INF, now = T;
	while (now != S)
	{
		int i = path[now];
		delta = min(delta, g[i].w);
		now = g[i ^ 1].to;
	}
	now = T;
	while (now != S)
	{
		int i = path[now];
		g[i].w -= delta;
		g[i ^ 1].w += delta;
		now = g[i ^ 1].to;
	}
	ans += delta * dist[T];
}

int main()
{
	scanf("%d", &n);
	for (int i = 1; i <= n; ++i) scanf("%d%d", &x[i], &y[i]);
	gn = 1;
	S = 2 * n + 1; T = S + 1;
	int T0 = T + 1;
	for (int i = 1; i <= n; ++i) 
	{
		AddEdge(S, i, 1, 0);
		AddEdge(i, i + n, 1, -1);
		AddEdge(i + n, T0, 1, 0); 
	}
	AddEdge(T0, T, 2, 0);
	for (int i = 1; i <= n; ++i)
		for (int j = 1; j <= n; ++j) if (i != j)
			if (x[i] >= x[j] && y[i] >= y[j]) AddEdge(j + n, i, 1, 0);
	while (SPFA()) Aug();
	printf("%d\n", -ans);
	
	return 0;
}
