#include <iostream>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <cmath>
#include <fstream>
#include <algorithm>

using namespace std;

const int MAXN = 10000 + 10;

int a[MAXN], n, m, ans;

int main()
{
	scanf("%d%d", &n, &m);
	for (int i = 1; i <= n; ++i) scanf("%d", &a[i]), a[i] *= 2;
	for (int x, y, z, i = 1; i <= m; ++i) 
	{
		scanf("%d%d%d", &x, &y, &z);
		a[x] += z; a[y] += z;
	}
	sort(a + 1, a + 1 + n);
	for (int i = 1; i <= n; i += 2) ans += (a[i + 1] - a[i]);
	printf("%d\n", ans / 2);
	
	return 0;
}
