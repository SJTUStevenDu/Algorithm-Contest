#include <iostream>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <cmath>
#include <algorithm>
#include <fstream>

using namespace std;

const int MAXN = 2000000 + 10;

int n, m, mod;
long long ans;
int prime[MAXN / 10], tot, fac[MAXN / 10];
bool vis[MAXN];

void Deal(int x, int f)
{
	for (int i = 1; i <= tot; ++i)
	{
		int j = x;
		while (j) fac[i] += f * j / prime[i], j /= prime[i];
	}
}

int main()
{
	scanf("%d%d", &n, &mod);
	m = n * 2;
	for (int i = 2; i <= m; ++i) 
	{
		if (!vis[i]) prime[++tot] = i;
		for (int j = 1; j <= tot && prime[j] * i <= m; ++j)
		{
			vis[prime[j] * i] = 1;
			if (i % prime[j] == 0) break;
		}
	}
	Deal(m, 1);
	Deal(n, -1);
	Deal(n + 1, -1);
	ans = 1LL;
	for (int i = 1; i <= tot; ++i) 
		for (int j = 1; j <= fac[i]; ++j) ans = ans * prime[i] % mod;
	printf("%lld\n", ans); 
	
	return 0;
}
