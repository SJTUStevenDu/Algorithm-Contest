#include <iostream>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <cmath>
#include <fstream>
#include <algorithm>

using namespace std;

const int MAXN = 2200 + 10;

struct Node
{
	int h, w;
} a[MAXN];

bool cmp(Node A, Node B)
{
	return A.h > B.h;
}

int n, m, now, pre, ans = 0x7FFFFFFF >> 2;
int f[2][MAXN][MAXN];

inline void checkmin(int &x, int y) {if (x > y) x = y;}

int main()
{
	scanf("%d", &n);
	for (int i = 1; i <= n; ++i) scanf("%d%d", &a[i].h, &a[i].w), m += a[i].w;
	sort(a + 1, a + 1 + n, cmp);
	memset(f, 63, sizeof(f));
	now = 0; pre = 1;
	f[now][0][0] = 0;
	for (int i = 1; i <= n; ++i) 
	{
		now = now ^ 1; pre = pre ^ 1;
		for (int j = 0; j <= m; ++j)
			for (int k = 0; k <= m; ++k)
			{
				f[now][j][k] = f[pre][j][k];
				if (j == a[i].w) checkmin(f[now][j][k], f[pre][0][k] + a[i].h);
				if (j > a[i].w) checkmin(f[now][j][k], f[pre][j - a[i].w][k]);
				if (k == a[i].w) checkmin(f[now][j][k], f[pre][j][0] + a[i].h);
				if (k > a[i].w) checkmin(f[now][j][k], f[pre][j][k - a[i].w]);
			}
	}
	for (int i = 1; i <= m; ++i) 
		for (int j = 1; j <= m; ++j) 
		{
			long long tmp = (long long)(f[now][i][j] + a[1].h) * max(max(i, j), m - i - j);
			if (tmp < ans) ans = tmp;
		}
	printf("%d\n", ans);
	return 0;
}
