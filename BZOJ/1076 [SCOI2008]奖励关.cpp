#include <iostream>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <cmath>
#include <algorithm>
#include <fstream>

using namespace std;

const int MAXN = 100 + 10;
const int MAXC = 1 << 16;

double f[MAXN][MAXC];
int n, k, p[MAXN], d[MAXN], w[MAXN];

int main()
{
	scanf("%d%d", &k, &n);
	for (int i = 1; i <= 20; ++i) d[i] = (1 << (i - 1));
	for (int i = 1; i <= n; ++i)
	{
		scanf("%d", &w[i]);
		int x;
		scanf("%d", &x);
		while (x)
		{
			p[i] += d[x];
			scanf("%d", &x);
		}
	}
	for (int i = k; i; i--)
		for (int j = 0; j < d[n + 1]; ++j) 
		{
			f[i][j] = 0;
			for (int s = 1; s <= n; ++s)
				if ((p[s] & j) == p[s]) f[i][j] += max(f[i + 1][j], f[i + 1][j | d[s]] + w[s]);
				else f[i][j] += f[i + 1][j];
			f[i][j] = f[i][j] / n;
		}
	printf("%.6lf\n", f[1][0]);
	
	return 0;
}
