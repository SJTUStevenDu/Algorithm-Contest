#include <iostream>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <cmath>
#include <algorithm>
#include <fstream>

using namespace std;

const int MAXN = 2000000 + 10;

long long fac[MAXN];
int n, mod, s[MAXN];

long long QuickMod(long long a, int b, int c)
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

int Calc(int x)
{
	int res = 0;
	while (x)
	{
		res += x / mod;
		x /= mod;
	}
	return res;
}

long long NewFac(int x)
{
	if (x == 0) return 1;
	return fac[x % mod] * QuickMod(mod - 1, x / mod, mod) % mod * NewFac(x / mod) % mod;
}

long long C(long long x, long long y)
{
	if (Calc(x) > Calc(y) + Calc(x - y)) return 0;
	return NewFac(x) * QuickMod(NewFac(y), mod - 2, mod) % mod * QuickMod(NewFac(x - y), mod - 2, mod) % mod;
}

long long dp(int x)
{
	if (x > n) return 1;
	if (s[x] == 1) return 1;
	int L = x * 2, R = x * 2 + 1;
	return C(s[L] + s[R], s[L]) * dp(L) % mod * dp(R) % mod;
}

int main()
{
	scanf("%d%d", &n, &mod);
	fac[0] = 1;
	for (int i = 1; i <= n; ++i) fac[i] = fac[i - 1] * i % mod;
	for (int i = 1; i <= n; ++i) 
		for (int j = i; j; j /= 2) s[j]++;
	printf("%lld\n", dp(1));
	
	return 0;
}
