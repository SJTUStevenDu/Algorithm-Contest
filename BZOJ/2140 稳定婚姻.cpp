#include <iostream>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <cmath>
#include <fstream>
#include <algorithm>

using namespace std;

const int MAXN = 8000 + 10;
const int MAXM = 20000 + 10;

struct Edge
{
	int next, to;
} g[MAXM * 2];
int gn, start[MAXN];

inline void AddEdge(int a, int b)
{
	gn++; g[gn].next = start[a]; start[a] = gn; g[gn].to = b;
}

string s[MAXN], bb[MAXN], gg[MAXN], t1, t2;
char tmp[MAXN];
int n, m, boy[MAXN], girl[MAXN];
int dfn[MAXN], low[MAXN], Belong[MAXN], stk[MAXN], Top, Bcnt, Index;
bool vis[MAXN];

inline int GetPos(string x)
{
	int l = 1, r = 2 * n;
	while (l <= r)
	{
		int mid = (l + r) >> 1;
		if (s[mid] == x) return mid;
		if (s[mid] < x) l = mid + 1;
		else r = mid - 1;
	}
}

void Tarjan(int p)
{
	dfn[p] = low[p] = ++Index;
	vis[p] = 1;
	stk[++Top] = p;
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
		Bcnt++;
		int i = -1;
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
	for (int i = 1; i <= 2 * n; ++i) 
	{
		scanf("%s", tmp);
		s[i] = tmp;
	}
	for (int i = 1; i <= n; ++i)
	{
		gg[i] = s[i * 2 - 1];
		bb[i] = s[i * 2];
	}
	sort(s + 1, s + 1 + 2 * n);
	for (int i = 1; i <= n; ++i) boy[i] = GetPos(bb[i]), girl[i] = GetPos(gg[i]);
	for (int i = 1; i <= n; ++i) AddEdge(girl[i], boy[i]);
	scanf("%d", &m);
	for (int i = 1; i <= m; ++i) 
	{
		scanf("%s", tmp); t1 = tmp;
		scanf("%s", tmp); t2 = tmp;
		AddEdge(GetPos(t2), GetPos(t1));
	}
	for (int i = 1; i <= n * 2; ++i) if (!dfn[i]) Tarjan(i);
	for (int i = 1; i <= n; ++i)
	{
		if (Belong[girl[i]] == Belong[boy[i]]) puts("Unsafe");
		else puts("Safe");
	}
	
	return 0;
}
