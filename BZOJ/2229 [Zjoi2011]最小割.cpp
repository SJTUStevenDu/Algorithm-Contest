#include <iostream>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <cmath>
#include <fstream>
#include <algorithm>
#include <vector>

using namespace std;

const int MAXN = 150 + 10;
const int MAXM = 6000 + 10;
const int INF = 0x7FFFFFFF >> 2;

struct Edge
{
	int next, to, w;
} g[MAXM];
int gn, start[MAXN];

inline void AddEdge(int a, int b, int c)
{
	gn++; g[gn].next = start[a]; start[a] = gn; g[gn].to = b; g[gn].w = c;
	gn++; g[gn].next = start[b]; start[b] = gn; g[gn].to = a; g[gn].w = c;
}

int n, m, e[MAXM][3], S, T, N, h[MAXN], vh[MAXN], q[MAXN], head, tail, f[MAXN][MAXN], maxflow, tst, Q;
bool vis[MAXN], hk[MAXN];

int Aug(int p, int flow)
{
	if (p == T) return flow;
	int minnode = N - 1, ret = flow;
	for (int i = start[p]; i; i = g[i].next) if (g[i].w > 0)
	{
		int v = g[i].to;
		if (h[v] + 1 == h[p])
		{
			int tmp = Aug(v, min(ret, g[i].w));
			g[i].w -= tmp;
			g[i ^ 1].w += tmp;
			ret -= tmp;
			if (h[S] >= N || ret == 0) return flow - ret;
		}
		if (g[i].w) minnode = min(minnode, h[v]);
	}
	if (ret == flow)
	{
		--vh[h[p]];
		if (vh[h[p]] == 0) h[S] = N;
		++vh[h[p] = minnode + 1];
	}
	return flow - ret;
}

void Work(vector <int> M)
{
	if (M.size() <= 1) return;
	memset(start, 0, sizeof(start));
	gn = 1;
	for (int i = 1; i <= m; ++i) AddEdge(e[i][0], e[i][1], e[i][2]);
	memset(vh, 0, sizeof(vh));
	memset(h, 0, sizeof(h));
	maxflow = 0;
	S = M[0]; T = M[1];
	while (h[S] < N) maxflow += Aug(S, INF);
	head = 0; tail = 1; q[0] = S;
	memset(vis, 0, sizeof(vis));
	memset(hk, 0, sizeof(hk));
	while (head != tail)
	{
		int p = q[head++];
		for (int i = start[p]; i; i = g[i].next) if (g[i].w > 0)
		{
			int v = g[i].to;
			if (!vis[v]) q[tail++] = v, vis[v] = 1;
		}
	}
	for (int i = 0; i < tail; ++i) hk[q[i]] = 1;
	for (int i = 1; i <= n; ++i)
		for (int j = i + 1; j <= n; ++j) if (hk[i] != hk[j]) 
		{
			f[i][j] = min(f[i][j], maxflow);
			f[j][i] = min(f[j][i], maxflow);
		}
	vector <int> M1, M2;
	M1.clear(); M2.clear();
	for (int i = 0; i < M.size(); ++i) if (!hk[M[i]]) M1.push_back(M[i]); else M2.push_back(M[i]);
	Work(M1); Work(M2);
}

int main()
{
	scanf("%d", &tst);
	while (tst--)
	{
		vector <int> A;
		A.clear();
		scanf("%d%d", &n, &m);
		N = n;
		for (int i = 1; i <= n; ++i) A.push_back(i);
		for (int a, b, c, i = 1; i <= m; ++i) scanf("%d%d%d", &e[i][0], &e[i][1], &e[i][2]);
		memset(f, 63, sizeof(f));
		Work(A);
		scanf("%d", &Q);
		while (Q--)
		{
			int x, cnt = 0;
			scanf("%d", &x);
			for (int i = 1; i <= n; ++i)
				for (int j = i + 1; j <= n; ++j) if (f[i][j] <= x) ++cnt;
			printf("%d\n", cnt);
		}
		printf("\n");
	}
	
	return 0;
}
