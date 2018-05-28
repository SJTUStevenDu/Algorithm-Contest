#include <iostream>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <algorithm>
#include <cmath>

using namespace std;

const int MAXN = 100000 + 10;

long long a[MAXN], s[MAXN];
int n, Q, opr, l, r, father[MAXN];

inline int lowbit(int x) {return x & (-x);}

inline void Add(int x, long long v)
{
	for (; x <= n; x += lowbit(x)) s[x] += v;
}

inline long long Query(int x)
{
	long long res = 0;
	for (; x; x -= lowbit(x)) res += s[x];
	return res;
}

int getfather(int x)
{
	return (father[x] == x) ? x : father[x] = getfather(father[x]);
}

int main()
{
	scanf("%d", &n);
	for (int i = 1; i <= n; ++i) scanf("%lld", &a[i]);
	for (int i = 1; i <= n; ++i) Add(i, a[i]);
	for (int i = 1; i <= n + 1; ++i) father[i] = i;
	scanf("%d", &Q);
	while (Q--)
	{
		scanf("%d%d%d", &opr, &l, &r);
		if (l > r) swap(l, r);
		if (opr == 1) printf("%lld\n", Query(r) - Query(l - 1));
		else for (int i = getfather(l); i <= r; i = getfather(i + 1))
		{
			long long m = (long long)floor(sqrt((double)a[i]));
			Add(i, m - a[i]);
			a[i] = m;
			if (m <= 1) father[i] = i + 1;
		}
	}
	
	return 0;
}
