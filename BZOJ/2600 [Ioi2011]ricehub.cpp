#include <iostream>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <cmath>
#include <fstream>
#include <algorithm>

using namespace std;

const int MAXN = 100000 + 10;

int n, xxxx, ans;
long long lim, sum[MAXN], a[MAXN];

long long calc(int l, int r)
{
	int mid = (l + r) / 2;
	return a[mid] * (mid - l + 1) - (sum[mid] - sum[l - 1]) + (sum[r] - sum[mid]) - a[mid] * (r - mid);
}

int main()
{
	scanf("%d%d%lld", &n, &xxxx, &lim);
	for (int i = 1; i <= n; ++i) scanf("%lld", &a[i]), sum[i] = sum[i - 1] + a[i];
	int l = 1;
	for (int r = 1; r <= n; ++r)
	{
		while (calc(l, r) > lim) ++l;
		ans = max(ans, r - l + 1);
	}
	printf("%d\n", ans);
	
	return 0;
}
