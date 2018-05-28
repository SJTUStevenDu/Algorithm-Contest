#include <iostream>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <algorithm>
#include <cmath>

using namespace std;

const int MAXN = 3600 + 10;
const int INF = 0x7FFFFFFF >> 2;

int f[2][MAXN][2];
int a[MAXN], n, m, now, pre, ans;

inline void checkmax(int &x, int y) {if (x < y) x = y;}

int main()
{
	scanf("%d%d", &n, &m);
	for (int i = 1; i <= n; ++i) scanf("%d", &a[i]);
	if (m == 0) 
	{
		puts("0");
		return 0;
	}
	now = 1; pre = 0;
	for (int i = 0; i <= m; ++i) 
		for (int j = 0; j <= 1; ++j) f[0][i][j] = f[1][i][j] = -INF;
	f[now][0][0] = 0;
	f[now][1][1] = 0;
	for (int i = 2; i <= n; ++i)
	{
		now = now ^ 1; pre = pre ^ 1;
		for (int j = 0; j <= m; ++j) 
		{
			f[now][j][0] = f[pre][j][0];
			checkmax(f[now][j][0], f[pre][j][1]);
			if (j) 
			{
				f[now][j][1] = f[pre][j - 1][0];
				checkmax(f[now][j][1], f[pre][j - 1][1] + a[i]);
			}
		}
	}
	checkmax(ans, f[now][m][0]);
	checkmax(ans, f[now][m][1]);
	now = 1; pre = 0;
	for (int i = 0; i <= m; ++i) 
		for (int j = 0; j <= 1; ++j) f[0][i][j] = f[1][i][j] = -INF;
	f[now][1][0] = a[1];
	f[now][1][1] = a[1];
	for (int i = 2; i <= n; ++i)
	{
		now = now ^ 1; pre = pre ^ 1;
		for (int j = 0; j <= m; ++j) 
		{
			f[now][j][0] = f[pre][j][0];
			checkmax(f[now][j][0], f[pre][j][1]);
			if (j) 
			{
				f[now][j][1] = f[pre][j - 1][0];
				checkmax(f[now][j][1], f[pre][j - 1][1] + a[i]);
			}
		}
	}
	checkmax(ans, f[now][m][1]);
	printf("%d\n", ans);
	
	return 0;
}
