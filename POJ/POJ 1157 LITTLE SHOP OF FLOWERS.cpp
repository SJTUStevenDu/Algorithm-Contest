#include <iostream>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <cmath>
#include <fstream>
#include <algorithm>

using namespace std;

const int MAXN = 100 + 10;

int f[MAXN][MAXN], a[MAXN][MAXN], n, m;

int main()
{
	scanf("%d%d", &n, &m);
	for (int i = 1; i <= n; ++i)
		for (int j = 1; j <= m; ++j) scanf("%d", &a[i][j]);
	for (int i = 1; i <= n; ++i)
		for (int j = 1; j <= m; ++j)
		{
			f[i][j] = f[i - 1][j - 1] + a[i][j];
			if (j > i) f[i][j] = max(f[i][j], f[i][j - 1]);
		}
	printf("%d\n", f[n][m]);
	
	return 0;
}
