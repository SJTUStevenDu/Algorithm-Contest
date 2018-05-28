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
	int l, r, idx, cur, type, val;
} q[MAXN], q1[MAXN], q2[MAXN];

int Q, n, tot, c1[MAXN], c2[MAXN], tmp[MAXN], ans[MAXN];

inline int lowbit(int x) {return x & (-x);}

inline void Add(int c[], int x, int v)
{
	for (int i = x; i <= n; i += lowbit(i)) c[i] += v;
}

inline int Query(int c[], int x)
{
	int ret = 0;
	for (int i = x; i; i -= lowbit(i)) ret += c[i];
	return ret;
}

inline void Modify(int l, int r, int d)
{
	Add(c1, l - 1, -d * (l - 1));
	Add(c1, r, d * r);
	Add(c2, 1, -d);
	Add(c2, l - 1, d);
	Add(c2, 1, d);
	Add(c2, r, -d);
}

void Solve(int head, int tail, int L, int R)
{
	if (head > tail) return;
	if (L == R)
	{
		for (int i = head; i <= tail; ++i) ans[q[i].idx] = L;
		return;
	}
	int mid = (L + R) >> 1;
	for (int i = head; i <= tail; ++i)
	{
		if (q[i].type == 1 && mid < q[i].val) Modify(q[i].l + 1, q[i].r + 1, 1);
		else if (q[i].type == 2) tmp[i] = Query(c1, q[i].r + 1) + Query(c2, q[i].r + 1) * (q[i].r + 1) - Query(c1, q[i].l) - Query(c2, q[i].l) * q[i].l;
	}
	for (int i = head; i <= tail; ++i) if (q[i].type == 1 && mid < q[i].val) Modify(q[i].l + 1, q[i].r + 1, -1);
	int l1 = 0, l2 = 0;
	for (int i = head; i <= tail; ++i)
	{
		if (q[i].type == 1)
		{
			if (q[i].val <= mid) q1[++l1] = q[i];
			else q2[++l2] = q[i];
		}
		else 
		{
			if (q[i].cur + tmp[i] > q[i].val - 1) q2[++l2] = q[i];
			else q[i].cur += tmp[i], q1[++l1] = q[i];
		}
	}
	for (int i = 1; i <= l1; ++i) q[head + i - 1] = q1[i];
	for (int i = 1; i <= l2; ++i) q[head + l1 + i - 1] = q2[i];
	Solve(head, head + l1 - 1, L, mid);
	Solve(head + l1, tail, mid + 1, R);
}

int main()
{
	scanf("%d%d", &n, &Q);
	for (int i = 1; i <= Q; ++i) 
	{
		scanf("%d%d%d%d", &q[i].type, &q[i].l, &q[i].r, &q[i].val);
		if (q[i].type == 2) q[i].idx = ++tot;
	}
	Solve(1, Q, -n, n);
	for (int i = 1; i <= tot; ++i) printf("%d\n", ans[i]);
	
	return 0;
}
