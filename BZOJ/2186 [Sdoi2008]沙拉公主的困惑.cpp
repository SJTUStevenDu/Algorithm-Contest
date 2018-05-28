#include <iostream>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <cmath>
#include <fstream>
#include <algorithm>

using namespace std;

const int MAXN = 10000000 + 10;

int Q, MOD, n, m, tot, prime[MAXN / 10];
bool vis[MAXN];
long long fac[MAXN], s1[MAXN], s2[MAXN];

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

int main()
{
	scanf("%d%d", &Q, &MOD);
	for (int i = 2; i <= 10000000; ++i)
	{
		if (!vis[i]) prime[++tot] = i;
		for (int j = 1; j <= tot && prime[j] * i <= 10000000; ++j)
		{
			vis[i * prime[j]] = 1;
			if (i % prime[j] == 0) break;
		}
	}
	fac[1] = s1[1] = s2[1] = 1;
	for (int i = 2; i <= 10000000; ++i) 
	{
		fac[i] = fac[i - 1] * i % MOD;
		s1[i] = s1[i - 1];
		s2[i] = s2[i - 1];
		if (!vis[i]) s1[i] = s1[i] * i % MOD, s2[i] = s2[i] * (i - 1) % MOD;
	}
	while (Q--)
	{
		scanf("%d%d", &n, &m);
		long long ans = fac[n] * s2[m] % MOD;
		ans = ans * QuickMod(s1[m], MOD - 2, MOD) % MOD;
		printf("%lld\n", ans);
	}
	
	return 0;
}
