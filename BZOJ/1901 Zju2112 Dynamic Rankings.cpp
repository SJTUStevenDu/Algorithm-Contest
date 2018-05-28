#include <iostream>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <algorithm>
#include <cmath>

using namespace std;

const int MAXN = 10000 + 10;
const int MAXT = MAXN * 900;
const int MAXC = 1000000000;

int n, Q, tot;
int root[MAXN], a[MAXN], u[MAXN], v[MAXN], l[MAXT], r[MAXT], s[MAXT];

inline int lowbit(int x) {return x & (-x);}

void Insert(int &x, int L, int R, int v, int d)
{
	if (!x) x = ++tot;
	s[x] += d;
	if (L == R) return;
	int mid = (L + R) >> 1;
	if (v <= mid) Insert(l[x], L, mid, v, d);
	else Insert(r[x], mid + 1, R, v, d);
}

inline void Update(int x, int v, int d)
{
	for (; x <= n; x += lowbit(x)) Insert(root[x], 0, MAXC, v, d);
}

inline int Query(int x)
{
	int ret = 0;
	for (; x; x -= lowbit(x)) ret += s[l[u[x]]];
	return ret;
}

inline int init(int x)
{
	for (; x; x -= lowbit(x)) u[x] = root[x], v[x] = 0;
}

inline void turnl(int x, int cnt)
{
	for (; x; x -= lowbit(x)) if (v[x] != cnt) u[x] = l[u[x]], v[x] = cnt;
}

inline void turnr(int x, int cnt)
{
	for (; x; x -= lowbit(x)) if (v[x] != cnt) u[x] = r[u[x]], v[x] = cnt;
}

char opr[5];
int x, y, z;

int main()
{
	scanf("%d%d", &n, &Q);
	for (int i = 1; i <= n; ++i) 
	{
		scanf("%d", &a[i]);
		Update(i, a[i], 1);
	}	
	while (Q--)
	{
		scanf("%s", opr);
		if (opr[0] == 'C')
		{
			scanf("%d%d", &x, &y);
			Update(x, a[x], -1);
			Update(x, a[x] = y, 1);
		}
		else 
		{
			scanf("%d%d%d", &x, &y, &z);
			int cnt = 0;
			init(y); init(x - 1);
			int L = 0, R = MAXC;
			while (L < R) 
			{
				int mid = (L + R) >> 1;
				++cnt;
				int cur = Query(y) - Query(x - 1);
				if (z <= cur)
				{
					R = mid;
					turnl(y, cnt); turnl(x - 1, cnt);
				}
				else 
				{
					L = mid + 1; z -= cur;
					turnr(y, cnt); turnr(x - 1, cnt);
				}
			}
			printf("%d\n", L);
		}
	}
	
	return 0;
}
