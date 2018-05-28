#include <iostream>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <cmath>
#include <algorithm>
#include <fstream>

using namespace std;

const int MAXN = 100000 + 10;
const int MOD = 1000000007;

struct Node
{
	int pos, p;
} a[MAXN];

bool cmp(Node A, Node B)
{
	return A.pos < B.pos || (A.pos == B.pos && A.p < B.p);
}

int n, m, k, tot;
long long bbb, b[MAXN], ans, c[MAXN];

long long QuickMod(long long a, int b)
{
	long long res = 1LL;
	while (b)
	{
		if (b & 1) res = res * a % MOD;
		b >>= 1;
		a = a * a % MOD;
	}
	return res;
}

int main()
{
	scanf("%d%d%d", &n, &m, &k);
	bbb = (long long) n * (n + 1) / 2;
	bbb %= MOD;
	for (int i = 1; i <= k; ++i) scanf("%d%d", &a[i].pos, &a[i].p);
	sort(a + 1, a + 1 + k, cmp);
	for (int i = 1; i <= k; ++i)
	{
		if (i != 1 && a[i].pos == a[i - 1].pos && a[i].p == a[i - 1].p) continue;
		if (c[tot] != a[i].pos) b[++tot] = a[i].p, c[tot] = a[i].pos;
		else b[tot] += a[i].p;
	}
	ans = QuickMod(bbb, m - tot);
	for (int i = 1; i <= tot; ++i)
	{
		b[i] = bbb - b[i];
		b[i] = (b[i] % MOD + MOD) % MOD;
		ans = ans * b[i] % MOD;
	}
	printf("%lld\n", ans);
	
	return 0;
}
