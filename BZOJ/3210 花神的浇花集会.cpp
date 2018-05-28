#include <iostream>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <cmath>
#include <fstream>
#include <algorithm>

using namespace std;

const int MAXN = 100000 + 10;

int n;
long long ans, x[MAXN], y[MAXN];

long long calc(long long sx, long long sy)
{
	long long ret = 0;
	for (int i = 1; i <= n; ++i) ret += abs(x[i] - sx) + abs(y[i] - sy);
	return ret;
}

int main()
{
	scanf("%d", &n);
	for (int a, b, i = 1; i <= n; ++i)
	{
		scanf("%d%d", &a, &b);
		x[i] = a + b;
		y[i] = a - b;
	}
	sort(x + 1, x + 1 + n);
	sort(y + 1, y + 1 + n);
	long long sx = x[(n + 1) / 2], sy = y[(n + 1) / 2];
	if ((sx + sy) % 2 == 0) ans = calc(sx, sy);
	else
	{
		ans = calc(sx, sy + 1);
		ans = min(ans, calc(sx, sy - 1));
		ans = min(ans, calc(sx + 1, sy));
		ans = min(ans, calc(sx - 1, sy));
	}
	ans /= 2;
	printf("%lld\n", ans);
	
	return 0;
}
