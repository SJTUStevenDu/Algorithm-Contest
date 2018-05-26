#include <iostream>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <algorithm>
#include <cmath>

using namespace std;

const int MAXN = 200000 + 10;

struct Node
{
	long long cnt;
	int minh;
} stk[MAXN];

int a[MAXN], ra[MAXN], rank[MAXN], wa[MAXN], wb[MAXN], wv[MAXN], sa[MAXN], h[MAXN];
int n, n1, k, Top;
long long ans, cur;

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
	while (scanf("%d", &k))
	{
		if (k == 0) break; getchar();
		char c;
		n = n1 = 0; ans = 0;
		for (c = getchar(); c != '\n'; c = getchar()) a[n++] = c;
		n1 = n; a[n++] = '@';
		for (c = getchar(); c != '\n'; c = getchar()) a[n++] = c;
		BuildSA(n, 200);
		Top = 0; cur = 0;
		for (int i = 2; i <= n; ++i)
		{
			long long cc = 0;
			if (h[i] < k) {Top = 0; cur = 0; continue;}
			while (Top && stk[Top].minh + k - 1 >= h[i])
			{
				cc += stk[Top].cnt;
				cur -= stk[Top].cnt * stk[Top].minh;
				--Top;
			}
			if (sa[i - 1] > n1) ++cc;
			stk[++Top].minh = h[i] - k + 1, stk[Top].cnt = cc;
			cur += stk[Top].cnt * stk[Top].minh;
			if (sa[i] < n1) ans += cur;
		}
		Top = 0; cur = 0;
		for (int i = 2; i <= n; ++i)
		{
			long long cc = 0;
			if (h[i] < k) {Top = 0; cur = 0; continue;}
			while (Top && stk[Top].minh + k - 1 >= h[i])
			{
				cc += stk[Top].cnt;
				cur -= stk[Top].cnt * stk[Top].minh;
				--Top;
			}
			if (sa[i - 1] < n1) ++cc;
			stk[++Top].minh = h[i] - k + 1, stk[Top].cnt = cc;
			cur += stk[Top].cnt * stk[Top].minh;
			if (sa[i] > n1) ans += cur;
		}
		printf("%lld\n", ans);
	}
	
	return 0;
}
