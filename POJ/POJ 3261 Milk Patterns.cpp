#include <iostream>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <algorithm>
#include <cmath>

using namespace std;

const int MAXN = 20000 + 10;
const int MAXM = 1000000 + 10;

int a[MAXN], ra[MAXM], sa[MAXN], rank[MAXN], wa[MAXN], wb[MAXN], wv[MAXN], h[MAXN];
int n, m, s;

void BuildSA()
{
	a[n++] = 0;
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
		x[sa[0]] = 0; p = 1;
		for (int i = 1; i < n; ++i)
			if (y[sa[i]] == y[sa[i - 1]] && y[sa[i] + j] == y[sa[i - 1] + j]) x[sa[i]] = p - 1; else x[sa[i]] = p++;
		m = p;
	}
	--n;
	for (int i = 1; i <= n; ++i) rank[sa[i]] = i;
	int k = 0;
	for (int i = 0; i < n; h[rank[i++]] = k)
	{
		if (k) k--;
		for (int j = sa[rank[i] - 1]; a[j + k] == a[i + k]; ++k);
	}
}

bool check(int x)
{
	int cnt = 0;
	for (int i = 2; i <= n; ++i) 
		if (h[i] < x) cnt = 1;
		else 
		{
			++cnt;
			if (cnt >= s) return true;
		}
	return false;
}

int main()
{
	scanf("%d%d", &n, &s);
	for (int i = 0; i < n; ++i) scanf("%d", &a[i]);
	m = 1000001;
	BuildSA();
	int l = 0, r = n;
	while (l <= r)
	{
		int mid = (l + r) >> 1;
		if (check(mid)) l = mid + 1; else r = mid - 1;
	}
	printf("%d\n", r);
	
	return 0;
}
