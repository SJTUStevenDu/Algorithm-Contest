#include <iostream>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <algorithm>
#include <cmath>

using namespace std;

const int MAXN = 10;
const int dx[4] = {0, 1, 0, -1};
const int dy[4] = {-1, 0, 1, 0};

int a[MAXN][MAXN], v[MAXN][MAXN], n, ans;
bool vis[MAXN];

int Left()
{
	int ret = 0;
	memset(vis, 0, sizeof(vis));
	for (int i = 1; i <= n; ++i)
		for (int j = 1; j <= n; ++j)
			if (v[i][j] != 1 && !vis[a[i][j]]) vis[a[i][j]] = 1, ++ret;
	return ret;
}

void dfs(int x, int y, int c)
{
	v[x][y] = 1;
	for (int k = 0; k < 4; ++k)
	{
		int vx = dx[k] + x, vy = dy[k] + y;
		if (vx > 0 && vx <= n && vy > 0 && vy <= n && v[vx][vy] != 1)
		{
			v[vx][vy] = 2;
			if (a[vx][vy] == c) dfs(vx, vy, c);
		}
	}
}

int Color(int c)
{
	int ret = 0;
	for (int i = 1; i <= n; ++i)
		for (int j = 1; j <= n; ++j) if (v[i][j] == 2 && a[i][j] == c) 
		{
			++ret;
			dfs(i, j, c);
		}
	return ret;
}

bool IDA(int dep)
{
	int l = Left();
	if (dep + l > ans) return 0;
	if (!l) return 1;
	int tmp[MAXN][MAXN];
	for (int c = 0; c <= 5; ++c)
	{
		memcpy(tmp, v, sizeof(v));
		if (Color(c) && IDA(dep + 1)) return 1;
		memcpy(v, tmp, sizeof(tmp));
	}
	return 0;
}

int main()
{
	while (scanf("%d", &n) && n) 
	{
		for (int i = 1; i <= n; ++i)
			for (int j = 1; j <= n; ++j) scanf("%d", &a[i][j]);
		memset(v, 0, sizeof(v));
		dfs(1, 1, a[1][1]);
		for (ans = 0;; ++ans) if (IDA(0)) break;
		printf("%d\n", ans);
	}
	
	return 0;
}
