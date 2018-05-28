#include <iostream>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <cmath>
#include <fstream>
#include <algorithm>

using namespace std;

const int MAXN = 200 + 10;

int dp[2][MAXN][MAXN];
int n, m, now, pre, cost[MAXN][MAXN], pos, pos1, ans;

inline void checkmin(int &x, int y)
{
	if (x > y) x = y;
}

int main()
{
	scanf("%d", &n);
	for (int i = 1; i <= n; ++i)
		for (int j = 1; j <= n; ++j) scanf("%d", &cost[i][j]);
	memset(dp, 63, sizeof(dp));
	int INF = dp[0][0][0];
	pos1 = 1; now = 0; pre = 1;
	dp[now][2][3] = dp[now][3][2] = 0;
	while (~scanf("%d", &pos))
	{
		swap(now, pre);
		memset(dp[now], 63, sizeof(dp[now]));
		for (int i = 1; i <= n; ++i)
			for (int j = 1; j <= n; ++j) if (dp[pre][i][j] < INF)
			{
				checkmin(dp[now][i][j], dp[pre][i][j] + cost[pos1][pos]);
				checkmin(dp[now][pos1][j], dp[pre][i][j] + cost[i][pos]);
				checkmin(dp[now][i][pos1], dp[pre][i][j] + cost[j][pos]);
			}
		pos1 = pos;
	}
	ans = INF;
	for (int i = 1; i <= n; ++i) 
		for (int j = 1; j <= n; ++j) checkmin(ans, dp[now][i][j]);
	printf("%d\n", ans);
	
	return 0;
}
