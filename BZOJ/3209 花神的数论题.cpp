#include <iostream>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <cmath>
#include <fstream>
#include <algorithm>

using namespace std;

const int MAXN = 50 + 10;
const int MOD = 10000007;

long long n, num[MAXN], ans;
int a[MAXN];

long long C(int n, int m)
{
	long long ret = 1;
	for (int i = 1; i <= m; ++i) ret = ret * (n - m + i) / i;
	return ret;
}

long long QuickMod(long long a, long long b)
{
	long long ret = 1;
	while (b)
	{
		if (b & 1) ret = ret * a % MOD;
		b >>= 1;
		a = a * a % MOD;
	}
	return ret;
}

int main()
{
	scanf("%lld", &n);
	while (n)
	{
		a[++a[0]] = n % 2;
		n /= 2;
	}
	int cnt = 0;
	for (int i = a[0]; i; --i)
	{
		if (a[i] == 0) continue;
		for (int j = 0; j < i; ++j) num[j + cnt] += C(i - 1, j);
		++cnt;
	}
	ans = 1;
	for (int i = 1; i < a[0]; ++i) ans = ans * QuickMod((long long)i, num[i]) % MOD;
	ans = ans * (long long)cnt % MOD;
	printf("%lld\n", ans);
	
	return 0;
}
