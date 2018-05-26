#include <iostream>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <algorithm>
#include <cmath>

using namespace std;

const int MAXN = 200000 + 10;

int a[MAXN], wa[MAXN], wb[MAXN], wv[MAXN], sa[MAXN], rank[MAXN], ra[MAXN], h[MAXN];
int n1, n, ans;

void BuildSA(int n, int m)
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

int main()
{
	char c = 0;
	for (c = getchar(); c != '\n'; c = getchar()) a[n++] = c - 'a' + 1;
	n1 = n; a[n++] = 27;
	for (c = getchar(); c != '\n'; c = getchar()) a[n++] = c - 'a' + 1;
	BuildSA(n, 30);
	for (int i = 2; i <= n; ++i) 
		if ((sa[i - 1] > n1 && sa[i] < n1) || (sa[i - 1] < n1 && sa[i] > n1)) ans = max(ans, h[i]);
	printf("%d\n", ans);
	
	return 0;
}
