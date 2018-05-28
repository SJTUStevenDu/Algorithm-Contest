#include <iostream>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <fstream>
#include <algorithm>

using namespace std;

const int MAXN = 300 + 10;
const int MAXC = 100 + 10;

int s[MAXC][MAXN][MAXN];
int n, m, Q, x1, y1, x2, y2, c, opr;
int map[MAXN][MAXN];

inline int lowbit(int x) {return x & (-x);}

void Update(int C, int x, int y, int v)
{
	for (; x <= n; x += lowbit(x))
		for (int j = y; j <= m; j += lowbit(j)) s[C][x][j] += v;
}

int Query(int C, int x, int y)
{
	int res = 0;
	for (; x; x -= lowbit(x))
		for (int j = y; j; j -= lowbit(j)) res += s[C][x][j];
	return res;
}

int main()
{
	scanf("%d%d", &n, &m);
	for (int i = 1; i <= n; ++i)
		for (int j = 1; j <= m; ++j)
		{
			scanf("%d", &map[i][j]);
			Update(map[i][j], i, j, 1);
		}
	scanf("%d", &Q);
	while (Q--)
	{
		scanf("%d", &opr);
		if (opr == 1)
		{
			scanf("%d%d%d", &x1, &y1, &c);
			Update(map[x1][y1], x1, y1, -1);
			Update(map[x1][y1] = c, x1, y1, 1);
		}
		else
		{
			scanf("%d%d%d%d%d", &x1, &x2, &y1, &y2, &c);
			printf("%d\n", Query(c, x2, y2) - Query(c, x1 - 1, y2) - Query(c, x2, y1 - 1) + Query(c, x1 - 1, y1 - 1));
		}
	}
	
	return 0;
}
