#include <iostream>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <algorithm>
#include <cmath>

using namespace std;

int ans, T, n;

int solve(int x, int y)
{
	int ret = 31;
	for (int i = 30; i; --i)
	{
		int tmp = (1 << i);
		if (x <= tmp && y <= tmp) ret = i;
		if (x > tmp) x -= tmp;
		if (y > tmp) y -= tmp;
	}
	return (x == 1 && y == 1) ? 0 : ret;
}

int main()
{
	scanf("%d", &T);
	while (T--)
	{
		scanf("%d", &n);
		n /= 2;
		ans = 0;
		for (int x, y, i = 1; i <= n; ++i) scanf("%d%d", &x, &y), ans ^= solve(x, y);
		puts(ans ? "YES" : "NO");
	}
	
	return 0;
}
