#include <iostream>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <cmath>
#include <algorithm>
#include <fstream>
 
using namespace std;
 
const int MAXN = 100 + 10;
const double INF = 1e100;
 
int n;
double ans = -INF, S, v0[MAXN], v1[MAXN], ansL;
 
void check(double L)
{
    if (L < 0 || L > S) return;
    double mint = INF;
    for (int i = 1; i < n; ++i) mint = min(mint, L / v0[i] + (S - L) / v1[i]);
    mint = mint - (L / v0[n] + (S - L) / v1[n]);
    if (mint > ans)
    {
        ans = mint;
        ansL = L;
    }
}
 
int main()
{
    scanf("%lf%d", &S, &n);
    for (int i = 1; i <= n; ++i) scanf("%lf%lf", &v0[i], &v1[i]);
    for (int i = 1; i <= n; ++i) v0[i] /= 3.6, v1[i] /= 3.6;
    check(0);
    check(S);
    for (int i = 1; i <= n; ++i)
        for (int j = 1; j <= n; ++j)
        {
            double k1 = 1.0 / v0[i] - 1.0 / v1[i], b1 = S / v1[i];
            double k2 = 1.0 / v0[j] - 1.0 / v1[j], b2 = S / v1[j];
            if (fabs(k1 - k2) < 1e-8) continue;
            check((b2 - b1) / (k1 - k2));
        }
    if (ans < 0) puts("NO");
    else printf("%.2lf %.2lf %.0lf\n", ansL, S - ansL, ans * 1000);
     
    return 0;
}
