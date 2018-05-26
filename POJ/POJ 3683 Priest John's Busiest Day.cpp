#include <iostream>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <algorithm>
#include <cmath>

using namespace std;

const int MAXN = 2000 + 10;
const int MAXM = MAXN * MAXN;

struct Edge
{
	int next, to;
} g[MAXM], G[MAXM];
int gn, start[MAXN], Gstart[MAXN];

inline void AddEdge(int a, int b)
{
	gn++; g[gn].next = start[a]; start[a] = gn; g[gn].to = b;
}

inline void GAddEdge(int a, int b)
{
	gn++; G[gn].next = Gstart[a]; Gstart[a] = gn; G[gn].to = b;
}

int n, m, Top, Bcnt, Index;
int dfn[MAXN], Belong[MAXN], low[MAXN], stk[MAXN], st[MAXN], en[MAXN], ind[MAXN], col[MAXN], cf[MAXN];
bool vis[MAXN], ans = true, gg[MAXN][MAXN];
char str[50];

bool check(int i, int j)
{
	if (en[i] <= st[j] || en[j] <= st[i]) return true;
	return false;
}

void Tarjan(int p)
{
	dfn[p] = low[p] = ++Index;
	stk[++Top] = p;
	vis[p] = 1;
	for (int i = start[p]; i; i = g[i].next)
	{
		int v = g[i].to;
		if (!dfn[v])
		{
			Tarjan(v);
			low[p] = min(low[p], low[v]);
		}
		else if (vis[v]) low[p] = min(low[p], dfn[v]);
	}
	if (low[p] == dfn[p])
	{
		int i = -1;
		++Bcnt;
		while (i != p)
		{
			i = stk[Top--];
			vis[i] = 0;
			Belong[i] = Bcnt;
		}
	}
}

int main()
{
	scanf("%d", &n);
	for (int i = 1; i <= n; ++i) 
	{
		scanf("%s", str);
		int hh = (str[0] - '0') * 10 + (str[1] - '0');
		int mm = (str[3] - '0') * 10 + (str[4] - '0');
		int ss = hh * 60 + mm;
		scanf("%s", str);
		hh = (str[0] - '0') * 10 + (str[1] - '0');
		mm = (str[3] - '0') * 10 + (str[4] - '0');
		int ee = hh * 60 + mm;
		int tt;
		scanf("%d", &tt);
		st[i * 2] = ss; en[i * 2] = ss + tt;
		st[i * 2 + 1] = ee - tt; en[i * 2 + 1] = ee;
	}
	for (int i = 1; i <= n; ++i) 
		for (int j = 1; j <= n; ++j) if (i != j)
		{
			if (!check(i * 2, j * 2)) AddEdge(i * 2, j * 2 + 1);
			if (!check(i * 2, j * 2 + 1)) AddEdge(i * 2, j * 2);
			if (!check(i * 2 + 1, j * 2)) AddEdge(i * 2 + 1, j * 2 + 1);
			if (!check(i * 2 + 1, j * 2 + 1)) AddEdge(i * 2 + 1, j * 2);
		}
	for (int i = 2; i <= 2 * n + 1; ++i) if (!dfn[i]) Tarjan(i);
	for (int i = 1; i <= n; ++i)
	{
		if (Belong[i * 2] == Belong[i * 2 + 1]) {ans = false; break;}
		cf[Belong[i * 2]] = Belong[i * 2 + 1];
		cf[Belong[i * 2 + 1]] = Belong[i * 2];
	}
	if (!ans) 
	{
		puts("NO");
		return 0;
	}
	puts("YES");
	gn = 0;
	for (int p = 2; p <= 2 * n + 1; ++p)
		for (int i = start[p]; i; i = g[i].next)
		{
			int v = g[i].to;
			int pp = Belong[p], vv = Belong[v];
			if (pp == vv) continue;
			if (gg[vv][pp]) continue;
			gg[vv][pp] = 1;
			GAddEdge(vv, pp);
			++ind[pp];
		}
	memcpy(start, Gstart, sizeof(start));
	memcpy(g, G, sizeof(g));
	Top = 0;
	for (int i = 1; i <= Bcnt; ++i) if (!ind[i]) stk[++Top] = i;
	while (Top)
	{
		int p = stk[Top--];
		if (!col[p])
		{
			col[p] = 1;
			col[cf[p]] = -1;
		}
		for (int i = start[p]; i; i = g[i].next)
		{
			int v = g[i].to;
			--ind[v];
			if (!ind[v]) stk[++Top] = v;
		}
	}
	int a, b, c, d;
	for (int i = 1; i <= n; ++i) if (col[Belong[2 * i]] == 1)
	{
		a = st[2 * i] / 60;
		b = st[2 * i] % 60;
		c = en[2 * i] / 60;
		d = en[2 * i] % 60;
		printf("%02d:%02d %02d:%02d\n", a, b, c, d);
	}
	else 
	{
		a = st[2 * i + 1] / 60;
		b = st[2 * i + 1] % 60;
		c = en[2 * i + 1] / 60;
		d = en[2 * i + 1] % 60;
		printf("%02d:%02d %02d:%02d\n", a, b, c, d);
	}
	
	return 0;
}
