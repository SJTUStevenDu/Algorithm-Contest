#include <iostream>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <algorithm>
#include <cmath>
 
using namespace std;
 
const int MAXN = 100000 + 10;
const long long INF = 10000000000000000LL;
 
long long dp[2][16][2];
int pos[MAXN][16], n, q[MAXN], len[MAXN];
 
void Prepare()
{
    for (int i = 1; i <= n; ++i)
        for (int j1 = -2; j1 <= 2; ++j1) if (j1 + i >= 1 && j1 + i <= n)
            for (int j2 = -2; j2 <= 0; ++j2) if (j2 + q[j1 + i] >= 1 && j2 + q[j1 + i] <= q[i]) pos[i][++len[i]] = j2 + q[j1 + i];
}
 
inline void checkmin(long long &x, long long y)
{
    if (x > y) x = y;
}
 
int main()
{
    scanf("%d", &n);
    for (int i = 1; i <= n; ++i) scanf("%d", &q[i]);
    Prepare();
    int now = 1, pre = 0;
    for (int i = 1; i <= len[1]; ++i) dp[now][i][0] = dp[now][i][1] = q[1] - pos[1][i];
    for (int i = 2; i <= n; ++i)
    {
        now ^= 1; pre ^= 1;
        for (int j = 1; j <= len[i]; ++j)
        {
            dp[now][j][0] = dp[now][j][1] = INF;
            for (int k = 1; k <= len[i - 1]; ++k)
                if (pos[i][j] > pos[i - 1][k]) checkmin(dp[now][j][1], dp[pre][k][0]);
                else if (pos[i][j] == pos[i - 1][k]) checkmin(dp[now][j][1], dp[pre][k][1]), checkmin(dp[now][j][0], dp[pre][k][0]);
                else checkmin(dp[now][j][0], dp[pre][k][1]);
            if (dp[now][j][0] != INF) dp[now][j][0] += q[i] - pos[i][j];
            if (dp[now][j][1] != INF) dp[now][j][1] += q[i] - pos[i][j];
        }
    }
    long long ans = INF;
    for (int i = 1; i <= len[n]; ++i) checkmin(ans, min(dp[now][i][0], dp[now][i][1]));
    printf("%lld\n", ans);
     
    return 0;
}
