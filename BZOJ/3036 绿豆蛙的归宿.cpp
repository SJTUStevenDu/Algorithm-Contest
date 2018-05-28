#include <iostream>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <algorithm>
#include <cmath>

using namespace std;

const int MAXN = 100000 + 10;

struct Edge
{
	int next, to, w;
} g[MAXN * 2];
int gn, start[MAXN];

inline void AddEdge(int a, int b, int c)
{
	gn++; g[gn].next = start[a]; start[a] = gn; g[gn].to = b; g[gn].w = c;
}

int stk[MAXN], ind[MAXN], outd[MAXN];
int n, m, ss[MAXN], Top, num;
double ans[MAXN];

int main()
{
	scanf("%d%d", &n, &m);
	for (int a, b, c, i = 1; i <= m; ++i)
	{
		scanf("%d%d%d", &a, &b, &c);
		AddEdge(b, a, c);
		ind[a]++;
		outd[a]++;
	}
	stk[++Top] = n;
	while (Top)
	{
		int p = stk[Top--];
		ss[++num] = p;
		for (int i = start[p]; i; i = g[i].next)
		{
			int v = g[i].to;
			--ind[v];
			if (ind[v] == 0) stk[++Top] = v;
		}
	}
	ans[n] = 0;
	for (int i = 1; i <= num; ++i)
	{
		int p = ss[i];
		for (int i = start[p]; i; i = g[i].next)
		{
			
			int v = g[i].to;
			ans[v] += (ans[p] + g[i].w) * 1.0 / outd[v];
		}
	}
	printf("%.2lf\n", ans[1]);
	
	return 0;
}
