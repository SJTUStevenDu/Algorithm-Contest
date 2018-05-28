#include <iostream>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <cmath>
#include <fstream>
#include <algorithm>
#include <vector>

using namespace std;

const int MAXN = 3000 + 10;
const int MAXM = 70000 + 10;
const long long INF = 10000000000000000LL;

struct Edge
{
	int next, to, w;
} g[MAXM];
int gn, start[MAXN];

inline void AddEdge(int a, int b, int c)
{
	gn++; g[gn].next = start[a]; start[a] = gn; g[gn].to = b; g[gn].w = c;
}

long long dist[MAXN];
int n, m, ind[MAXN];
bool vis[MAXN];
vector <int> Q[MAXN];
vector <int> :: iterator it;

void Dij()
{
	for (int i = 0; i <= n; ++i) dist[i] = INF;
	dist[1] = 0;
	for (int i = 1; i <= n; ++i)
	{
		int la = 0;
		for (int j = 1; j <= n; ++j) if (!vis[j] && ind[j] == 0 && dist[j] < dist[la]) la = j;
		vis[la] = 1;
		if (la == n) break;
		for (int j = start[la]; j; j = g[j].next) dist[g[j].to] = min(dist[g[j].to], dist[la] + g[j].w);
		for (it = Q[la].begin(); it != Q[la].end(); ++it) ind[*it]--, dist[*it] = max(dist[*it], dist[la]);
	}
}

int main()
{
	scanf("%d%d", &n, &m);
	for (int a, b, c, i = 1; i <= m; ++i)
	{
		scanf("%d%d%d", &a, &b, &c);
		AddEdge(a, b, c);
	}
	for (int i = 1; i <= n; ++i)
	{
		scanf("%d", &ind[i]);
		for (int x, j = 1; j <= ind[i]; ++j)
		{
			scanf("%d", &x);
			Q[x].push_back(i);
		}
	}
	Dij();
	printf("%lld\n", dist[n]);
	
	return 0;
}
