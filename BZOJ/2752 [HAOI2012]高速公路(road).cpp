#include <iostream>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <cmath>
#include <fstream>
#include <algorithm>

using namespace std;

const int MAXN = 100000 + 10;

struct Node
{
	long long s0, s1, s2, lazy;
	int left, right;
} seg[MAXN << 2], tmp[MAXN << 2];

int n, Q, x, y;
long long sx1[MAXN], sx2[MAXN], z;

long long gcd(long long n, long long m)
{
	long long tmp;
	while (m)
	{
		tmp = n % m;
		n = m;
		m = tmp;
	}
	return n;
}

void Pushup(int p);
void Pushdown(int p);

void Build(int p, int l, int r)
{
	seg[p].left = l; seg[p].right = r;
	if (l == r) 
	{
		seg[p].s0 = seg[p].s1 = seg[p].s2 = seg[p].lazy = 0;
		return;
	}
	int mid = (l + r) >> 1;
	Build(p << 1, l, mid);
	Build(p << 1 | 1, mid + 1, r);
}

void Modify(int p, int l, int r, long long v)
{
	if (l == seg[p].left && r == seg[p].right)
	{
		seg[p].lazy += v;
		seg[p].s0 += (seg[p].right - seg[p].left + 1) * v;
		seg[p].s1 += (sx1[r] - sx1[l - 1]) * v;
		seg[p].s2 += (sx2[r] - sx2[l - 1]) * v;
		return;
	}
	Pushdown(p);
	int mid = (seg[p].left + seg[p].right) >> 1;
	if (l > mid) Modify(p << 1 | 1, l, r, v);
	else if (r <= mid) Modify(p << 1, l, r, v);
	else Modify(p << 1, l, mid, v), Modify(p << 1 | 1, mid + 1, r, v);
	Pushup(p);
}

void Query(int p, int l, int r)
{
	if (l == seg[p].left && r == seg[p].right) 
	{
		tmp[p] = seg[p];
		return;
	}
	Pushdown(p);
	int mid = (seg[p].left + seg[p].right) >> 1;
	if (l > mid) 
	{
		Query(p << 1 | 1, l, r);
		tmp[p] = tmp[p << 1 | 1];
		return;
	}
	else if (r <= mid)
	{
		Query(p << 1, l, r);
		tmp[p] = tmp[p << 1];
		return;
	}
	Query(p << 1, l, mid);
	Query(p << 1 | 1, mid + 1, r);
	tmp[p].s0 = tmp[p << 1].s0 + tmp[p << 1 | 1].s0;
	tmp[p].s1 = tmp[p << 1].s1 + tmp[p << 1 | 1].s1;
	tmp[p].s2 = tmp[p << 1].s2 + tmp[p << 1 | 1].s2;
}

void Pushup(int p)
{
	seg[p].s0 = seg[p << 1].s0 + seg[p << 1 | 1].s0;
	seg[p].s1 = seg[p << 1].s1 + seg[p << 1 | 1].s1;
	seg[p].s2 = seg[p << 1].s2 + seg[p << 1 | 1].s2;
}

void Pushdown(int p)
{
	if (seg[p].lazy == 0) return;
	long long x = seg[p].lazy;
	int mid = (seg[p].left + seg[p].right) >> 1;
	seg[p].lazy = 0;
	if (seg[p].left == seg[p].right) return;
	Modify(p << 1, seg[p].left, mid, x);
	Modify(p << 1 | 1, mid + 1, seg[p].right, x);
}

char opr[5];

int main()
{
	scanf("%d%d", &n, &Q);
	for (int i = 1; i <= n; ++i) sx1[i] = sx1[i - 1] + (long long)i;
	for (int i = 1; i <= n; ++i) sx2[i] = sx2[i - 1] + (long long)i * i;
	Build(1, 1, n - 1);
	while (Q--)
	{
		scanf("%s", opr);
		scanf("%d%d", &x, &y);
		if (opr[0] == 'Q')
		{
			Query(1, x, y - 1);
			long long ans1 = -tmp[1].s2 + (long long)(y + x - 1) * tmp[1].s1 - tmp[1].s0 * y * (x - 1);
			long long ans2 = (long long)(y - x + 1) * (y - x) / 2;
			long long gg = gcd(ans1, ans2);
			printf("%lld/%lld\n", ans1 / gg, ans2 / gg);
		}
		else 
		{
			scanf("%lld", &z);
			Modify(1, x, y - 1, z);
		}
	}
	
	return 0;
}
