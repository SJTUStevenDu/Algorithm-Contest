#include <iostream>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <algorithm>
#include <cmath>

using namespace std;

const int MAXN = 30000 + 10;
const int INF = 0x7FFFFFFF >> 2;

int dp[MAXN];
int a[MAXN][3], n, ans, m;

int main()
{
	scanf("%d", &n);
	for (int i = 1; i <= n; ++i)
	{
		scanf("%d%d%d", &a[i][0], &a[i][1], &a[i][2]);
		int tmp = INF;
		if (a[i][0]) tmp = min(tmp, a[i][0]);
		if (a[i][1]) tmp = min(tmp, a[i][1]);
		if (a[i][2]) tmp = min(tmp, a[i][2]);
		m += tmp;
	}
	for (int i = 1; i <= n; ++i)
		for (int j = m; j >= 0; --j)
		{
			int tmp = INF;
			if (a[i][0] && j >= a[i][0]) tmp = min(tmp, dp[j - a[i][0]]);
			if (a[i][1]) tmp = min(tmp, dp[j] + a[i][1]);
			if (a[i][2] && j >= a[i][2]) tmp = min(tmp, dp[j - a[i][2]] + a[i][2]);
			dp[j] = tmp;
		}
	ans = INF;
	for (int i = 0; i <= m; ++i) ans = min(ans, max(i, dp[i]));
	printf("%d\n", ans);
	
	return 0;
}
