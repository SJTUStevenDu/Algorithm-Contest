#include <iostream>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <algorithm>
#include <cmath>
 
using namespace std;
 
const int MAXN = 50000 + 10;
 
int prm[MAXN / 10], Top;
int s[MAXN];
int T, a, b, c, d, k;
bool vis[MAXN];
 
void Prepare()
{
    int m = (int)sqrt(50000.0) + 1;
    for (int i = 2; i <= m; ++i)
    {
        if (!vis[i]) prm[++Top] = i;
        for (int j = 1; j <= Top && prm[j] * i <= m; ++j)
        {
            vis[i * prm[j]] = 1;
            if (i % prm[j] == 0) break;
        }
    }
    s[1] = 1;
    for (int i = 2; i <= 50000; ++i)
    {
        bool flag = true;
        int x = i, cnt = 0;
        for (int j = 1; j <= Top; ++j)
        {
            if (!flag) break;
            if (x % prm[j] == 0)
            {
                x /= prm[j];
                if (x % prm[j] == 0) flag = false;
                ++cnt;
            }
        }
        if (x > 1) ++cnt;
        if (!flag) s[i] = 0;
        else if (cnt & 1) s[i] = -1;
        else s[i] = 1;
        s[i] += s[i - 1];
    }
}
 
long long Solve(int x, int y, int k)
{
    x /= k; y /= k;
    if (x > y) swap(x, y);
    int p1, p2, l, r;
    long long res = 0;
    for (l = 1; l <= x; l = r + 1)
    {
        p1 = x / l; p2 = y / l;
        r = min(x / p1, y / p2);
        r = min(r, x);
        res += (long long)(s[r] - s[l - 1]) * (long long)p1 * (long long)p2;
    }
    return res;
}
 
int main()
{
    Prepare();
    scanf("%d", &T);
    while (T--)
    {
        scanf("%d%d%d%d%d", &a, &b, &c, &d, &k);
        printf("%lld\n", Solve(b, d, k) - Solve(a - 1, d, k) - Solve(b, c - 1, k) + Solve(a - 1, c - 1, k));
    }
     
    return 0;
}
