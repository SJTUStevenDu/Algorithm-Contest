#include <iostream>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <cmath>
#include <fstream>
#include <algorithm>

using namespace std;

const int MAXN = 1500 * 1500 + 10;
const int MAXM = 1500 + 10;

struct Node
{
	int id1, id2;
	long long dist, zx, zy;
} a[MAXN];

long long ans, x[MAXM], y[MAXM];
int n, tot;

bool cmp(Node A, Node B)
{
	if (A.dist != B.dist) return A.dist < B.dist;
	if (A.zx != B.zx) return A.zx < B.zx;
	return A.zy < B.zy;
}

inline long long Getdist(int a, int b)
{
	return (x[a] - x[b]) * (x[a] - x[b]) + (y[a] - y[b]) * (y[a] - y[b]);
}

inline long long CalcS(int a, int b, int c)
{
	long long x1 = x[a] - x[c], x2 = x[b] - x[c], y1 = y[a] - y[c], y2 = y[b] - y[c];
	return x1 * y2 - x2 * y1;
}

int main()
{
	scanf("%d", &n);
	for (int i = 1; i <= n; ++i) scanf("%lld%lld", &x[i], &y[i]), x[i] *= 2, y[i] *= 2;
	for (int i = 1; i <= n; ++i)
		for (int j = i + 1; j <= n; ++j) 
		{
			++tot; a[tot].id1 = i; a[tot].id2 = j; a[tot].dist = Getdist(i, j);
			a[tot].zx = (x[i] + x[j]) / 2; a[tot].zy = (y[i] + y[j]) / 2;
		}
	sort(a + 1, a + 1 + tot, cmp);
	for (int i = 1; i <= tot;)
	{
		int j;
		for (j = i + 1; j <= tot; ++j) if (a[j].zx != a[i].zx || a[j].zy != a[i].zy || a[j].dist != a[i].dist) break;
		for (int k1 = i; k1 < j; ++k1)
			for (int k2 = k1 + 1; k2 < j; ++k2)
				ans = max(ans, abs(CalcS(a[k1].id1, a[k1].id2, a[k2].id1)));
		i = j;
	}
	printf("%lld\n", ans / 4);
	
	return 0;
}
