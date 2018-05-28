#include <iostream>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <cmath>
#include <algorithm>
#include <fstream>

using namespace std;

const int MAXN = 10000000 + 10;

int n, m, Q, g[MAXN], h[MAXN], prime[MAXN], tot;
long long sum[MAXN], ans;
bool vis[MAXN];

inline int Pow2(int x) {return (x & 1) ? -1 : 1;}

void Preparation()
{
	for (int i = 2; i <= 10000000; ++i)
	{
		if (!vis[i]) prime[++tot] = i, g[i] = h[i] = 1;
		for (int j = 1; j <= tot && prime[j] * i <= 10000000; ++j)
		{
			vis[i * prime[j]] = 1;
			if (i % prime[j] == 0)
			{
				g[i * prime[j]] = g[i] + 1;
				h[i * prime[j]] = h[i];
				break;
			}
			g[i * prime[j]] = g[i] + 1;
			h[i * prime[j]] = h[i] + 1;
		}
	}
	for (int i = 2; i <= 10000000; ++i)
	{
		int tmp = 0;
		if (g[i] == h[i] + 1) tmp = Pow2(h[i]);
		else if (g[i] == h[i]) tmp = Pow2(h[i] - 1) * h[i];
		sum[i] = sum[i - 1] + tmp;
	}
}

void Solve(int n, int m)
{
	ans = 0;
	if (n > m) swap(n, m);
	for (int i = 1, nexti; i <= n; i = nexti + 1)
	{
		int ta = n / i, tb = m / i;
		nexti = min(n / ta, m / tb); 
		ans = ans + (sum[nexti] - sum[i - 1]) * ta * tb;
	}
}

int main()
{
	scanf("%d", &Q);
	Preparation();
	while (Q--)
	{
		scanf("%d%d", &n, &m);
		Solve(n, m);
		printf("%lld\n", ans);
	}
	
	return 0;
}
