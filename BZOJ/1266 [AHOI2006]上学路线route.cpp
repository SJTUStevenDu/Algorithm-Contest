#include <iostream>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <cmath>
#include <fstream>
#include <algorithm>

using namespace std;

const int MAXN = 500 + 10;
const int MAXM = 124750 + 10;
const int INF = 0x7FFFFFFF >> 2;

struct Edge
{
	int next, to, w, cost;
} g[MAXM * 2], G[MAXM * 2];
int gn, Gn, start[MAXN], Gstart[MAXN];

inline void AddEdge(int a, int b, int c, int d)
{
	gn++; g[gn].next = start[a]; start[a] = gn; g[gn].to = b; g[gn].w = d;
	gn++; g[gn].next = start[b]; start[b] = gn; g[gn].to = a; g[gn].w = 0;
}

inline void GAddEdge(int a, int b, int c, int d)
{
	Gn++; G[Gn].next = Gstart[a]; Gstart[a] = Gn; G[Gn].to = b; G[Gn].w = c; G[Gn].cost = d;
	Gn++; G[Gn].next = Gstart[b]; Gstart[b] = Gn; G[Gn].to = a; G[Gn].w = c; G[Gn].cost = d;
}

int n, m, dist[MAXN], q[MAXN], head, tail, delta, ans, S, T;
bool vis[MAXN];

void SPFA()
{
	memset(dist, 63, sizeof(dist));
	head = 0; tail = 1; vis[1] = 1; dist[S] = 0; q[head] = S;
	while (head != tail)
	{
		int p = q[head++];
		vis[p] = 0;
		if (head == MAXN) head = 0;
		for (int i = Gstart[p]; i; i = G[i].next)
		{
			int v = G[i].to;
			if (dist[v] > dist[p] + G[i].w)
			{
				dist[v] = dist[p] + G[i].w;
				if (!vis[v]) 
				{
					vis[v] = 1;
					if (dist[v] > dist[q[head]])
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
	printf("%d\n", dist[T]);
}

int now[MAXN], h[MAXN], vh[MAXN];

int Aug(int p, int flow)
{
	if(p == T) return flow;
	int ret = 0, minh = n - 1;
	for (int i = now[p]; i; i = now[p] = g[i].next) if (g[i].w)
	{
		int v = g[i].to;
		if (h[v] + 1 == h[p])
		{
			int tmp = Aug(v, min(flow - ret, g[i].w));
			ret += tmp;
			g[i].w -= tmp;
			g[i^1].w += tmp;
			if (ret == flow) return flow;
		}
		minh = min(minh, h[v]);
	}
	--vh[h[p]];
	if (!vh[h[p]]) h[S] = n;
	h[p] = minh + 1;
	now[p] = start[p];
	++vh[h[p]];
	return ret;
}

int main()
{
	gn = 1;
	scanf("%d%d", &n, &m);
	for (int a, b, c, d, i = 1; i <= m; ++i)
	{
		scanf("%d%d%d%d", &a, &b, &c, &d);
		GAddEdge(a, b, c, d);
	}
	S = 1; T = n;
	SPFA();
	for (int p = 1; p <= n; ++p)
	{
		for (int i = Gstart[p]; i; i = G[i].next)
		{
			int v = G[i].to;
			if (dist[p] + G[i].w == dist[v]) AddEdge(p, G[i].to, G[i].w, G[i].cost);
		}
	}
	for (int i = 1; i <= n; ++i) now[i] = start[i];
	vh[0] = n;
	while (h[S] < n) ans += Aug(S, INF);
	printf("%d\n", ans);
	
	return 0;
}
