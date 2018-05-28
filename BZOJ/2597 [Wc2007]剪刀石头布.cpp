#include <iostream>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <cmath>
#include <algorithm>
#include <fstream>
 
using namespace std;
 
const int MAXC = 100 + 10;
const int MAXN = MAXC * MAXC / 2;
const int MAXM = 10 * MAXC * MAXC;
const int INF = 0x7FFFFFFF >> 2;
 
struct Edge
{
    int next, to, w, cost;
} g[MAXM];
int gn, start[MAXN];
 
inline void AddEdge(int a, int b, int c, int d)
{
    gn++; g[gn].next = start[a]; start[a] = gn; g[gn].to = b; g[gn].w = c; g[gn].cost = d;
    gn++; g[gn].next = start[b]; start[b] = gn; g[gn].to = a; g[gn].w = 0; g[gn].cost = -d;
}
 
int n, m, cur[MAXC][MAXC], tot, S, T, ind[MAXN], path[MAXN];
int q[MAXN], head, tail, dist[MAXN], ans, e[MAXN][2];
bool vis[MAXN];
 
bool SPFA()
{
    memset(vis, 0, sizeof(vis));
    memset(dist, 63, sizeof(dist));
    head = 0; tail = 1; q[head] = S; vis[S] = 0; dist[S] = 0;
    while (head != tail)
    {
        int p = q[head++];
        if (head == MAXN) head = 0;
        vis[p] = 0;
        for (int i = start[p]; i; i = g[i].next) if (g[i].w > 0)
        {
            int v = g[i].to;
            if (dist[v] > dist[p] + g[i].cost)
            {
                dist[v] = dist[p] + g[i].cost;
                path[v] = i;
                if (!vis[v])
                {
                    vis[v] = 1;
                    if (dist[q[head]] < dist[v])
                    {
                        q[tail++] = v;
                        if (tail == MAXN) tail = 0;
                    }
                    else
                    {
                        --head; if (head == -1) head += MAXN;
                        q[head] = v;
                    }
                }
            }
        }
    }
    return dist[T] < INF;
}
 
void Aug()
{
    int delta = INF, now = T;
    while (now != S)
    {
        int i = path[now];
        delta = min(delta, g[i].w);
        now = g[i ^ 1].to;
    }
    now = T;
    ans += dist[T] * delta;
    while (now != S)
    {
        int i = path[now];
        g[i].w -= delta;
        g[i ^ 1].w += delta;
        now = g[i ^ 1].to;
    }
}
 
int main()
{
    gn = 1;
    scanf("%d", &n);
    m = n * (n - 1) / 2;
    for (int i = 1; i <= n; ++i)
        for (int j = 1; j <= n; ++j) scanf("%d", &cur[i][j]);
    S = n + m + 1; T = S + 1;
    for (int i = 1; i <= n; ++i)
        for (int j = 1; j < i; ++j)
        {
            ++tot;
            if (cur[i][j] == 2) e[tot][0] = gn + 1, AddEdge(tot, i + m, 1, 0), e[tot][1] = gn + 1, AddEdge(tot, j + m, 1, 0), ++ind[i], ++ind[j];
            else if (cur[i][j] == 1) AddEdge(tot, i + m, 1, 0), ++ind[i];
            else AddEdge(tot, j + m, 1, 0), ++ind[j];
        }
    for (int i = 1; i <= m; ++i) AddEdge(S, i, 1, 0);
    for (int i = 1; i <= n; ++i) 
        for (int j = 1; j <= ind[i]; ++j) AddEdge(i + m, T, 1, 2 * j - 1);
    while (SPFA()) Aug();
    printf("%d\n", n * (n - 1) * (n - 2) / 6 + m / 2 - ans / 2);
    tot = 0;
    for (int i = 1; i <= n; ++i)
        for (int j = 1; j < i; ++j)
        {
            ++tot;
            if (cur[i][j] == 2)
            {
                if (g[e[tot][0]].w == 0) cur[i][j] = 1, cur[j][i] = 0;
                else cur[i][j] = 0, cur[j][i] = 1;
            }
        }
    for (int i = 1; i <= n; ++i)
    {
        for (int j = 1; j < n; ++j) printf("%d ", cur[i][j]);
        printf("%d\n", cur[i][n]);
    }
     
    return 0;
}
