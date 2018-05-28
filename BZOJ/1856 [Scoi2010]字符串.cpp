#include <iostream>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <cmath>
#include <fstream>
#include <algorithm>

using namespace std;

const int MAXN = 2000000 + 10;
const int MOD = 20100403;

long long QuickPow(long long a, int b, int c)
{
	long long res = 1;
	while (b)
	{
		if (b & 1) res = res * a % c;
		b >>= 1;
		a = a * a % c;
	}
	return res;
}

int n, m;
long long fac[MAXN], ans;

int main()
{
	scanf("%d%d", &n, &m);
	fac[0] = 1;
	for (int i = 1; i <= n + m; ++i) fac[i] = fac[i - 1] * i % MOD;
	ans = 1;
	ans = ans * fac[n + m] % MOD;
	ans = ans * (n - m + 1) % MOD;
	ans = ans * QuickPow(fac[n + 1], MOD - 2, MOD) % MOD;
	ans = ans * QuickPow(fac[m], MOD - 2, MOD) % MOD;
	printf("%lld\n", ans);
	
	return 0;
}
