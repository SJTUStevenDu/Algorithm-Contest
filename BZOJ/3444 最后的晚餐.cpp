#include <iostream>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <cmath>
#include <fstream>
#include <algorithm>

using namespace std;

const int MAXN = 500000 + 10;
const int MOD = 989381;

long long a[MAXN];
int n, m, father[MAXN], sz[MAXN], cnt[MAXN];

inline int getfather(int x)
{
	return father[x] == x ? x : father[x] = getfather(father[x]);
}

long long QuickPow(long long a, int b)
{
	long long ret = 1;
	while (b)
	{
		if (b & 1) ret = ret * a % MOD;
		a = a * a % MOD;
		b >>= 1;
	}
	return ret;
}

int main()
{
	scanf("%d%d", &n, &m);
	for (int x, y, i = 1; i <= m; ++i) 
	{
		scanf("%d%d", &x, &y);
		if (x > y) swap(x, y);
		--x; --y;
		a[i] = (long long)x * n + (long long)y;
	}
	sort(a + 1, a + 1 + m);
	m = unique(a + 1, a + 1 + m) - a - 1;
	for (int i = 0; i < n; ++i) father[i] = i;
	for (int i = 1; i <= m; ++i)
	{
		int x = (int)(a[i] / n), y = (int)(a[i] % n);
		++cnt[x]; ++cnt[y];
		x = getfather(x); y = getfather(y);
		if (x == y) 
		{
			puts("0");
			return 0;
		}
		father[x] = y;
	}
	for (int i = 0; i < n; ++i) if (cnt[i] > 2)
	{
		puts("0");
		return 0;
	}
	for (int i = 0; i < n; ++i) sz[getfather(i)]++;
	int x = 0, y = 0;
	for (int i = 0; i < n; ++i) if (sz[i] == 1) ++x; else if (sz[i] > 1) ++y;
	long long ans = QuickPow(2, y);
	for (int i = 1; i <= x + y; ++i) ans = ans * i % MOD;
	printf("%lld\n", ans);
	
	return 0;
}
