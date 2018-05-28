#include <iostream>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <cmath>
#include <fstream>
#include <algorithm>

using namespace std;

const int MAXN = 500 + 10;
const int MAXQ = 60000 + 10;
const int INF = 1000000000;

struct Node
{
	int x1, x2, y1, y2, type, cur, val, idx;
} q[MAXN * MAXN + MAXQ], q1[MAXN * MAXN + MAXQ], q2[MAXN * MAXN + MAXQ];

int n, Q, ans[MAXQ], tmp[MAXN * MAXN + MAXQ], c[MAXN][MAXN], tot;

inline int lowbit(int x) {return x & (-x);}

inline void Add(int x, int y, int d)
{
	for (int i = x; i <= n; i += lowbit(i))
		for (int j = y; j <= n; j += lowbit(j)) c[i][j] += d;
}

inline int Query(int x, int y)
{
	int ret = 0;
	for (int i = x; i; i -= lowbit(i))
		for (int j = y; j; j -= lowbit(j)) ret += c[i][j];
	return ret;
}

void Work(int head, int tail, int L, int R)
{
	if (head > tail) return;
	if (L == R)
	{
		for (int i = head; i <= tail; ++i) if (q[i].type == 2) ans[q[i].idx] = L;
		return;
	}
	int mid = (L + R) >> 1;
	for (int i = head; i <= tail; ++i) 
		if (q[i].type == 1 && q[i].val <= mid) Add(q[i].x1, q[i].y1, 1);
		else if (q[i].type == 2) tmp[i] = Query(q[i].x2, q[i].y2) + Query(q[i].x1 - 1, q[i].y1 - 1) - Query(q[i].x1 - 1, q[i].y2) - Query(q[i].x2, q[i].y1 - 1);
	for (int i = head; i <= tail; ++i) if (q[i].type == 1 && q[i].val <= mid) Add(q[i].x1, q[i].y1, -1);
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
			if (tmp[i] + q[i].cur > q[i].val - 1) q1[++l1] = q[i];
			else q[i].cur += tmp[i], q2[++l2] = q[i];
		}
	}
	for (int i = 1; i <= l1; ++i) q[i + head - 1] = q1[i];
	for (int i = 1; i <= l2; ++i) q[head + l1 + i - 1] = q2[i];
	Work(head, head + l1 - 1, L, mid);
	Work(head + l1, tail, mid + 1, R);
}

int main()
{
	scanf("%d%d", &n, &Q);
	for (int i = 1; i <= n; ++i)
		for (int j = 1; j <= n; ++j) 
		{
			int x;
			scanf("%d", &x);
			q[++tot].x1 = i; q[tot].y1 = j; q[tot].val = x; q[tot].type = 1;
		}
	for (int i = 1; i <= Q; ++i)
	{
		int x1, y1, x2, y2, k;
		scanf("%d%d%d%d%d", &x1, &y1, &x2, &y2, &k);
		q[++tot].x1 = x1; q[tot].x2 = x2; q[tot].y1 = y1; q[tot].y2 = y2; q[tot].val = k;
		q[tot].idx = i; q[tot].cur = 0; q[tot].type = 2;
	}
	Work(1, tot, 0, INF);
	for (int i = 1; i <= Q; ++i) printf("%d\n", ans[i]);
	
	return 0;
}
