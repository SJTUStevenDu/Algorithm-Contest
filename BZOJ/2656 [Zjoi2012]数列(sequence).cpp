#include <iostream>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <algorithm>
#include <cmath>

using namespace std;

const int MAXS = 1 << 9;
const int MAXN = 100 + 10;
const int MAXM = 10 + 5;
const int INF = 1061109567;
const int gx[4] = {-1, 0, 1, 0};
const int gy[4] = {0, -1, 0, 1};

int d[MAXS][MAXM][MAXM], n, m, t, b[MAXM][2], ans;
int score[MAXM], sc[MAXS], q[MAXN * MAXS][3], head, tail;
char map[MAXM][MAXM];

inline int calc(int z, int x, int y, int dx, int dy)
{
	for (int i = 0; i < t; ++i) if (y < b[i][1] && (x == b[i][0] && dx > b[i][0] || dx == b[i][0] && x > b[i][0])) z ^= (1 << i);
	return z;
}

void BFS(int x0, int y0)
{
	memset(d, 63, sizeof(d));
	d[0][x0][y0] = 0;
	head = 0; tail = 1;
	q[head][0] = x0; q[head][1] = y0; q[head][2] = 0;
	while (head != tail)
	{
		int x = q[head][0], y = q[head][1], z = q[head][2];
		++head;
		for (int k = 0; k < 4; ++k)
		{
			int dx = x + gx[k], dy = y + gy[k];
			if (map[dx][dy] != '0') continue;
			int dz = calc(z, x, y, dx, dy);
			if (d[dz][dx][dy] == INF)
			{
				d[dz][dx][dy] = d[z][x][y] + 1;
				q[tail][0] = dx; q[tail][1] = dy; q[tail][2] = dz;
				++tail;
			}
		}
	}
}

int main()
{
	scanf("%d%d%d", &n, &m, &t);
	for (int i = 0; i < t; ++i) scanf("%d", &score[i]);
	for (int s = 0; s < (1 << t); ++s)
		for (int i = 0; i < t; ++i) if (s & (1 << i)) sc[s] += score[i];
	for (int i = 1; i <= n; ++i)
	{
		scanf("%s", map[i] + 1);
		for (int j = 1; j <= m; ++j) if (map[i][j] != '0' && map[i][j] != '#') b[map[i][j] - '1'][0] = i, b[map[i][j] - '1'][1] = j;
	}
	for (int i = 1; i <= n; ++i) 
		for (int j = 1; j <= m; ++j) if (map[i][j] == '0')
		{
			BFS(i, j);
			for (int s = 0; s < (1 << t); ++s) ans = max(ans, sc[s] - d[s][i][j]);
		}
	printf("%d\n", ans);
	return 0;
}
