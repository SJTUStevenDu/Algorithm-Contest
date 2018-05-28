#include <iostream>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <algorithm>
#include <cmath>
 
using namespace std;
 
const int MAXN = 1000000 + 10;
 
int n, dp[MAXN], l, ans, now;
 
inline void checkmax(int &x, int y) {if (x < y) x = y;}
 
int main()
{
    scanf("%d%d", &n, &l);
    for (int x, i = 1; i <= n; ++i)
    {
        scanf("%d", &x);
        now = 0;
        for (int j = 1; j * j <= x; ++j) if (x % j == 0)
        {
            if (j >= l) checkmax(now, dp[j]);
            if (x / j >= l) checkmax(now, dp[x / j]);
        }
        ++now;
        checkmax(ans, now);
        for (int j = 1; j * j <= x; ++j) if (x % j == 0)
        {
            if (j >= l) checkmax(dp[j], now);
            if (x / j >= l) checkmax(dp[x / j], now);
        }
    }
    printf("%d\n", ans);
     
    return 0;
}
