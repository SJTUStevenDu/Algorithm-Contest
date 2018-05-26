#include <iostream>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <cmath>
#include <algorithm>
#include <fstream>

using namespace std;

const int MAXN = 100 + 10;
const int MAXM = 1000 + 10;

int T, n, num[MAXN], maxb;
int a[MAXN][MAXN][2];
int f[MAXN][MAXM];
double ans;

int main()
{
	scanf("%d", &T);
	while (T--)
	{
		memset(f, 63, sizeof(f));
		maxb = 0;
		ans = 0.0;
		scanf("%d", &n);
		for (int i = 1; i <= n; ++i)
		{
			scanf("%d", &num[i]);
			for (int j = 1; j <= num[i]; ++j) scanf("%d%d", &a[i][j][0], &a[i][j][1]), maxb = max(maxb, a[i][j][0]);
		}
		for (int i = 0; i <= maxb; ++i) f[0][i] = 0;
		for (int i = 1; i <= n; ++i)
			for (int j = 1; j <= num[i]; ++j)
				for (int k = 1; k <= a[i][j][0]; ++k) f[i][k] = min(f[i][k], f[i - 1][k] + a[i][j][1]);
		for (int i = 1; i <= maxb; ++i) ans = max(ans, i * 1.0 / f[n][i]);
		printf("%.3lf\n", ans);
	}
	
	return 0;
}
