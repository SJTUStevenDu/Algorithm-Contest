#include <iostream>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <cmath>
#include <algorithm>
#include <fstream>

using namespace std;

const int MAXN = 100 + 10;
const int INF = 0x7FFFFFFF>>2;

int map[MAXN][MAXN], d[MAXN];
int n, m, s, v, ans;

int main()
{
	while(~scanf("%d", &n))
	{
		if (!n) break;
		memset(d, 0, sizeof(d));
		for (int i = 1; i <= n; ++i)
			for (int j = 1; j <= n; ++j) map[i][j] = (i != j) * INF;
		for (int i = 1; i <= n; ++i)
		{
			scanf("%d", &m);
			while (m--)
			{
				scanf("%d%d", &s, &v);
				map[i][s] = min(map[i][s], v);
			}
		}
		for (int k = 1; k <= n; ++k)
			for (int i = 1; i <= n; ++i)
				for (int j = 1; j <= n; ++j) map[i][j] = min(map[i][j], map[i][k] + map[k][j]);
		for (int i = 1; i <= n; ++i) 
			for (int j = 1; j <= n; ++j) if (i != j) d[i] = max(d[i], map[i][j]);
		d[ans = 0] = INF;
		for (int i = 1; i <= n; ++i) if (d[i] < d[ans]) ans = i;
		if (ans == 0) puts("disjoint");
		else printf("%d %d\n", ans, d[ans]);
	}
	
	return 0;
}
