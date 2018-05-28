#include <iostream>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <cmath>
#include <algorithm>
#include <fstream>

using namespace std;

const int MAXN = 4200 + 10;

int n, mod;
int dp[2][MAXN];

int main()
{
	scanf("%d%d", &n, &mod);
	if (n == 1)
	{
		printf("%d\n", n % mod);
		return 0;
	}
	int now = 1, pre = 0;
	for (int i = 1; i <= n; ++i) dp[now][i] = 1;
	for (int i = 2; i <= n; ++i)
	{
		now ^= 1; pre ^= 1;
		for (int j = 1; j <= i; ++j) dp[now][j] = (dp[now][j - 1] + dp[pre][i - j]) % mod;
	}
	printf("%d\n", dp[now][n] * 2 % mod);
	
	return 0;
}
