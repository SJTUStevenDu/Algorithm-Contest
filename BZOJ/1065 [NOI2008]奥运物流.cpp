#include <cstdio>
#include <cstdlib>
#include <algorithm>
#include <cstring>
#include <string>
 
using namespace std;
 
const int MAXN = 80;
double f[MAXN][MAXN][MAXN], g[MAXN][MAXN][MAXN],C[MAXN], F[MAXN], K[MAXN], ans;
int pre[MAXN], n, m;
 
void Dp(int u, int d)
{
    for (int v = 2; v<=n; ++v) if (pre[v] == u) Dp(v, d + 1);
    for (int dd = min(2, d); dd<=d; ++dd)
    {
        for (int j = 0; j<=m; ++j) F[j] = 0;
        for (int v = 2; v<=n; ++v) if (pre[v] == u)
        for (int j = m; j > -1; --j)
        for (int k = j; k > -1; --k)
            F[j] = max(F[j], F[k] + g[v][j - k][dd]);
        for (int j = 0; j<=m; ++j)
            f[u][j][dd] = F[j] + C[u] * K[dd];
    }
    if (d > 1)
    {
        for (int j = 0; j<=m; ++j) F[j] = 0;
        for (int v = 2; v<=n; ++v) if (pre[v] == u)
        for (int j = m; j > -1; --j)
        for (int k = j; k > -1; --k)
            F[j] = max(F[j], F[k] + g[v][j - k][1]);
        for (int j = 1; j<=m; ++j)
            f[u][j][1] = F[j - 1] + C[u] * K[1];
    }
    for (int j = 0; j<=m; ++j)
    for (int dd = 0; dd < d; ++dd)
        g[u][j][dd] = max(f[u][j][dd + 1], f[u][j][1]);
    return;
}
 
int main()
{
    scanf("%d%d%lf", &n, &m, K + 1);
    for (int i = 2; i<=n; ++i) K[i] = K[i - 1] * K[1];
    for (int i = 1; i<=n; ++i) scanf("%d", pre + i);
    for (int i = 1; i<=n; ++i) scanf("%lf", C + i);
    for (int ths = pre[1], len = 2; ths - 1; ths = pre[ths], ++len)
    {
        for (int i = 1; i<=n; ++i)
        for (int j = 0; j<=m; ++j)
        for (int k = 0; k<=n; ++k)
            f[i][j][k] = g[i][j][k] = 0;
        int tmp = pre[ths]; double Now = 0;
        pre[ths] = 1;
        for (int v = 2; v<=n; ++v) if (pre[v] == 1) Dp(v, 1);
        for (int j = 0; j<=m; ++j) F[j] = 0;
        for (int v = 2; v<=n; ++v) if (pre[v] == 1)
        for (int j = m; j > -1; --j)
        for (int k = j; k > -1; --k)
            F[j] = max(F[j], F[k] + f[v][j - k][1]);
        for (int j = 0; j < m; ++j) Now = max(Now, F[j]);
        if (tmp == 1) Now = max(Now, F[m]);
        ans = max(ans, (Now + C[1]) / (1 - K[len]));
        pre[ths] = tmp;
    }
    printf("%.2lf\n", ans);
    return 0;
}