#include <iostream>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <algorithm>

using namespace std;

const int MAXN = 200000 + 10;
const int MOD = 16777216;

int n, a[MAXN];
long long c1[MAXN], c2[MAXN], c3[MAXN], c4[MAXN], c5[MAXN], c6[MAXN], b[MAXN], x, y, ans;

inline int lowbit(int x) {return x & (-x);}

inline void Add(long long s[], int x, long long v)
{
	for (; x <= n; x += lowbit(x)) s[x] += v;
}

inline long long Query(long long s[], int x)
{
	long long res = 0LL;
	for (; x; x -= lowbit(x)) res += s[x];
	return res;
}

inline long long C(long long x, int y)
{
	if (x < y) return 0;
	if (y == 2) return x * (x - 1) / 2;
	else return x * (x - 1) / 2 * (x - 2) / 3;
}

int main()
{
	scanf("%d", &n);
	for (int i = 1; i <= n; ++i) scanf("%d", &a[i]);
	for (int i = n; i; --i)
	{
		y = Query(c1, a[i]);
		x = b[i] = Query(c1, n) - y;
		ans = (ans - C(x, 3) + MOD) % MOD; //1xxx
		ans = (ans + Query(c3, n) - Query(c3, a[i]) + MOD) % MOD; //1234
		ans = (ans + x * (Query(c4, a[i]) - C(y, 2))) % MOD; //1x3x
		Add(c1, a[i], 1);
		Add(c2, a[i], x);
		x = Query(c2, n) - Query(c2, a[i]);
		Add(c3, a[i], x);
		Add(c4, a[i], a[i] - 1);
	}
	for (int i = 1; i <= n; ++i)
	{
		x = Query(c5, a[i]); y = Query(c6, a[i]);
		ans = (ans + b[i] * (x * i - y - C(x, 2))) % MOD;
		Add(c5, a[i], 1);
		Add(c6, a[i], i + 1); 
	}
	printf("%lld\n", ans);
	
	return 0;
}
