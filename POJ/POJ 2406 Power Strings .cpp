#include <iostream>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <algorithm>
#include <cmath>

//倍增被卡了，要用DC3写才能过= = 

using namespace std;

const int MAXN = 1000000 + 10;
const int INF = 0x7FFFFFFF >> 2;

char s[MAXN];
int a[MAXN], wa[MAXN], ra[MAXN], wb[MAXN], wv[MAXN], rank[MAXN], sa[MAXN], h[MAXN], rm[MAXN];
int n;

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
		if (k) k--;
		for (int j = sa[rank[i] - 1]; a[j + k] == a[i + k]; ++k);
	}
}

int Solve()
{
	int minn = INF;
	for (int i = rank[0]; i > 1; --i) rm[i] = minn, minn = min(minn, h[i]);
	minn = INF;
	for (int i = rank[0] + 1; i <= n; ++i) minn = min(minn, h[i]), rm[i] = minn;
	for (int ans = n; ans; --ans)
	{
		if (ans == 1) return ans;
		if (n % ans != 0) continue;
		int tmp = n / ans;
		if (rm[rank[tmp]] == n - tmp) return ans;
	}
}

int main()
{
	for (;;)
	{
		scanf("%s", s);
		n = 0;
		for (int i = 0; s[i]; ++i) a[n++] = s[i];
		if (n == 1 && s[0] == '.') break;
		BuildSA(n, 200);
		printf("%d\n", Solve());
	}
	
	return 0;
}
