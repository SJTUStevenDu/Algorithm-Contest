#include <iostream>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <cmath>
#include <algorithm>
#include <fstream>

using namespace std;

const int MAXN = (1 << 16) + 10;

int prime[MAXN], tot, n;
long long ans;
bool vis[MAXN];

long long phi(long long x)
{
	long long res = x;
	for (int i = 1; i <= tot; ++i)
	{
		if (x % prime[i] != 0) continue;
		res = res / prime[i];
		res = res * (prime[i] - 1);
		while (x % prime[i] == 0) x /= prime[i];
	}
	if (x != 1) res = res / x * (x - 1);
	return res;
}

int main()
{
	for (int i = 2; i <= (1<<16); ++i) 
	{
		if (!vis[i]) prime[++tot] = i;
		for (int j = 1; j <= tot && i * prime[j] <= (1 << 16); ++j)
		{
			vis[i * prime[j]] = 1;
			if (i % prime[j] == 0) break;
		}
	}
	scanf("%d", &n);
	for (int i = 1; i * i <= n; ++i)
	{
		if (n % i != 0) continue;
		ans += (long long)i * phi(n / i);
		if (i * i != n) ans += (long long)(n / i) * phi(i);
	}
	printf("%lld\n", ans);
	
	return 0;
}
