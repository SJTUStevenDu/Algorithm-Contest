#include <iostream>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <cmath>
#include <fstream>
#include <algorithm>

using namespace std;

const int MAXN = 200000 + 10;

struct Edge
{
	int next, to;
} g[MAXN * 2];
int gn, start[MAXN];

inline void AddEdge(int a, int b)
{
	gn++; g[gn].next = start[a]; start[a] = gn; g[gn].to = b;
}

struct Node
{
	int nx, ny, idx;
} l[MAXN * 2];

int n, q[MAXN], d[MAXN], head, tail, tot, a, b, c, pp;
bool vis[MAXN];

inline void AddLine(int a, int b, int i)
{
	++tot; l[tot].idx = i; l[tot].nx = min(a, b); l[tot].ny = max(a, b);
}

bool cmp(Node A, Node B)
{
	return A.nx != B.nx ? A.nx < B.nx : A.ny < B.ny;
}

int main()
{
	scanf("%d", &n);
	for (int i = 1; i <= n - 2; ++i)
	{
		scanf("%d%d%d", &a, &b, &c);
		if (abs(a - b) > 1 && abs(a % n - b % n) > 1) AddLine(a, b, i);
		if (abs(a - c) > 1 && abs(a % n - c % n) > 1) AddLine(a, c, i);
		if (abs(b - c) > 1 && abs(b % n - c % n) > 1) AddLine(b, c, i);
	}
	sort(l + 1, l + 1 + tot, cmp);
	for (int i = 1; i <= tot; i += 2) AddEdge(l[i].idx, l[i + 1].idx), AddEdge(l[i + 1].idx, l[i].idx);
	vis[1] = 1; tail = 1; q[head] = 1; d[1] = 1;
	while (head != tail)
	{
		int p = q[head++];
		for (int i = start[p]; i; i = g[i].next)
		{
			int v = g[i].to;
			if (vis[v]) continue;
			q[tail++] = v;
			d[v] = d[p] + 1;
			vis[v] = 1;
		}
	}
	memset(vis, 0, sizeof(vis));
	memset(d, 0, sizeof(d));
	pp = q[tail - 1]; vis[pp] = 1; d[pp] = 1;
	head = 0; tail = 1; q[head] = pp;
	while (head != tail)
	{
		int p = q[head++];
		for (int i = start[p]; i; i = g[i].next)
		{
			int v = g[i].to;
			if (vis[v]) continue;
			q[tail++] = v;
			d[v] = d[p] + 1;
			vis[v] = 1;
		}
	}
	printf("%d\n", d[q[tail - 1]]);
	
	return 0;
}
