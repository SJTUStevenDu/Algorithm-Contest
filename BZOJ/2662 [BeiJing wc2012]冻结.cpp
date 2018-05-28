#include <iostream>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <cmath>
#include <fstream>
#include <algorithm>

using namespace std;

const int MAXN = 50 * 51 + 10;
const int MAXM = 1000 * 51 + 10;

struct Edge
{
	int next, to, w;
} g[MAXM * 4];
int gn, start[MAXN];

inline void AddEdge(int a, int b, int c)
{
	gn++; g[gn].next = start[a]; start[a] = gn; g[gn].to = b; g[gn].w = c;
}

int n, m, k, ans = 0x7FFFFFFF >> 2;
int q[MAXN], head, tail, dist[MAXN];
bool vis[MAXN];

void SPFA()
{
	memset(dist, 63, sizeof(dist));
	head = 0; tail = 1; q[head] = 1; vis[1] = 1; dist[1] = 0;
	while (head != tail)
	{
		int p = q[head++];
		if (head == MAXN) head = 0;
		vis[p] = 0;
		for (int i = start[p]; i; i = g[i].next)
		{
			int v = g[i].to;
			if (dist[v] > dist[p] + g[i].w)
			{
				dist[v] = dist[p] + g[i].w;
				if (vis[v]) continue;
				vis[v] = 1;
				q[tail++] = v;
				if (tail == MAXN) tail = 0;
			}
		}
	}
}

int main()
{
	scanf("%d%d%d", &n, &m, &k);
	for (int a, b, c, i = 1; i <= m; ++i)
	{
		scanf("%d%d%d", &a, &b, &c);
		for (int j = 0; j <= k; ++j)
		{
			AddEdge(j * n + a, j * n + b, c); AddEdge(j * n + b, j * n + a, c);
			if (j != k) AddEdge(j * n + a, (j + 1) * n + b, c / 2), AddEdge(j * n + b, (j + 1) * n + a, c / 2);
		}
	}
	SPFA();
	for (int i = 0; i <= k; ++i) ans = min(ans, dist[i * n + n]);
	printf("%d\n", ans);
	
	return 0;
}
