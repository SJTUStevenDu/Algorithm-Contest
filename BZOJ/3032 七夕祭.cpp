#include <iostream>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <cmath>
#include <fstream>
#include <algorithm>

using namespace std;

const int MAXN = 100000 + 10;

long long sx[MAXN], sy[MAXN];
int n, m, T;
long long ans;

int main()
{
	scanf("%d%d%d", &n, &m, &T);
	for (int x, y, i = 1; i <= T; ++i)
	{
		scanf("%d%d", &x, &y);
		sx[x]++; sy[y]++;
	}
	bool f1 = T % n, f2 = T % m;
	f1 = !f1; f2 = !f2;
	if (f1 && f2) printf("both ");
	else if (f2) printf("column ");
	else if (f1) printf("row ");
	else 
	{
		puts("impossible");
		return 0;
	}
	if (f1)
	{
		long long tmp = T / n;
		for (int i = 1; i <= n; ++i) sx[i] -= tmp;
		for (int i = 1; i <= n; ++i) sx[i] += sx[i - 1];
		sort(sx + 1, sx + 1 + n);
		tmp = sx[(n + 1) / 2];
		for (int i = 1; i <= n; ++i) ans += abs(tmp - sx[i]);
	}
	if (f2)
	{
		long long tmp = T / m;
		for (int i = 1; i <= m; ++i) sy[i] -= tmp;
		for (int i = 1; i <= m; ++i) sy[i] += sy[i - 1];
		sort(sy + 1, sy + 1 + m);
		tmp = sy[(m + 1) / 2];
		for (int i = 1; i <= m; ++i) ans += (long long)abs(tmp - sy[i]);
	}
	printf("%lld\n", ans);
	
	return 0;
}
