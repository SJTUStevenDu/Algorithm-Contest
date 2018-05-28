#include <iostream>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <algorithm>
#include <cmath>

using namespace std;

const int MAXN = 100000 + 10;

int t, mod;
int a[20], n, m;
long long fac[MAXN], rfac[MAXN], ans;

inline long long QuickMod(long long a, int b, int c)
{
	long long ret = 1;
	while (b)
	{
		if (b & 1) ret = ret * a % c;
		b >>= 1;
		a = a * a % c;
	}
	return ret;
}

long long Lucas(int n, int m, int p)
{
	long long ret = 1;
	while (n && m)
	{
		int x = n % p, y = m % p;
		if (x < y) return 0;
		ret = ret * fac[x] % mod * rfac[y] % mod * rfac[x - y] % mod;
		n /= p;
		m /= p;
	}
	return ret;
}

int main()
{
	scanf("%d%d%d%d", &n, &t, &m, &mod);
	for (int i = 1; i <= t; ++i) scanf("%d", &a[i]), ++a[i];
	fac[0] = rfac[0] = 1;
	for (int i = 1; i < mod; ++i) fac[i] = fac[i - 1] * i % mod;
	for (int i = 1; i < mod; ++i) rfac[i] = QuickMod(fac[i], mod - 2, mod);
	for (int i = 0; i < (1 << t); ++i)
	{
		int tt = 0, now = n + m;
		for (int j = 0; j < t; ++j) if (i & (1 << j)) ++tt, now -= a[j + 1];
		if (tt & 1) ans -= Lucas(now, n, mod);
		else ans += Lucas(now, n, mod);
		ans = (ans % mod + mod) % mod; 
	}
	printf("%lld\n", ans);
	return 0;
}
