#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <cmath>

using namespace std;

const int MAXN = 200000 + 10;
const int dx[4] = {0, -1, 0, 1};
const int dy[4] = {-1, 0, 1, 0};

char a[110][110];
int ver[MAXN], next[MAXN], head[MAXN], v[MAXN], n, m, tot, cnt, Q;
double f[MAXN], pi = acos(-1.0), ans;

void AddEdge(int i, int j, int k, int x, int y, int z)
{
	int a = (i - 1) * m + j + k * n * m, b = (x - 1) * m + y + z * n * m;
	ver[++tot] = b; next[tot] = head[a]; head[a] = tot;
}

void dfs(int x)
{
	v[x] = cnt;
	if (x <= n * m) f[cnt] += 4 - pi / 2; else f[cnt] += pi / 4;
	for (int i = head[x]; i; i = next[i]) if (!v[ver[i]]) dfs(ver[i]);
}

double s(int x,int y,int z)
{
	x = x / 2 + 1; y = y / 2 + 1;
	if (!z) return f[v[(x - 1) * m + y]];
	if (a[x][y] == '0')
		if (z == 1) return f[v[((x - 1) * m + y) + n * m]];
		else if (z == 4) return f[v[((x - 1) * m + y) + 2 * n * m]];
		else return f[v[(x - 1) * m + y]];
	else if (z == 2) return f[v[((x - 1) * m + y) + n * m]];
		else if (z == 3) return f[v[((x - 1) * m + y) + 2 * n * m]];
		else return f[v[(x - 1) * m + y]];
}

int main()
{
	scanf("%d%d", &n, &m);
	for (int i = 1; i <= n; ++i) scanf("%s",a[i]+1);
	for (int i = 1; i <= n; ++i)
		for (int j = 1; j <= m; ++j)
			for (int k = 0; k < 4; ++k)
			{
				int x = i + dx[k], y = j + dy[k];
				if (x < 1 || y < 1 || x > n || y > m) continue;
				if (a[i][j] == '0')
				{
					if (k == 0)
					{
						if (a[x][y] == '0') AddEdge(i, j, 1, x, y, 0), AddEdge(i, j, 0, x, y, 2);
						else AddEdge(i, j, 1, x, y, 1), AddEdge(i, j, 0, x, y, 0);
					}
					else if (k == 1)
					{
						if (a[x][y] == '0') AddEdge(i, j, 0, x, y, 2), AddEdge(i, j, 1, x, y, 0);
						else AddEdge(i, j, 0, x, y, 0), AddEdge(i, j, 1, x, y, 2);
					}
					else if (k == 2)
					{ 
						if (a[x][y] == '0') AddEdge(i, j, 0, x, y, 1), AddEdge(i, j, 2, x, y, 0);
						else AddEdge(i, j, 0, x, y, 0), AddEdge(i, j, 2, x, y, 2);
					}
					else 
					{
						if (a[x][y] == '0') AddEdge(i, j, 0, x, y, 1), AddEdge(i, j, 2, x, y, 0);
						else AddEdge(i, j, 0, x, y, 0), AddEdge(i, j, 2, x, y, 1);
					}
				}
				else
				{
					if (k == 0)
					{
						if (a[x][y] == '1') AddEdge(i, j, 0, x, y, 1), AddEdge(i, j, 2, x, y, 0);
						else AddEdge(i, j, 2, x, y, 2), AddEdge(i, j, 0, x, y, 0);
					}
					else if (k == 1)
					{
						if (a[x][y] == '1') AddEdge(i, j, 0, x, y, 2), AddEdge(i, j, 1, x, y, 0);
						else AddEdge(i, j, 0, x, y, 0), AddEdge(i, j, 1, x, y, 2);
					}
					else if (k == 2) 
					{
						if (a[x][y] == '1') AddEdge(i, j, 0, x, y, 2), AddEdge(i, j, 1, x, y, 0);
						else AddEdge(i, j, 0, x, y, 0), AddEdge(i, j, 1, x, y, 1);
					}
					else
					{
						if (a[x][y] == '1') AddEdge(i, j, 0, x, y, 1), AddEdge(i, j, 2, x, y, 0);
						else AddEdge(i, j, 0, x, y, 0), AddEdge(i, j, 2, x, y, 1);
					}
				}
			}
	for (int i = 1; i <= n * m * 3; ++i) if (!v[i]) ++cnt, dfs(i);
	scanf("%d", &Q);
	while (Q--)
	{
		int x, y;
		scanf("%d%d", &x, &y);
		if ((x & 1) && (y & 1)) ans = s(x, y, 0);
		else if (!(x & 1) && !(y & 1))
			if (x == 0) 
			{
				if (y == 0) ans = s(x + 1, y + 1, 1);
				else ans = s(x + 1, y - 1, 2);
			}
			else if (y == 0) ans = s(x - 1, y + 1, 3);
			else ans = s(x - 1, y - 1, 4);
		else ans = 0;
		printf("%.4lf\n", ans);
	}
	return 0;
}
