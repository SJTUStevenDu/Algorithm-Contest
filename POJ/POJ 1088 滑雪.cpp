#include <iostream>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <cmath>
#include <algorithm>
#include <fstream>

using namespace std;

const int MAXN = 100 + 10;
const int dx[4] = {-1, 0, 1, 0};
const int dy[4] = {0, -1, 0, 1};

int n, m, h[MAXN][MAXN], dp[MAXN][MAXN], ans, tot;

int dfs(int x, int y)
{
	if (dp[x][y]) return dp[x][y];
	dp[x][y] = 1;
	for (int k = 0; k < 4; ++k)
	{
		int vx = x +dx[k], vy = y + dy[k];
		if (vx > 0 && vy > 0 && vx <= n && vy <= m && h[vx][vy] < h[x][y]) dp[x][y] = max(dp[x][y], dfs(vx, vy) + 1);
	}
	return dp[x][y];
}

int main()
{
	scanf("%d%d", &n, &m);
	for (int i = 1; i <= n; ++i)
		for (int j = 1; j <= m; ++j) scanf("%d", &h[i][j]);
	for (int i = 1; i <= n; ++i) 
		for (int j = 1; j <= m; ++j) ans = max(ans, dfs(i, j));
	printf("%d\n", ans);
	
	return 0;
}
