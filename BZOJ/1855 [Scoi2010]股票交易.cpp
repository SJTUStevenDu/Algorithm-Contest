#include <iostream>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <cmath>
#include <fstream>
#include <algorithm>

using namespace std;

const int MAXN = 2000 + 10;

int f[MAXN][MAXN], q[MAXN], val[MAXN], l, r, n, maxp, ap[MAXN], bp[MAXN], as[MAXN], bs[MAXN], W, ans;

inline void checkmax(int &x, int y)
{
	if (x < y) x = y;
}

int main()
{
	scanf("%d%d%d", &n, &maxp, &W);
	for (int i = 1; i <= n; ++i) scanf("%d%d%d%d", &ap[i], &bp[i], &as[i], &bs[i]);
	memset(f, ~63, sizeof(f));
	f[0][0] = 0;
	for (int i = 1; i <= n; ++i)
	{
		for (int j = 0; j <= as[i]; ++j) f[i][j] = -ap[i] * j;
		for (int j = 0; j <= maxp; ++j) checkmax(f[i][j], f[i - 1][j]);
		int now = i - 1 - W;
		if (now >= 0)
		{
			l = 1; r = 0;
			for (int j = 0; j <= maxp; ++j)
			{
				while (l <= r && q[l] < j - as[i]) ++l;
				while (l <= r && f[now][j] + j * ap[i] >= val[r]) --r;
				q[++r] = j;
				val[r] = f[now][j] + j * ap[i];
				checkmax(f[i][j], val[l] - j * ap[i]);
			}
			l = 1; r = 0;
			for (int j = maxp; j >= 0; --j)
			{
				while (l <= r && q[l] > j + bs[i]) ++l;
				while (l <= r && f[now][j] + j * bp[i] >= val[r]) --r;
				q[++r] = j;
				val[r] = f[now][j] + j * bp[i];
				checkmax(f[i][j], val[l] - j * bp[i]);
			}
		}
		checkmax(ans, f[i][0]);
	}
	printf("%d\n", ans);
	
	return 0;
}
