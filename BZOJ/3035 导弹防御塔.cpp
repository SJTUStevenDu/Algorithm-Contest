#include <iostream>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <cmath>
#include <fstream>
#include <algorithm>

using namespace std;

const int MAXN = 2500 + 10;
const int MAXM = 50 + 10;
const double eps = 1e-8;

struct Edge
{
	int next, to;
} g[MAXN * MAXM];
int gn, start[MAXN];

inline void AddEdge(int a, int b)
{
	gn++; g[gn].next = start[a]; start[a] = gn; g[gn].to = b;
}

struct Node
{
	int x, y;
} a[MAXM], b[MAXM];

struct NNode
{
	int x; double y;
} c[MAXN];

double dist(Node A, Node B)
{
	return sqrt((A.x - B.x) * (A.x - B.x) * 1.0 + (A.y - B.y) * (A.y - B.y) * 1.0);
}

int n, m, Link[MAXN];
double t1, t2, v;
bool vis[MAXN];

bool dfs(int p)
{
	for (int i = start[p]; i; i = g[i].next)
	{
		int v = g[i].to;
		if (vis[v]) continue;
		vis[v] = 1;
		if (!Link[v] || dfs(Link[v])) 
		{
			Link[v] = p;
			return 1;
		}
	}
	return 0;
}

int main()
{
	scanf("%d%d%lf%lf%lf", &n, &m, &t1, &t2, &v);
	t1 /= 60;
	for (int i = 1; i <= m; ++i) scanf("%d%d", &a[i].x, &a[i].y);
	for (int i = 1; i <= n; ++i) scanf("%d%d", &b[i].x, &b[i].y);
	int num = m * n;
	for (int i = 1; i <= m; ++i)
		for (int j = 1; j <= n; ++j) 
			c[(i - 1) * n + j].x = j, c[(i - 1) * n + j].y = (t1 + t2) * (i - 1) + t1;
	double l = t1, r = 30000;
	while (l + eps < r)
	{
		double mid = (l + r) / 2;
		memset(start, 0, sizeof(start));
		memset(Link, 0, sizeof(Link));
		gn = 0;
		for (int i = 1; i <= m; ++i)
			for (int j = 1; j <= num; ++j) if (c[j].y + dist(a[i], b[c[j].x]) / v <= mid) AddEdge(i, j);
		bool flag = true;
		for (int i = 1; i <= m; ++i)
		{
			memset(vis, 0, sizeof(vis));
			if (!dfs(i)) {flag = false; break;}
		}
		if (flag) r = mid; else l = mid;
	}
	printf("%.6lf\n", l);
	
	return 0;
}
