#include <iostream>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <cmath>
#include <algorithm>
#include <fstream>
 
using namespace std;
 
const int MAXC = 11;
const int MAXN = 1100;
const int MAXM = 2200;
const int INF = 0x7FFFFFFF >> 2;
 
struct Rec
{
    int r[MAXM], lim;
    int get(int a, int b)
    {
        return r[a * lim + b];
    }
    void set(int a, int b, int c)
    {
        r[a * lim + b] = c;
    }
} dp[MAXM];
 
int n, m, ans, fa[MAXN][MAXC], cost[MAXN][MAXC], flow[MAXN][MAXN], c[MAXN];
bool type[MAXN];
 
int calc(int a, int na, int S)
{
    int ca = 0, cb = 0;
    for (int i = 1; i <= n; ++i, S >>= 1) 
    {
        if (S & 1) ca += cost[a][i];
        else cb += cost[a][i];
    }
    if (na == 1) return ca + (type[a] ? 0 : c[a]);
    else return cb + (type[a] ? c[a] : 0);
}
 
int DP(int i, int j, int k, int h)
{
    int ret = dp[i].get(j, k);
    if (ret == 0)
    {
        if (h)
        {
            ret = INF;
            int tmp, maxs, nowk;
            nowk = (k << 1) + (j < ((1 << h) - j));
            maxs = 1 << (h - 1);
            for (int a = max(0, j - maxs); a <= j && a <= maxs; ++a)
            {
                tmp = DP(i << 1, a, nowk, h - 1);
                tmp += DP(i << 1 | 1, j - a, nowk, h - 1);
                ret = min(ret, tmp);
            }
        }
        else ret = calc(i - m + 1, j, k);
        dp[i].set(j, k, ret);
    }
    return ret;
}
 
int main()
{
    scanf("%d", &n);
    m = (1 << n);
    for (int a, i = 1; i <= m; ++i)
    {
        scanf("%d", &a);
        type[i] = (a == 0);
    }
    for (int i = 1; i <= m; ++i) scanf("%d", &c[i]);
    for (int i = 1; i <= m; ++i)
        for (int j = i + 1; j <= m; ++j)
        {
            scanf("%d", &flow[i][j]);
            flow[j][i] = flow[i][j];
        }
    ans = INF;
    for (int i = 1; i <= m; ++i)
    {
        int k = i + m - 1;
        for (int j = 1; j <= n; ++j) 
        {
            k >>= 1;
            fa[i][j] = k;
        }
    }
    for (int k = 1; k <= n + 1; ++k)
    {
        int a = 1 << (k - 1);
        int b = (1 << k) - 1;
        for (int p = a; p <= b; ++p)
        {
            dp[p].lim = 1 << (k - 1);
            memset(dp[p].r, 0, sizeof(dp[p].r));
        }
    }
    for (int i = 1; i <= m; ++i)
        for (int j = i + 1; j <= m; ++j)
        {
            for (int k = 1; k <= n; ++k)
                if (fa[i][k] == fa[j][k])
                {
                    cost[j][k] += flow[i][j];
                    cost[i][k] += flow[i][j];
                    break;
                }
        }
    for (int i = 0; i <= m; ++i)
    {
        int tmp = DP(1, i, 0, n);
        ans = min(ans, tmp);
    }
    printf("%d\n", ans);
     
    return 0;
}
