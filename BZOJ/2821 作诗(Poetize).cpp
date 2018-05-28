#include <iostream>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <cmath>
#include <fstream>
#include <algorithm>

using namespace std;

const int MAXN = 100000 + 10;
const int MAXM = 400 + 10;

int n, Q, c, sz, m, ans;
int cnt[MAXN], num[MAXN], be[MAXM], en[MAXM], rank[MAXN], numbe[MAXN], numen[MAXN], dp[MAXM][MAXM];

int Calc(int p, int x, int y)
{
	if (x > y) return 0;
	int l = numbe[p], r = numen[p];
	while (l <= r)
	{
		int mid = (l + r) >> 1;
		if (rank[mid] < x) l = mid + 1;
		else r = mid - 1;
	}
	x = l;
	l = numbe[p], r = numen[p];
	while (l <= r)
	{
		int mid = (l + r) >> 1;
		if (rank[mid] > y) r = mid - 1;
		else l = mid + 1;
	}
	y = r;
	return y - x + 1;
}

int q[MAXN], vis[MAXN];

int main()
{
	scanf("%d%d%d", &n, &c, &Q);
	for (int i = 1; i <= n; ++i) scanf("%d", &num[i]);
	for (int i = 1; i <= n; ++i) cnt[num[i]]++;
	int tot = 0;
	for (int i = 1; i <= c; ++i) numbe[i] = tot + 1, tot += cnt[i], numen[i] = tot;
	memset(cnt, 0, sizeof(cnt));
	for (int i = 1; i <= n; ++i) rank[numbe[num[i]] + cnt[num[i]]] = i, cnt[num[i]]++;
	m = (int)sqrt(n);
	sz = n / m;
	for (int i = 1; i <= m; ++i) be[i] = (i - 1) * sz + 1, en[i] = i * sz;
	if (en[m] < n)
	{
		++m;
		be[m] = en[m - 1] + 1;
		en[m] = n;
	}
	for (int i = 1; i <= m; ++i)
	{
		memset(cnt, 0, sizeof(cnt));
		ans = 0;
		for (int j = i; j <= m; ++j) 
		{
			for (int k = be[j]; k <= en[j]; ++k)
			{
				++cnt[num[k]];
				if (cnt[num[k]] == 1) continue;
				if (cnt[num[k]] & 1) ans--;
				else ++ans;
			}
			dp[i][j] = ans;
		}
	}
	ans = 0;
	for (int z = 1; z <= Q; ++z)
	{
		int l, r;
		scanf("%d%d", &l, &r);
		l = (l + ans) % n + 1; r = (r + ans) % n + 1;
		if (l > r) swap(l, r);
		int x, y;
		for (x = 1; x <= m; ++x) if (en[x] >= l) break;
		for (y = m; y; --y) if (be[y] <= r) break;
		ans = dp[x + 1][y - 1];
		if (x == y)
			for (int i = l; i <= r; ++i) if (vis[num[i]] != z) vis[num[i]] = z, cnt[num[i]] = 1;
			else {
				cnt[num[i]]++;
				if (cnt[num[i]] & 1) ans--;
				else ans++;
			}
		else 
		{
			tot = 0;
			for (int i = l; i <= en[x]; ++i) 
				if (vis[num[i]] != z) vis[num[i]] = z, cnt[num[i]] = 1, q[++tot] = num[i];
				else ++cnt[num[i]];
			for (int i = be[y]; i <= r; ++i) 
				if (vis[num[i]] != z) vis[num[i]] = z, cnt[num[i]] = 1, q[++tot] = num[i];
				else ++cnt[num[i]];
			for (int i = 1; i <= tot; ++i)
			{
				int p = q[i];
				int k = Calc(p, be[x + 1], en[y - 1]);
				if (!k && cnt[p] % 2 == 0) ++ans;
				if (k && k % 2 == 1 && cnt[p] % 2 == 1) ++ans;
				if (k && k % 2 == 0 && cnt[p] % 2 == 1) --ans;
			}
		}
		printf("%d\n", ans);
	}
	
	return 0;
}
