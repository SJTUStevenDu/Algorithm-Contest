#include <iostream>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <cmath>
#include <algorithm>
#include <fstream>

using namespace std;

const int MAXN = 50000 + 10;

struct Seg_Tree
{
	int left, right, data;
} seg[MAXN << 2];

struct Node 
{
	int x, h;
} c[MAXN];

bool cmp(Node A, Node B)
{
	return A.x < B.x;
}

int n, d, ans;

inline void Pushup(int p)
{
	seg[p].data = max(seg[p << 1].data, seg[p << 1 | 1].data);
}

void Build(int p, int l, int r)
{
	seg[p].left = l; seg[p].right = r;
	if (l == r)
	{
		seg[p].data = c[l].h;
		return;
	}
	int mid = (l + r) >> 1;
	Build(p << 1, l, mid);
	Build(p << 1 | 1, mid + 1, r);
	Pushup(p);
}

int Query(int p, int l, int r)
{
	if (l == seg[p].left && r == seg[p].right) return seg[p].data;
	int mid = (seg[p].left + seg[p].right) >> 1;
	if (l > mid) return Query(p << 1 | 1, l, r);
	else if (r <= mid) return Query(p << 1, l, r);
	return max(Query(p << 1, l, mid), Query(p << 1 | 1, mid + 1, r));
}

int main()
{
	scanf("%d%d", &n, &d);
	for (int i = 1; i <= n; ++i) scanf("%d%d", &c[i].x, &c[i].h);
	sort(c + 1, c + 1 + n, cmp);
	Build(1, 1, n);
	int pos1, pos2;
	pos1 = pos2 = 1;
	for (int i = 1; i <= n; ++i)
	{
		while (c[pos1].x + d < c[i].x) ++pos1;
		while (c[pos2].x - d <= c[i].x && pos2 <= n) ++pos2;
		--pos2;
		if (pos1 == i || pos2 == i) continue;
		if (Query(1, pos1, i - 1) < 2 * c[i].h) continue;
		if (Query(1, i + 1, pos2) < 2 * c[i].h) continue;
		++ans;
	}
	printf("%d\n", ans);
	
	return 0;
}
