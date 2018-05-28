#include <iostream>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <algorithm>
#include <cmath>
 
using namespace std;
 
const int MAXN = 500 + 10;
const int MAXM = MAXN * MAXN;
const double eps = 1e-8;
 
double a[MAXN][MAXN], v[MAXN], w[MAXM];
int n, m, e[MAXM][2], d[MAXN], ed[MAXN][MAXN];
double ans;
 
void gauss()
{
    for (int i = 1; i <= n; ++i)
    {
        int l = -1;
        for (int j = i; j <= n; ++j) if (fabs(a[i][j]) > eps) {l = j; break;}
        for (int j = 1; j <= n + 1; ++j) swap(a[i][j], a[l][j]);
        for (int j = i + 1; j <= n; ++j)
        {
            double rat = a[j][i] / a[i][i];
            for (int k = i; k <= n + 1; ++k) a[j][k] -= a[i][k] * rat;
        }
    }
    for (int i = n; i; --i)
    {
        v[i] = a[i][n + 1];
        for (int j = i + 1; j <= n; ++j) v[i] -= v[j] * a[i][j];
        v[i] /= a[i][i];
    }
}
 
int main()
{
    scanf("%d%d", &n, &m);
    for (int p, q, i = 1; i <= m; ++i)
    {
        scanf("%d%d", &p, &q);
        e[i][0] = p; e[i][1] = q;
        ed[p][++d[p]] = q;
        if (p != q) ed[q][++d[q]] = p;
    }
    for (int i = 1; i < n; ++i)
    {
        a[i][i] = 1.0;
        for (int j = 1; j <= d[i]; ++j)
        {
            int k = ed[i][j];
            if (k == n) continue;
            a[i][k] -= 1.0 / d[k];
        }
    }
    --n;
    a[1][n + 1] = 1;
    gauss();
    for (int i = 1; i <= m; ++i)
    {
        int p = e[i][0], q = e[i][1];
        w[i] = v[p] / d[p] + v[q] / d[q];
    }
    sort(w + 1, w + 1 + m);
    for (int i = 1; i <= m; ++i) ans += w[i] * (m - i + 1);
    printf("%.3lf\n", ans);
     
    return 0;
}
