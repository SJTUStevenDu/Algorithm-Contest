#include <iostream>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <cmath>
#include <algorithm>
#include <fstream>

using namespace std;

const int MAXN = 500 + 10;
const int MAXM = 5000 + 10;

struct Edge
{
	int u, v, w;
} g[MAXM];

inline bool cmp(Edge A, Edge B)
{
	return A.w < B.w;
}

int father[MAXN], n, m, l, r, S, T, ans1, ans2;

int getfather(int x)
{
	return father[x] == x ? x : getfather(father[x]);
}

void Union(int x, int y)
{
	int fx = getfather(x);
	int fy = getfather(y);
	if (fx != fy) father[fx] = fy;
}

int gcd(int n, int m)
{
	while (m)
	{
		int tmp = n % m;
		n = m;
		m = tmp;
	}
	return n;
}

int main()
{
	scanf("%d%d", &n, &m);
	for (int i = 1; i <= m; ++i) scanf("%d%d%d", &g[i].u, &g[i].v, &g[i].w);
	scanf("%d%d", &S, &T);
	sort(g + 1, g + 1 + m, cmp);
	for (int i = 1; i <= n; ++i) father[i] = i;
	for (int i = 1; i <= m; ++i) Union(g[i].u, g[i].v);
	if (getfather(S) != getfather(T))
	{
		puts("IMPOSSIBLE");
		return 0;
	}
	else ans1 = g[1].w, ans2 = g[m].w;
	for (l = 1; l <= m; ++l)
	{
		for (int i = 1; i <= n; ++i) father[i] = i;
		for (r = l; r <= m; ++r)
		{
			Union(g[r].u, g[r].v);
			if (getfather(S) == getfather(T)) break;
			if (ans2 * g[l].w < g[r].w * ans1) break;
		}
		if (getfather(S) != getfather(T)) continue;
		if (ans2 * g[l].w < g[r].w * ans1) continue;
		ans1 = g[l].w; ans2 = g[r].w;
	}
	int d = gcd(ans1, ans2);
	ans1 /= d; ans2 /= d;
	if (ans1 == 1) printf("%d\n", ans2);
	else printf("%d/%d\n", ans2, ans1);
	
	return 0;
}
