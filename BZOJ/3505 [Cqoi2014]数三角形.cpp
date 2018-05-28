#include <iostream>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <cmath>
#include <fstream>
#include <algorithm>

using namespace std;

long long ans, cnt;
int n, m;

inline int gcd(int n, int m)
{
	int tmp;
	while (m)
	{
		tmp = n % m;
		n = m;
		m = tmp;
	}
	return n;
}

int main()
{
	scanf("%d%d", &n, &m);
	++n; ++m;
	for (int i = 0; i < n; ++i)
		for (int j = 0; j < m; ++j)
		{
			if (i == 0 && j == 0) continue;
			int g = gcd(i, j);
			if (i == 0 || j == 0) cnt += (long long)(g - 1) * (long long)(n - i) * (long long)(m - j);
			else cnt += (long long)(g - 1) * (long long)(n - i) * (long long)(m - j) * 2;
		}
	ans = (long long)n * m * (long long)(n * m - 1) / 2 * (long long)(n * m - 2) / 3 - cnt;
	printf("%lld\n", ans);
	
	return 0;
}
