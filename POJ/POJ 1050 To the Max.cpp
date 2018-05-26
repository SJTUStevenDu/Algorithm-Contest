#include <iostream>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <cmath>
#include <algorithm>
#include <fstream>

using namespace std;

const int MAXN = 100 + 10;

int a[MAXN][MAXN];
int n, ans;
int sum[MAXN];

int main()
{
	scanf("%d", &n);
	for (int i = 1; i <= n; ++i)
		for (int j = 1; j <= n; ++j) scanf("%d", &a[i][j]);
	for (int i = 1; i <= n; ++i)
	{
		memset(sum, 0, sizeof(sum));
		for (int j = i; j <= n; ++j)
		{
			int now = 0;
			for (int k = 1; k <= n; ++k)
			{
				sum[k] += a[j][k];
				now += sum[k];
				if (now < 0) now = 0;
				ans = max(ans, now);
			}
		}
	}
	printf("%d\n", ans);
	
	return 0;
}
