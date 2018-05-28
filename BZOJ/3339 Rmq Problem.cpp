#include <iostream>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <algorithm>
#include <cmath>

using namespace std;

const int MAXN = 200000 + 10;
const int MAXT = 4000000 + 20;

int root[MAXN], l[MAXT], r[MAXT], d[MAXT], tot, n, Q;

void insert(int x, int &y, int L, int R, int p, int v)
{
	y = ++tot;
	if (L == R) 
	{
		d[y] = v;
		return;
	}
	int mid = (L + R) >> 1;
	if (p <= mid)
	{
		insert(l[x], l[y], L, mid, p, v);
		r[y] = r[x];
	}
	else 
	{
		insert(r[x], r[y], mid + 1, R, p, v);
		l[y] = l[x];
	}
	d[y] = min(d[l[y]], d[r[y]]);
}

int Query(int x, int L, int R, int p)
{
	if (L == R) return L;
	int mid = (L + R) >> 1;
	if (d[l[x]] < p) return Query(l[x], L, mid, p);
	else return Query(r[x], mid + 1, R, p);
}

int main()
{
	scanf("%d%d", &n, &Q);
	for (int x, i = 1; i <= n; ++i)
	{
		scanf("%d", &x);
		insert(root[i - 1], root[i], 0, MAXN, x, i);
	}
	while (Q--)
	{
		int x, y;
		scanf("%d%d", &x, &y);
		printf("%d\n", Query(root[y], 0, MAXN, x));
	}
	
	return 0;
}
