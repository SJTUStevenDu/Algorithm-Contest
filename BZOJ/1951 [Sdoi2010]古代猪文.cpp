#include <iostream>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <cmath>
#include <fstream>
#include <algorithm>

using namespace std;

//999911658 = 2 * 3 * 4679 * 35617

const int MAXN = 40000;
const int MOD = 999911659;

long long fac[4][MAXN], n, g, ans[4], w[4] = {2, 3, 4679, 35617};

long long QuickMod(long long a, long long b, int c)
{
	long long ret = 1;
	while (b)
	{
		if (b & 1) ret = ret * a % c;
		b >>= 1;
		a = a * a % c;
	}
	return ret;
}

long long C(long long n, long long m, int k)
{
	if (n < m) return 0;
	return fac[k][n] * QuickMod(fac[k][n - m] * fac[k][m], w[k] - 2, w[k]) % w[k];
}

long long Lucas(long long n, long long m, int k)
{
	long long ret = 1;
	while (n && m)
	{
		ret = ret * C(n % w[k], m % w[k], k) % w[k];
		n /= w[k]; m /= w[k]; 
	}
	return ret;
}

long long CRT()
{
	long long M = 999911658, ret = 0;
	for (int i = 0; i < 4; ++i)
	{
		long long d = M / w[i];
		ret = (ret + d * QuickMod(d, w[i] - 2, w[i]) * ans[i]) % M;
	}
	while (ret <= 0) ret += M;
	return ret;
}

int main()
{
	cin >> n >> g;
	g %= MOD;
	for (int i = 0; i < 4; ++i) 
	{
		fac[i][0] = 1;
		for (int j = 1; j <= w[i]; ++j) fac[i][j] = fac[i][j - 1] * j % w[i];
	}
	for (int i = 1; i * i <= n; ++i) if (n % i == 0)
	{
		long long tmp = n / i;
		for (int k = 0; k < 4; ++k)
		{
			if (tmp != i) ans[k] = (ans[k] + Lucas(n, i, k)) % w[k];
			ans[k] = (ans[k] + Lucas(n, tmp, k)) % w[k];
		}
	}
	cout << QuickMod(g, CRT(), MOD) <<endl;
	
	return 0;
}
