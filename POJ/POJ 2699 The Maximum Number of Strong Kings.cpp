#include <iostream>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <algorithm>
#include <cmath>
#include <string>
#include <sstream>

using namespace std;

const int MAXN = 100 + 10;
const int MAXE = 10000 + 10;
const int INF = 0x7FFFFFFF >> 2;

struct Edge
{
	int next, to, w;
} g[MAXE];
int gn, start[MAXN], now[MAXN];

inline void AddEdge(int a, int b, int c)
{
	gn++; g[gn].next = start[a]; start[a] = gn; g[gn].to = b; g[gn].w = c;
	gn++; g[gn].next = start[b]; start[b] = gn; g[gn].to = a; g[gn].w = 0;
}

int n, m, ans, h[MAXN], vh[MAXN], flow, len, S, T, tst, sc[MAXN], N, Max[MAXN];
char str[MAXE];

int Aug(int p, int flow)
{
	if (p == T) return flow;
	int ret = 0;
	for (int i = now[p]; i; now[p] = i = g[i].next)
	{
		int v = g[i].to;
		if (h[v] + 1 == h[p] && g[i].w > 0)
		{
			int tmp = Aug(v, min(g[i].w, flow - ret));
			ret += tmp;
			g[i].w -= tmp;
			g[i ^ 1].w += tmp;
			if (ret == flow) return flow;
		}
	}
	--vh[h[p]]; if (!vh[h[p]]) h[S] = N;
	++h[p]; ++vh[h[p]]; now[p] = start[p];
	return ret;
}

void Init()
{
	gets(str);
	stringstream ss(str);
	n = 0;
	int j;
	while (ss >> j) sc[++n]=j;
/*	gets(str);
	len = strlen(str);
	n = 1;
	int ret = 0;
	for (int i = 0; i < len; ++i) 
	{
		if (str[i] == ' ') {if (str[i - 1] != ' ') sc[n++] = ret; ret = 0;}
		else ret = ret * 10 + str[i] - '0';
	}
	sc[n] = ret;*/
}

bool check()
{
	gn = 1; flow = 0;
	memset(start, 0, sizeof(start));
	memset(h, 0, sizeof(h));
	memset(vh, 0, sizeof(vh)); vh[0] = N;
	for (int i = 1; i <= m; ++i) AddEdge(S, i, 1);
	for (int i = 1; i <= n; ++i) AddEdge(i + m, T, sc[i]);
	for (int i = 1; i <= n; ++i)
		if (i > ans) AddEdge(i + m + n, i + m, sc[i]);
		else if (Max[i] < sc[i]) AddEdge(i + m + n, i + m, sc[i] - Max[i]);
		else if (Max[i] == sc[i]) continue;
		else return false;
	int tot = 0;
	for (int i = 1; i <= n; ++i) 
		for (int j = i + 1; j <= n; ++j) 
		{
			++tot;
			if (j <= ans && sc[j] < sc[i]) AddEdge(tot, j + m, 1);
			else AddEdge(tot, i + m + n, 1), AddEdge(tot, j + m + n, 1);
		}
	for (int i = 1; i <= N; ++i) now[i] = start[i];
	while (h[S] < N) flow += Aug(S, INF);
	return flow == tot;
}

void Solve()
{
	m = n * (n - 1) / 2;
	S = n * 2 + m + 1; T = S + 1; N = T;
	sort(sc + 1, sc + 1 + n);
	for (int i = 1; i <= n / 2; ++i) swap(sc[i], sc[n - i + 1]);
	for (int i = 1; i <= n; ++i) Max[i] = 0;
	for (int i = 1; i <= n; ++i) 
		for (int j = 1; j < i; ++j) if (sc[j] > sc[i]) Max[i]++;
	for (ans = 1; ans <= n; ++ans) if (!check()) break;
	printf("%d\n", ans - 1);
}

int main()
{
	scanf("%d\n", &tst);
	while (tst--)
	{
		Init();
		Solve();
	}
	
	return 0;
}
