#include <iostream>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <algorithm>
#include <cmath>

using namespace std;

const int MAXN = 1000 + 10;
const int MAXM = 4000000 + 10;

struct Edge
{
	int next, to;
} g[MAXM];
int gn, start[MAXN];

inline void AddEdge(int a, int b)
{
	gn++; g[gn].next = start[a]; start[a] = gn; g[gn].to = b;
}

int n, m, dfn[MAXN], low[MAXN], Belong[MAXN], Bcnt, Index, stk[MAXN], Top;
char opr[10];
bool vis[MAXN], ans;

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
	scanf("%d%d", &n, &m);
	for (int a, b, c, i = 1; i <= m; ++i) 
	{
		scanf("%d%d%d", &a, &b, &c);
		++a; ++b;
		scanf("%s", opr);
		if (opr[0] == 'A')
		{
			if (c == 1)
			{
				AddEdge(a + n, a);
				AddEdge(b + n, b);
				AddEdge(a, b);
				AddEdge(b, a);
			}
			else 
			{
				AddEdge(b, a + n);
				AddEdge(a, b + n);
			}
		}
		else if (opr[0] == 'O')
		{
			if (c == 0)
			{
				AddEdge(a, a + n);
				AddEdge(b, b + n);
				AddEdge(a + n, b + n);
				AddEdge(b + n, a + n);
			}
			else 
			{
				AddEdge(a + n, b);
				AddEdge(b + n, a);
			}
		}
		else
		{
			if (c == 1)
			{
				AddEdge(a, b + n);
				AddEdge(b + n, a);
				AddEdge(a + n, b);
				AddEdge(b, a + n);
			}
			else 
			{
				AddEdge(a, b);
				AddEdge(b, a);
				AddEdge(a + n, b + n);
				AddEdge(b + n, a + n);
			}
		}
	}
	for (int i = 1; i <= 2 * n; ++i) if (!dfn[i]) Tarjan(i);
	ans = true;
	for (int i = 1; i <= n; ++i) if (Belong[i] == Belong[i + n])
	{
		ans = false;
		break;
	}
	if (ans) puts("YES");
	else puts("NO");
	
	return 0;
}
