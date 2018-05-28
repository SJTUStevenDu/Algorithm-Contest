#include <iostream>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <algorithm>
#include <cmath>

using namespace std;

long long n, m, k;
int mod;

long long QuickMod(long long a, long long b)
{
	long long ret = 1;
	while (b)
	{
		if (b & 1) ret = ret * a % mod;
		b >>= 1;
		a = a * a % mod;
	}
	return ret;
}

int main()
{
	scanf("%lld%lld%lld%d", &n, &k, &m, &mod);
	long long ans = (n % mod) * QuickMod(m, k - 1) % mod;
	long long ans2 = m * (m + 1) / 2;
	ans2 %= mod;
	ans2 = ans2 * (k - 1) % mod * QuickMod(m, k - 2);
	ans = ((ans - ans2) % mod + mod) % mod;
	printf("%lld\n", ans);
	
	return 0;
}
