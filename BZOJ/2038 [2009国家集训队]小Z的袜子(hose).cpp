#include <iostream>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <algorithm>
#include <cmath>

using namespace std;

const int MAXN = 50000 + 10;
const int MAXS = 35;

int n, Q, pn, sz;
int a[MAXN];
int sum[MAXS][MAXS][MAXN], tot[MAXS][MAXS];
int st[MAXS], en[MAXS];

void Init()
{
	scanf("%d%d", &n, &Q);
	for (int i = 1; i <= n; ++i) scanf("%d", &a[i]);
}

void Prepare()
{
	pn = 1;
	while ((pn + 1) * (pn + 1) * (pn + 1) <= n) pn++;
	pn = min(pn, 34);
	sz = n / pn;
	for (int i = 1; i <= pn; ++i) 
	{
		st[i] = (i - 1) * sz + 1;
		en[i] = i * sz;
	}
	en[pn] = n;
	for (int i = 1; i <= pn; ++i)
		for (int j = i; j <= pn; ++j)
			for (int k = st[i]; k <= en[j]; ++k) tot[i][j] += sum[i][j][a[k]], sum[i][j][a[k]]++;
}

long long gcd(long long a, long long b)
{
	long long tmp;
	while (b)
	{
		tmp = a % b;
		a = b;
		b = tmp;
	}
	return a;
}

int tmp[MAXN];

void Solve()
{
	while (Q--)
	{
		int l, r, x, y;
		long long ans;
		scanf("%d%d", &l, &r);
		x = 1; y = pn;
		for (; en[x] < l; ++x);
		for (; st[y] > r; --y);
		if (y - x <= 1)
		{
			ans = 0;
			for (int i = l; i <= r; ++i) ans += (long long)tmp[a[i]], tmp[a[i]]++;
			for (int i = l; i <= r; ++i) tmp[a[i]] = 0;
		}
		else
		{
			ans = tot[x + 1][y - 1];
			for (int i = l; i <= en[x]; ++i) ans += (long long)tmp[a[i]] + (long long)sum[x + 1][y - 1][a[i]], tmp[a[i]]++;
			for (int i = st[y]; i <= r; ++i) ans += (long long)tmp[a[i]] + (long long)sum[x + 1][y - 1][a[i]], tmp[a[i]]++;
			for (int i = l; i <= en[x]; ++i) tmp[a[i]] = 0;
			for (int i = st[y]; i <= r; ++i) tmp[a[i]] = 0;
		}
		if (ans == 0) puts("0/1");
		else 
		{
			long long bb = (long long)(r - l + 1)  * (long long)(r - l) / 2;
			long long d = gcd(ans, bb);
			ans /= d; bb /= d;
			printf("%lld/%lld\n", ans, bb);
		}
	}
}

int main()
{
	Init();
	Prepare();
	Solve();
	
	return 0;
}
