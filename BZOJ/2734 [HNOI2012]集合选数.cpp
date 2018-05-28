#include <iostream>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <cmath>
#include <fstream>
#include <algorithm>

using namespace std;

const int MAXN = (1 << 12) + 10;
const int MAXC = 30;
const int MOD = 1000000001;

int n, lim[MAXC], dp[2][MAXN];
bool check[MAXN];
long long ans;

long long Solve(int p)
{
	memset(lim, 0, sizeof(lim));
	int m = 1, now, pre;
	for (now = p; now <= n; ++m) 
	{
		int tmp = now;
		for (; tmp <= n; tmp *= 3) lim[m]++;
		now *= 2;
	}
	--m;
	now = 1; pre = 0;
	for (int i = 0; i < (1 << lim[1]); ++i) if (check[i]) dp[now][i] = 1; else dp[now][i] = 0;
	for (int i = 2; i <= m; ++i)
	{
		now = now ^ 1; pre = pre ^ 1;
		for (int j = 0; j < (1 << lim[i]); ++j)
		{
			dp[now][j] = 0;
		 	if (!check[j]) continue;
			for (int k = 0; k < (1 << lim[i - 1]); ++k)
				if ((j & k) == 0) dp[now][j] = (dp[now][j] + dp[pre][k]) % MOD;
		}
	}
	int ret = 0;
	for (int i = 0; i < (1 << lim[m]); ++i) ret = (ret + dp[now][i]) % MOD;
	return (long long)ret;
}

int main()
{
	scanf("%d", &n);
	for (int i = 0; i < MAXN; ++i) if ((i & (i << 1)) == 0) check[i] = true;
	ans = 1;
	for (int i = 1; i <= n; ++i)
	{
		if (i % 2 == 0 || i % 3 == 0) continue;
		ans = ans * Solve(i) % MOD;
	}
	printf("%lld\n", ans);
	
	return 0;
}
