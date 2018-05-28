#include <iostream>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <cmath>
#include <algorithm>
#include <fstream>
 
using namespace std;
 
const int MAXC = 40 + 10;
const int MAXN = MAXC * MAXC * MAXC;
const int MAXE = 600000 + 10;
const int INF = 0x7FFFFFFF >> 2;
const int dx[4] = {1, 0, -1, 0};
const int dy[4] = {0, 1, 0, -1};
 
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
 
int n, m, l, S, T, N, h[MAXN], vh[MAXN], ans, c[MAXC][MAXC][MAXC], d;
 
int Aug(int p, int flow)
{
    if (p == T) return flow;
    int ret = 0;
    for (int i = now[p]; i; now[p] = i = g[i].next)
    {
        int v = g[i].to;
        if (h[p] == h[v] + 1 && g[i].w > 0)
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
 
inline int f(int i, int j, int k)
{
    return (k - 1) * n * m + (i - 1) * m + j;
}
 
int main()
{
    scanf("%d%d%d", &n, &m, &l);
    scanf("%d", &d);
    gn = 1;
    for (int k = 1; k <= l; ++k)
        for (int i = 1; i <= n; ++i)
            for (int j = 1; j <= m; ++j) scanf("%d", &c[i][j][k]);
    S = f(n, m, l + 1) + 1; T = S + 1; N = T;
    for (int i = 1; i <= n; ++i)
        for (int j = 1; j <= m; ++j) AddEdge(S, f(i, j, 1), INF), AddEdge(f(i, j, l + 1), T, INF);\
    for (int k = 1; k <= l; ++k)
    {
        for (int i = 1; i <= n; ++i)
            for (int j = 1; j <= m; ++j) AddEdge(f(i, j, k), f(i, j, k + 1), c[i][j][k]);    
    }
    for (int i = 1; i <= n; ++i)
        for (int j = 1; j <= m; ++j)
        {
            for (int kk = 0; kk < 4; ++kk)
            {
                int x = i + dx[kk], y = j + dy[kk];
                if (x <= 0 || x > n || y <= 0 || y > m) continue;
                for (int k = d + 1; k <= l + 1; ++k) AddEdge(f(i, j, k), f(x, y, k - d), INF);
            }
        }
    vh[0] = N;
    for (int i = 1; i <= N; ++i) now[i] = start[i];
    while (h[S] < N) ans += Aug(S, INF);
    printf("%d\n", ans);
     
    return 0;
}
