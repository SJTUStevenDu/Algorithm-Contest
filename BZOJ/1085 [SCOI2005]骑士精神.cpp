#include <iostream>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <cmath>
#include <algorithm>
#include <fstream>

using namespace std;

const int MAXN = 6;
const int INF = 0x7FFFFFFF >> 2;
const int gx[10] = {1, 2, 1, 2, -1, -2, -1, -2};
const int gy[10] = {2, 1, -2, -1, 2, 1, -2, -1};
const int des[MAXN][MAXN] = {
{0, 0, 0, 0, 0, 0},
{0, 2, 2, 2, 2, 2},
{0, 1, 2, 2, 2, 2},
{0, 1, 1, 0, 2, 2},
{0, 1, 1, 1, 1, 2},
{0, 1, 1, 1, 1, 1}};

int a[MAXN][MAXN], tst, now, ans, minx, px, py, x, y;
char cc[MAXN];

int ListCate()
{
	int res = 0;
	for (int i = 1; i < MAXN; ++i)
		for (int j = 1; j < MAXN; ++j) if (a[i][j] != des[i][j] && a[i][j] && des[i][j]) ++res;
	return res;
}

void dfs(int dep, int x, int y)
{
	int nnow = ListCate();
	if (nnow + dep > now)
	{
		minx = min(minx, nnow + dep);
		return;
	}
	if (nnow == 0 && x == 3 && y == 3) 
	{
		ans = dep;
		return;
	}
	for (int i = 0; i < 8; ++i)
	{
		int vx = x + gx[i]; int vy = y + gy[i];
		if (vx <= 0 || vx >= MAXN || vy <= 0 || vy >= MAXN) continue;
		swap(a[x][y], a[vx][vy]);
		dfs(dep + 1, vx, vy);
		if (ans < INF) return;
		swap(a[x][y], a[vx][vy]);
	}
}

int main()
{
	scanf("%d", &tst);
	while (tst--)
	{
		for (int i = 1; i < MAXN; ++i)
		{
			scanf("%s", cc);
			for (int j = 1; j < MAXN; ++j)
			{
				if (cc[j - 1] == '0') a[i][j] = 1;
				else if (cc[j - 1] == '1') a[i][j] = 2;
				else a[i][j] = 0, x = i, y = j;
			}
		}
		now = ListCate(); ans = INF;
		while (now <= 15)
		{
			minx = INF;
			dfs(0, x, y);
			if (ans < INF) break;
			if (minx == INF) {ans = -1; break;} else now = minx;
		}
		if (ans == INF) puts("-1");
		else printf("%d\n", ans);
	}
	
	return 0;
}
