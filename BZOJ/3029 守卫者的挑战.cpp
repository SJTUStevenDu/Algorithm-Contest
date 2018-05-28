#include <iostream>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <cmath>
#include <fstream>
#include <algorithm>

using namespace std;

const int MAXN = 400 + 10;

double f[2][MAXN][MAXN];
int a[MAXN], n, m, t, pre, now;
double p[MAXN], ans;

int main()
{
	scanf("%d%d%d", &n, &m, &t);
	if (t > n) t = n;
	for (int i = 1; i <= n; ++i) scanf("%lf", &p[i]), p[i] /= 100;
	for (int i = 1; i <= n; ++i) scanf("%d", &a[i]);
	pre = 1; now = 0;
	f[0][0][t + 200] = 1;
	for (int i = 0; i < n; ++i)
	{
		now ^= 1; pre ^= 1;
		for (int j = 0; j <= n; ++j)
			for (int k = -n; k <= n; ++k) f[now][j][k + 200] = 0;
		for (int j = 0; j <= n; ++j)
			for (int k = -n; k <= n; ++k)
			{
				if (a[i + 1] == -1)
				{
					f[now][j + 1][k - 1 + 200] += f[pre][j][k + 200] * p[i + 1];
					f[now][j][k + 200] += f[pre][j][k + 200] * (1 - p[i + 1]);
				}
				else 
				{
					f[now][j + 1][min(k + a[i + 1], n) + 200] += f[pre][j][k + 200] * p[i + 1];
					f[now][j][k + 200] += f[pre][j][k + 200] * (1 - p[i + 1]);
				}
			}
	}
	for (int i = m; i <= n; ++i)
		for (int j = 0; j <= n; ++j) ans += f[now][i][j + 200];
	printf("%.6lf\n", ans);
	
	return 0;
}
