#include <iostream>
#include <cstdio>
#include <cstring>
#include <cstdlib>

using namespace std;

const int MAXN = 1000 + 10;

int n, a[MAXN][MAXN], ans, f[MAXN][MAXN];

int main()
{
	scanf("%d", &n);
	for (int i = 1; i <= n; ++i)
		for (int j = 1; j <= i; ++j) scanf("%d", &a[i][j]);
	f[1][1] = a[1][1];
	for (int i = 2; i <= n; ++i)
		for (int j = 1; j <= i; ++j) 
			f[i][j] = max(f[i - 1][j - 1], f[i - 1][j]) + a[i][j];
	for (int i = 1; i <= n; ++i) ans = max(ans, f[n][i]);
	printf("%d\n", ans);
	return 0;
}
