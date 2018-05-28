#include <iostream>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <cmath>
#include <fstream>
#include <algorithm>

using namespace std;

const int MAXN = 100000 + 10;
const int MAXM = 100 + 10;

long long f[MAXM], s[MAXM];
long long n, ans;
long long dp[MAXM][MAXN];

void GetDp(long long n, int p)
{
	if (p < 0) return;
	if (n <= 100000) ans += dp[p][n];
	else
	{
		if (n >= f[p]) GetDp(n - f[p], p - 1);
		if (s[p - 1] >= n) GetDp(n, p - 1);
	}
}

int main()
{
	f[1] = 1; f[2] = 2;
	for (int i = 3; i <= 88; ++i) f[i] = f[i - 1] + f[i - 2];
	for (int i = 1; i <= 88; ++i) s[i] = s[i - 1] + f[i];
	dp[0][0] = 1;
	for (int i = 1; i <= 88; ++i)
	{
		for (int j = 0; j <= 100000; ++j) dp[i][j] = dp[i - 1][j];
		for (int j = 100000; j >= f[i]; --j) dp[i][j] += dp[i - 1][j - f[i]];
	}
	scanf("%lld", &n);
	GetDp(n, 88);
	printf("%lld\n", ans);
	
	return 0;
}
