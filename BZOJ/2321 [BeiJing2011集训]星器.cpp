#include <iostream>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <cmath>
#include <algorithm>
#include <fstream>

using namespace std;

const int MAXN = 200 + 10;

int n, m, a[MAXN][MAXN];
long long ans;

int main()
{
	scanf("%d%d", &n, &m);
	for (int i = 1; i <= n; ++i) 
		for (int j = 1; j <= m; ++j) scanf("%d", &a[i][j]);
	for (int x, i = 1; i <= n; ++i)
		for (int j = 1; j <= m; ++j)
		{
			scanf("%d", &x);
			a[i][j] -= x;
			ans += (long long)a[i][j] * (long long)(i * i + j * j);
		}
	printf("%lld\n", ans / 2);
	
	return 0;
}
