#include <iostream>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <cmath>
#include <fstream>
#include <algorithm>

using namespace std;

const int MAXN = 2000 + 10;

struct Node
{
	int a, b;
} x[MAXN];

bool cmp(Node A, Node B)
{
	return A.a + A.b < B.a + B.b;
}

int f[MAXN], n, ans, h;

int main()
{
	scanf("%d", &n);
	for (int i = 1; i <= n; ++i) scanf("%d%d", &x[i].a, &x[i].b), f[0] += x[i].a;
	for (int i = 1; i <= n; ++i) f[i] = -1;
	sort(x + 1, x + 1 + n, cmp);
	scanf("%d", &h);
	for (int i = 1; i <= n; ++i) 
	{
		for (int j = ans; j >= 0; --j) if (f[j] + x[i].b >= h)
			f[j + 1] = max(f[j + 1], f[j] - x[i].a);
		if (f[ans + 1] >= 0) ++ans;
	}
	printf("%d\n", ans);
	
	return 0;
}
