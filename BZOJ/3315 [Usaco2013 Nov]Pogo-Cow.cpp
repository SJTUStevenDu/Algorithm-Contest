#include <iostream>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <cmath>
#include <algorithm>
#include <fstream>

using namespace std;

const int MAXN = 1000 + 10;

struct Seg_Tree
{
	int left, right, data;
} seg[MAXN][MAXN << 2];

struct Node 
{
	int x, p;
} c[MAXN];

bool cmp(Node A, Node B)
{
	return A.x < B.x;
}

int n, f[MAXN][MAXN], ans, ro[MAXN];

inline void Pushup(int p, int i)
{
	seg[i][p].data = max(seg[i][p << 1].data, seg[i][p << 1 | 1].data);
}

void Build(int p, int l, int r, int i)
{
	seg[i][p].left = l; seg[i][p].right = r;
	if (l == r)
	{
		seg[i][p].data = f[i][l];
		return;
	}
	int mid = (l + r) >> 1;
	Build(p << 1, l, mid, i);
	Build(p << 1 | 1, mid + 1, r, i);
	Pushup(p, i);
}

int Query(int p, int l, int r, int i)
{
	if (l == seg[i][p].left && r == seg[i][p].right) return seg[i][p].data;
	int mid = (seg[i][p].left + seg[i][p].right) >> 1;
	if (l > mid) return Query(p << 1 | 1, l, r, i);
	else if (r <= mid) return Query(p << 1, l, r, i);
	return max(Query(p << 1, l, mid, i), Query(p << 1 | 1, mid + 1, r, i));
}

int main()
{
	scanf("%d", &n);
	for (int i = 1; i <= n; ++i) scanf("%d%d", &c[i].x, &c[i].p);
	sort(c + 1, c + 1 + n, cmp);
	int pos = 1;
	for (int i = 1; i <= n; ++i)
	{
		pos = 1;
		f[i][0] = c[i].p;
		for (int j = 1; j < i; ++j)
		{
			f[i][j] = f[j][0] + c[i].p;
			while (c[j].x - c[pos].x > c[i].x - c[j].x) ++pos;
			if (pos < j) f[i][j] = max(f[i][j], Query(1, pos, j - 1, j) + c[i].p);
		}
		Build(1, 1, n, i);
	}
	for (int i = 1; i <= n; ++i)
		for (int j = 0; j < i; ++j) ans = max(ans, f[i][j]);
	for (int i = 1; i <= n / 2; ++i) swap(c[i], c[n - i + 1]);
	memset(f, 0, sizeof(f));
	memset(seg, 0, sizeof(seg));
	for (int i = 1; i <= n; ++i)
	{
		pos = 1;
		f[i][0] = c[i].p;
		for (int j = 1; j < i; ++j)
		{
			f[i][j] = f[j][0] + c[i].p;
			while (c[pos].x - c[j].x > c[j].x - c[i].x) ++pos;
			if (pos < j) f[i][j] = max(f[i][j], Query(1, pos, j - 1, j) + c[i].p);
		}
		Build(1, 1, n, i);
	}
	for (int i = 1; i <= n; ++i)
		for (int j = 0; j < i; ++j) ans = max(ans, f[i][j]);
	printf("%d\n", ans);
	
	return 0;
}
