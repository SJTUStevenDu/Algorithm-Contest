#include <iostream>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <cmath>
#include <fstream>
#include <algorithm>

using namespace std;

const int MAXN = 100000 + 10;

int n, m, x;
long long c1[MAXN], c2[MAXN], a[MAXN], y;

inline int lowbit(int x) {return x & (-x);}

inline void Add(long long c[], int x, long long v)
{
	for (int i = x; i <= n; i += lowbit(i)) c[i] += v;
}

inline long long Query(long long c[], int x)
{
	long long ret = 0;
	for (; x > 0; x -= lowbit(x)) ret += c[x];
	return ret;
}

char opr[10];

int main()
{
	scanf("%d%d", &n, &m);
	for (int i = 1; i <= n; ++i) scanf("%lld", &a[i]);
	for (int i = 1; i <= n; ++i) Add(c1, i, a[i]), Add(c2, i, (n - i + 1) * a[i]);
	while (m--)
	{
		scanf("%s", opr);
		if (opr[0] == 'Q') 
		{
			scanf("%d", &x);
			long long cur1 = Query(c1, x), cur2 = Query(c2, x);
			printf("%lld\n", cur2 - cur1 * (n - x));
		}
		else 
		{
			scanf("%d%lld", &x, &y);
			Add(c1, x, -a[x]); Add(c2, x, -(n - x + 1) * a[x]);
			a[x] = y;
			Add(c1, x, a[x]); Add(c2, x, (n - x + 1) * a[x]);
		}
	}
	
	return 0;
}
