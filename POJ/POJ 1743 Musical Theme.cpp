#include <iostream>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <algorithm>
#include <cmath>

using namespace std;

const int MAXN = 20000 + 10;

int a[MAXN], wa[MAXN], wb[MAXN], wv[MAXN], ra[MAXN], sa[MAXN], rank[MAXN], h[MAXN];
int n, m;

void BuildSA()
{
	int p = 1, *x = wa, *y = wb;
	for (int i = 0; i < m; ++i) ra[i] = 0;
	for (int i = 0; i < n; ++i) ra[x[i] = a[i]]++;
	for (int i = 1; i < m; ++i) ra[i] += ra[i - 1];
	for (int i = n - 1; i >= 0; --i) sa[--ra[x[i]]] = i;
	for (int j = 1; p < n; j *= 2)
	{
		p = 0;
		for (int i = n - j; i < n; ++i) y[p++] = i;
		for (int i = 0; i < n; ++i) if (sa[i] >= j) y[p++] = sa[i] - j;
		for (int i = 0; i < m; ++i) ra[i] = 0;
		for (int i = 0; i < n; ++i) ra[wv[i] = x[y[i]]]++;
		for (int i = 1; i < m; ++i) ra[i] += ra[i - 1];
		for (int i = n - 1; i >= 0; --i) sa[--ra[wv[i]]] = y[i];
		int *t = x; x = y; y = t;
		p = 1; x[sa[0]] = 0;
		for (int i = 1; i < n; ++i) 
			if (y[sa[i]] == y[sa[i - 1]] && y[sa[i] + j] == y[sa[i - 1] + j]) x[sa[i]] = p - 1; else x[sa[i]] = p++;
		m = p;
	}
	--n;
	for (int i = 1; i <= n; ++i) rank[sa[i]] = i;
	int k = 0;
	for (int i = 0; i < n; h[rank[i++]] = k)
	{
		if (k) --k;
		for (int j = sa[rank[i] - 1]; a[i + k] == a[j + k]; ++k);
	}
}

bool check(int x)
{
	int mx, mi;
	mi = mx = sa[1];
	for (int i = 2; i <= n; ++i)
	{
		if (h[i] < x)
		{
			mx = sa[i];
			mi = sa[i];
		}
		else 
		{
			mx = max(mx, sa[i]);
			mi = min(mi, sa[i]);
			if (mx - mi >= x) return 1;
		}
	}
	return 0;
}

int main()
{
	while (~scanf("%d", &n))
	{
		if (n == 0) break;
		m = 200;
		for (int i = 0; i < n; ++i) scanf("%d", &a[i]);
		if (n < 10) {puts("0"); continue;}
		for (int i = 0; i < n - 1; ++i) a[i] = a[i] - a[i + 1] + 90;
		a[n] = 0;
		BuildSA();
		int l = 0, r = n;
		while (l <= r)
		{
			int mid = (l + r) >> 1;
			if (check(mid)) l = mid + 1; else r = mid - 1;
		}
		printf("%d\n", r > 3 ? r + 1 : 0);
	}
	
	return 0;
}
