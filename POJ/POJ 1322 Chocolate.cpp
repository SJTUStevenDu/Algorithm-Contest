#include <iostream>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <cmath>
#include <fstream>
#include <algorithm>

using namespace std;

const int MAXN = 1000 + 10;
const int MAXC = 100 + 10;

double f[MAXN][MAXC];
int n, m, c;

int main()
{
	while (~scanf("%d", &c))
	{
		if (c == 0) break;
		scanf("%d%d", &n, &m);
		if (n < m || c < m || (n + m) % 2 == 1) {puts("0.000"); continue;}
		if (n > 1000) n = 1000 + n % 2;
		f[0][0] = 1;
		for (int i = 1; i <= n; ++i)
			for (int j = 0; j <= c; ++j)
			{
				if (j == 0) f[i][j] = f[i - 1][j + 1] / c;
				else if (j == c) f[i][j] = f[i - 1][j - 1] / c;
				else f[i][j] = f[i - 1][j + 1] * (j + 1) / c + f[i - 1][j - 1] * (c - j + 1) / c;
			}
		printf("%.3lf\n", f[n][m]);
	}
	
	return 0;
}
