#include <iostream>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <cmath>
#include <fstream>
#include <algorithm>

using namespace std;

const int MAXN = 40000 + 10;
const int INF = 1073741823;

int f[MAXN], a[MAXN], n, tot, nxt[MAXN * 2], tail[MAXN], v[MAXN * 2], stk[MAXN], len, x, w[MAXN], maxw, b[MAXN];
bool diff[MAXN];
long long g[MAXN], sum, tmp;

inline void Add(int a, int b)
{
	tot++; nxt[tail[a]] = tot; v[tot] = b; tail[a] = tot;
}

int main()
{
	scanf("%d", &n);
	a[0] = -INF;
	for (int i = 1; i <= n; ++i) scanf("%d", &a[i]), a[i] -= i;
	a[++n] = INF;
	for (int i = 1; i <= n; ++i) tail[i] = i;
	tot = n; stk[0] = -INF; Add(0, 0); len = 0;
	for (int i = 1; i <= n; ++i)
	{
		if (a[i] >= stk[len]) stk[f[i] = ++len] = a[i];
		else
		{
			int l = 0, r = len;
			while (l <= r)
			{
				int mid = (l + r) >> 1;
				if (stk[mid] <= a[i]) l = mid + 1;
				else r = mid - 1;
			}
			stk[f[i] = l] = a[i];
		}
		for (int j = nxt[f[i] - 1]; j; j = nxt[j]) if (a[i] >= a[x = v[j]]) break;
		w[x] = 0;
		for (int j = x + 1; j < i; ++j) if (a[j] < a[i]) w[j] = w[j - 1] + 1; else w[j] = w[j - 1] - 1;
		sum = 0; maxw = -INF; g[i] = ~0ULL >> 2;
		for (int j = i - 1; j >= x; --j)
		{
			if (a[j] <= a[i] && f[j] == f[i] - 1)
			{
				tmp = g[j] + sum; g[i] = min(g[i], tmp);
				tmp = g[j] + sum - (long long)(maxw - w[j]) * (a[i] - a[j]); g[i] = min(g[i], tmp);
			}
			sum += (long long)abs(a[i] - a[j]);
			maxw = max(maxw, w[j]);
		}
		Add(f[i], i);
	}
	printf("%d\n", n - f[n]);
	printf("%lld\n", g[n]);
	
	return 0;
}
