#include <iostream>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <algorithm>
#include <cmath>
 
using namespace std;
 
const int MOD = 19940417;
const int TWO = 9970209;
const int SIX = 3323403;
 
long long n, m, ans;
 
long long sumsqr(long long n)
{
    return n * (n + 1) % MOD * (2 * n + 1) % MOD * SIX % MOD;
}
 
long long calc(long long m, long long n) // sigma ([n/i] * i) (i = 1..m)
{
    long long l, r, res = 0;
    for (l = 1; l <= m; l = r + 1)
    {
        long long p = n / l;
        r = min(n / p, m);
        res += (l + r) * (r - l + 1) % MOD * TWO % MOD * p % MOD;
        res %= MOD;
    }
    return res;
}
 
int main()
{
    scanf("%lld%lld", &n, &m);
    if (n < m) swap(n, m);
    ans = (n * n - calc(n, n)) % MOD * ((m * m - calc(m, m)) % MOD);
    ans += -m * m % MOD * n % MOD + calc(m, n) * m % MOD + calc(m, m) * n % MOD;
    ans %= MOD;
    long long l, r, p1, p2;
    for (l = 1; l <= m; l = r + 1)
    {
        p1 = n / l; p2 = m / l;
        r = min(m, min(n / p1, m / p2));
        ans += -p1 * p2 % MOD * ((sumsqr(r) - sumsqr(l - 1)) % MOD) % MOD;
        ans %= MOD;
    }
    ans = (ans % MOD + MOD) % MOD;
    printf("%lld\n", ans);
     
    return 0;
}
