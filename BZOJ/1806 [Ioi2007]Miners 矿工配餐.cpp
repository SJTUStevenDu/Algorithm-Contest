#include <iostream>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <fstream>
#include <algorithm>

using namespace std;

const int MAXN = 100000 + 10;

int dp[2][4][4][4][4], v[4][4][4], cnt[4];
int n, a[MAXN], now, pre, ans;
char s[MAXN];

inline int getnum(int a, int b, int c)
{
	cnt[0] = cnt[1] = cnt[2] = cnt[3] = 0;
	cnt[a]++; cnt[b]++; cnt[c]++;
	if (cnt[2] == 3) return 1;
	if (cnt[0] == 0)
	{
		if (a + b + c == 6) return 3;
		if (cnt[1] == 2 || cnt[2] == 2 || cnt[3] == 2) return 2;
		else return 1;
	}
	if (cnt[0] == 1)
	{
		if (cnt[1] == 2 || cnt[2] == 2 || cnt[3] == 2) return 1;
		else return 2;
	}
	return 1;
}

inline void checkmax(int &x, int y) {if (x < y) x = y;}

int main()
{
	scanf("%d", &n);
	scanf("%s", s + 1);
	for (int i = 1; i <= n; ++i)
	{
		if (s[i] == 'M') a[i] = 1;
		else if (s[i] == 'B') a[i] = 2;
		else if (s[i] == 'F') a[i] = 3;
	}
	for (int i = 0; i <= 3; ++i)
		for (int j = 0; j <= 3; ++j) 
			for (int k = 0; k <= 3; ++k) v[i][j][k] = getnum(i, j, k);
	now = 0; pre = 1;
	dp[now][0][a[1]][0][0] = dp[now][0][0][0][a[1]] = 1;
	for (int i = 2; i <= n; ++i)
	{
		now = now ^ 1;
		pre = pre ^ 1;
		for (int x1 = 0; x1 <= 3; ++x1)
			for (int x2 = 0; x2 <= 3; ++x2)
				for (int y1 = 0; y1 <= 3; ++y1)
					for (int y2 = 0; y2 <= 3; ++y2) if (dp[pre][x1][x2][y1][y2])
					{
						checkmax(dp[now][x2][a[i]][y1][y2], dp[pre][x1][x2][y1][y2] + v[x1][x2][a[i]]);
						checkmax(dp[now][x1][x2][y2][a[i]], dp[pre][x1][x2][y1][y2] + v[y1][y2][a[i]]);
					}
	}
	for (int x1 = 0; x1 <= 3; ++x1)
			for (int x2 = 0; x2 <= 3; ++x2)
				for (int y1 = 0; y1 <= 3; ++y1)
					for (int y2 = 0; y2 <= 3; ++y2) checkmax(ans, dp[now][x1][x2][y1][y2]);
	printf("%d\n", ans);
	
	return 0;
}
