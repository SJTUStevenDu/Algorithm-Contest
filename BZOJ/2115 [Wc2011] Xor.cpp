#include <iostream>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <cmath>
#include <fstream>
#include <algorithm>

using namespace std;

const int MAXN = 50000 + 10;
const int MAXM = 200000 + 10;

struct Edge
{
	int next, to;
	long long w;
} g[MAXM];
int gn, start[MAXN];

inline void AddEdge(int a, int b, long long c)
{
	gn++; g[gn].next = start[a]; start[a] = gn; g[gn].to = b; g[gn].w = c;
}

int n, m, tot, q[MAXN], head, tail;
long long d[MAXN], cir[MAXM], ans[100];
bool vis[MAXN];

int main()
{
	scanf("%d%d", &n, &m);
	for (int a, b, i = 1; i <= m; ++i)
	{
		long long c;
		scanf("%d%d%lld", &a, &b, &c);
		AddEdge(a, b, c);
		AddEdge(b, a, c);
	}
	d[1] = 0; q[head] = 1; tail = 1; vis[1] = 1;
	while (head != tail)
	{
		int p = q[head++];
		for (int i = start[p]; i; i = g[i].next)
		{
			int v = g[i].to;
			if (!vis[v])
			{
				d[v] = (d[p] ^ g[i].w);
				q[tail++] = v;
				vis[v] = 1;
			}
			else if ((d[v] ^ d[p] ^ g[i].w) != 0) cir[++tot] = (d[v] ^ d[p] ^ g[i].w);
		}
	}
	for (int i = 1; i <= tot; ++i)
	{
		long long tmp = cir[i];
		for (int j = 59; j >= 0; --j)
			if (tmp & (1LL << j)) tmp ^= ans[j];
		for (int j = 59; j >= 0; --j)
			if (tmp & (1LL << j)) {ans[j] = tmp; break;}
	}
	long long res = d[n];
	for (int i = 59; i >= 0; --i) if ((res ^ ans[i]) > res) res ^= ans[i];
	printf("%lld\n", res);
	
	return 0;
}
