#include <iostream>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <cmath>
#include <fstream>
#include <algorithm>

using namespace std;

const int MAXN = 50 + 10;

int n, m;
char a[MAXN][MAXN];
long long f[MAXN][MAXN];

inline long long gcd(long long n, long long m)
{
	while (m)
	{
		long long tmp = n % m;
		n = m;
		m = tmp;
	}
	return n;
}

int main()
{
	cin >> n >> m;
	for (int i = 1; i <= n; ++i)
		for (int j = 1; j <= i; ++j) cin >> a[i][j];
	f[1][1] = 1LL;
	++n; ++m;
	for (int i = 2; i <= n; ++i)
		for (int j = 1; j <= i; ++j)
		{
			if (a[i - 2][j - 1] == '.') f[i][j] += f[i - 2][j - 1] * 4;
			if (a[i - 1][j] == '*') f[i][j] += f[i - 1][j];
			if (a[i - 1][j - 1] == '*') f[i][j] += f[i - 1][j - 1];
		}
	long long s = (1LL << (n - 1));
	long long d = gcd(s, f[n][m]);
	s /= d; f[n][m] /= d;
	if (f[n][m] == 0) puts("0/1");
	else printf("%lld/%lld\n", f[n][m], s);
	
	return 0;
}
