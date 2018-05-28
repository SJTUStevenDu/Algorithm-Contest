#include <iostream>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <cmath>
#include <fstream>
#include <algorithm>
 
using namespace std;
 
const int MAXN = 50000 + 10;
const int INF = 1000000000;
const int MOD = 99991;
 
struct Edge
{
    int next, to, w;
} g[MAXN * 100];
int gn, start[MAXN];
 
inline void AddEdge(int a, int b, int c)
{
    gn++; g[gn].next = start[a]; start[a] = gn; g[gn].to = b; g[gn].w = c;
}
 
int n, a[MAXN], h[MOD], num[MAXN], tot, nxt[MAXN], q[MAXN], dist[MAXN], head, tail;
long long vv[MAXN];
char S[MAXN][15];
bool vis[MAXN];
 
inline void Insert(long long x, int y)
{
    int mm = x % MOD;
    ++tot; nxt[tot] = h[mm]; h[mm] = tot; vv[tot] = x; num[tot] = y;
}
 
inline int Find(long long x)
{
    int mm = x % MOD;
    for (int i = h[mm]; i; i = nxt[i]) if (vv[i] == x) return num[i];
    return -1;
}
 
inline long long trans(char ss[])
{
    long long ret = 0;
    for (int i = 1; i <= 10; ++i) ret = ret * 10 + (long long)(ss[i] - '0');
    return ret;
}
 
inline int lcp(char A[], char B[])
{
    for (int i = 1; i <= 10; ++i) if (A[i] != B[i]) return i;
}
 
void SPFA()
{
    for (int i = 1; i <= n; ++i) dist[i] = INF;
    dist[1] = 0; q[head] = 1; vis[1] = 1; tail = 1;
    while (head != tail)
    {
        int p = q[head++];
        vis[p] = 0;
        if (head == MAXN) head = 0;
        for (int i = start[p]; i; i = g[i].next)
        {
            int v = g[i].to;
            if (dist[v] > dist[p] + g[i].w)
            {
                dist[v] = dist[p] + g[i].w;
                if (!vis[v])
                {
                    vis[v] = 1;
                    if (dist[v] > dist[q[head]])
                    {
                        q[tail++] = v;
                        if (tail == MAXN) tail = 0;
                    }
                    else
                    {
                        --head; if (head < 0) head += MAXN;
                        q[head] = v;
                    }
                }
            }
        }
    }
}
 
int main()
{
    scanf("%d", &n);
    for (int i = 1; i <= 10; ++i) scanf("%d", &a[i]);
    for (int i = 1; i <= n; ++i) scanf("%s", S[i] + 1);
    for (int i = 1; i <= n; ++i) Insert(trans(S[i]), i);
    for (int i = 1; i <= n; ++i)
    {
        for (int j = 1; j <= 10; ++j)
        {
            int tmp = S[i][j] - '0';
            for (int k = 0; k <= 9; ++k) if (k != tmp)
            {
                S[i][j] = k + '0';
                int l = Find(trans(S[i]));
                S[i][j] = tmp + '0';
                if (l != -1) AddEdge(i, l, a[lcp(S[i], S[l])]);
            }
        }
        for (int j = 1; j <= 10; ++j)
            for (int k = 1; k < j; ++k)
            {
                if (S[i][j] == S[i][k]) continue;
                swap(S[i][j], S[i][k]);
                int l = Find(trans(S[i]));
                swap(S[i][j], S[i][k]);
                if (l != -1) AddEdge(i, l, a[lcp(S[i], S[l])]);
            }
    }
    SPFA();
    if (dist[n] == INF) puts("-1");
    else printf("%d\n", dist[n]);
     
    return 0;
}
