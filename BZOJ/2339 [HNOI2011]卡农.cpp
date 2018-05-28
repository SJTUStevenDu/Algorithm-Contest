#include <iostream>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <cmath>
#include <algorithm>

using namespace std;

const int MAXN = 1000000 + 10; 
const int MOD = 100000007;

int n, m;
long long ans, f[MAXN], A[MAXN], pw[MAXN];

long long QuickMod(long long a, int b)
{
	long long ret = 1LL;
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
	freopen("canon.in", "r", stdin);
	freopen("canon.out", "w", stdout);
	cin >> n >> m;
	pw[0] = 1;
	for (int i = 1; i <= n; ++i) pw[i] = pw[i - 1] * 2 % MOD;
	A[0] = 1;
	for (int i = 1; i <= m; ++i) A[i] = A[i - 1] * (pw[n] - i) % MOD;
	f[1] = f[2] = 0;
	for (int i = 3; i <= m; ++i) 
	{
		f[i] = (A[i - 1] - f[i - 1] - f[i - 2] * (i - 1) % MOD * (pw[n] - i + 1 + MOD) % MOD) % MOD;
		f[i] = (f[i] + MOD) % MOD;
	}
	ans = f[m];
	long long ca = 1;
	for (int i = 1; i <= m; ++i) ca = ca * i % MOD;
	ans = ans * QuickMod(ca, MOD - 2) % MOD;
	cout << ans << endl;
	
	return 0;
}
