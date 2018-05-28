#include <iostream>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <cmath>
#include <fstream>
#include <algorithm>

using namespace std;

const int MAXN = 1000 + 10;

struct Edge
{
	int next, to;
} g[MAXN * 2];
int gn, start[MAXN];

inline void AddEdge(int a, int b)
{
	gn++; g[gn].next = start[a]; start[a] = gn; g[gn].to = b;
}

int n, q[MAXN], head, tail, father[MAXN], ans;
bool vis[MAXN], mark[MAXN];

int main()
{
	scanf("%d", &n);
	for (int x, i = 2; i <= n; ++i)
	{
		scanf("%d", &x);
		AddEdge(x, i);
		AddEdge(i, x);
	}
	q[head] = 1; tail = 1; vis[1] = 1;
	while (head != tail)
	{
		int p = q[head++];
		for (int i = start[p]; i; i = g[i].next)
		{
			int v = g[i].to;
			if (vis[v]) continue;
			vis[v] = 1;
			q[tail++] = v;
			father[v] = p;
		}
	}
	for (int i = tail - 1; i >= 0; --i)
	{
		int p = q[i];
		if (mark[p]) continue;
		int s = father[father[p]];
		mark[s] = 1;
		for (int j = start[s]; j; j = g[j].next)
		{
			int v = g[j].to;
			mark[v] = 1;
			for (int k = start[v]; k; k = g[k].next) mark[g[k].to] = 1;
		}
		++ans;
	}
	printf("%d\n", ans);
	
	return 0;
}
