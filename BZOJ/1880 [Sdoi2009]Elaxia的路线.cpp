#include <iostream>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <cmath>
#include <fstream>
#include <algorithm>

using namespace std;

const int MAXN = 1500 + 10;
const int MAXM = 1000000 + 10;

struct Edge
{
	int next, to, w;
} g[MAXM * 2];
int gn, start[MAXN];

inline void AddEdge(int a, int b, int c)
{
	gn++; g[gn].next = start[a]; start[a] = gn; g[gn].to = b; g[gn].w = c;
}

int n, m, ans;
int dist1[MAXN], dist2[MAXN], dist3[MAXN], dist[MAXN], q[MAXN], head, tail, S1, S2, T1, T2;
bool vis[MAXN];

void SPFA(int v0)
{
	memset(vis, 0, sizeof(vis));
	memset(dist, 63, sizeof(dist));
	head = 0; tail = 1; q[head] = v0; dist[v0] = 0; vis[v0] = 1;
	while (head != tail)
	{
		int p = q[head++];
		vis[p] = 0;
		if (head == MAXN) head = 0;
		for (int i = start[p]; i; i = g[i].next)
		{
			int v = g[i].to;
			if (dist[v] > dist[p] + g[i].w)
			{
				dist[v] = dist[p] + g[i].w;
				if (!vis[v]) 
				{
					vis[v] = 1;
					if (dist[q[head]] < dist[p]) 
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
}

int main()
{
	scanf("%d%d", &n, &m);
	scanf("%d%d%d%d", &S1, &T1, &S2, &T2);
	for (int a, b, c, i = 1; i <= m; ++i)
	{
		scanf("%d%d%d", &a, &b, &c);
		AddEdge(a, b, c);
		AddEdge(b, a, c);
	}
	SPFA(T2);
	memcpy(dist3, dist, sizeof(dist));
	SPFA(S2);
	memcpy(dist2, dist, sizeof(dist));
	SPFA(T1);
	memcpy(dist1, dist, sizeof(dist));
	SPFA(S1);
	for (int i = 1; i <= n; ++i)
		for (int j = 1; j <= n; ++j)
		{
			if (dist[i] + dist1[i] != dist[T1] || dist[j] + dist1[j] != dist[T1]) continue;
			if (dist2[i] + dist3[i] != dist2[T2] || dist2[j] + dist3[j] != dist2[T2]) continue;
			ans = max(ans, abs(dist[i] + dist1[j] - dist[T1]));
		}
	printf("%d\n", ans);
	
	return 0;
}
