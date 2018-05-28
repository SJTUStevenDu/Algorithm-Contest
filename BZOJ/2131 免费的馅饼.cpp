#include <iostream>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <cmath>
#include <algorithm>
#include <fstream>

using namespace std;

const int MAXN = 100000 + 10;

struct Node
{
	int x, y, w;
} a[MAXN];

inline bool cmp1(Node A, Node B)
{
	return A.x < B.x;
}

inline bool cmp2(Node A, Node B)
{
	return A.y < B.y;
}

int n, s[MAXN], W, neww[MAXN], tot;

inline void checkmax(int &x, int y)
{
	if (y > x) x = y;
}

inline int lowbit(int x) {return x & (-x);}

inline int Query(int x)
{
	int ret = 0;
	for (; x; x -= lowbit(x)) checkmax(ret, s[x]);
	return ret;
}

inline void Add(int x, int v)
{
	for (; x <= tot; x += lowbit(x)) checkmax(s[x], v);
}

int main()
{
	scanf("%d%d", &W, &n);
	for (int aa, bb, cc, i = 1; i <= n; ++i) 
	{
		scanf("%d%d%d", &aa, &bb, &cc);
		a[i].x = aa * 2 - bb;
		a[i].y = aa * 2 + bb;
		a[i].w = cc;
	}
	sort(a + 1, a + 1 + n, cmp2);
	for (int i = 1; i <= n; ++i) neww[i] = (tot += a[i].y != a[i - 1].y);
	for (int i = 1; i <= n; ++i) a[i].y = neww[i];
	sort(a + 1, a + 1 + n, cmp1);
	for (int i = 1; i <= n; ++i) Add(a[i].y, Query(a[i].y) + a[i].w);
	printf("%d\n", Query(tot));
	
	return 0;
}
