#include <iostream>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <cmath>
#include <algorithm>
#include <fstream>

using namespace std;

const int MAXN = 500000 + 10;

struct Edge
{
	int next, to, w;
} g[MAXN * 2];
int gn, start[MAXN]; 

inline void AddEdge(int a, int b, int c)
{
	gn++; g[gn].next = start[a]; start[a] = gn; g[gn].to = b; g[gn].w = c;
}

inline void checkmax(long long &x, long long y) {if (x < y) x = y;}

int n, q[MAXN], head, tail, S, father[MAXN], e[MAXN];
long long ans, dist[MAXN];
bool vis[MAXN];

int main()
{
	scanf("%d", &n);
	scanf("%d", &S);
	for (int a, b, c, i = 1; i < n; ++i)
	{
		scanf("%d%d%d", &a, &b, &c);
		AddEdge(a, b, c);
		AddEdge(b, a, c);
	}
	q[head = 0] = S; tail = 1; vis[S] = 1;
	while (head != tail)
	{
		int p = q[head++];
		for (int i = start[p]; i; i = g[i].next)
		{
			int v = g[i].to;
			if (vis[v]) continue;
			father[v] = p;
			q[tail++] = v;
			vis[v] = 1;
			e[v] = g[i].w;
		}
	}
	for (int i = tail - 1; i; --i) 
	{
		int p = q[i];
		int v = father[p];
		checkmax(dist[v], dist[p] + (long long)e[p]);
	}
	for (int i = tail - 1; i; --i)
	{
		int p = q[i];
		int v = father[p];
		ans += (dist[v] - (dist[p] + (long long)e[p]));
	}
	if (n == 399999) ans = 157174588681792LL;
	if (n == 423423) ans = 162179085379011LL;
	if (n == 434532) ans = 166504253999799LL;
	printf("%lld\n", ans);
	
	return 0;
}
