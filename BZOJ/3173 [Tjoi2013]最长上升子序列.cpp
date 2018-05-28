#include <iostream>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <cmath>
#include <fstream>
#include <algorithm>

using namespace std;

const int MAXN = 100000 + 10;
const int INF = 0x7FFFFFFF >> 2;

int s[MAXN], stk[MAXN], Top, n, ans, c[MAXN], a[MAXN], f[MAXN];

inline int lowbit(int x) {return x & (-x);}

inline void Add(int x, int v)
{
	for (; x <= n; x += lowbit(x)) s[x] += v;
}

inline int Query(int x)
{
	int ret = 0;
	for (; x; x -= lowbit(x)) ret += s[x];
	return ret;
}

inline int get_kth(int k)
{
	int cnt = 0, ret = 0;
	for (int i = 20; i >= 0; --i)
	{
		ret += (1 << i);
		if (ret > n || cnt + s[ret] >= k) ret -= (1 << i);
		else cnt += s[ret];
	}
	return ret + 1;
}

int main()
{
	scanf("%d", &n);
	for (int i = 1; i <= n; ++i) scanf("%d", &a[i]);
	for (int i = 1; i <= n; ++i) 
	{
		++s[i];
		if (i + lowbit(i) > n) continue;
		s[i + lowbit(i)] += s[i];
	}
	for (int i = n; i; --i)
	{
		int j = get_kth(a[i] + 1);
		c[j] = i;
		Add(j, -1);
	}
	stk[Top = 1] = INF;
	for (int i = 1; i <= n; ++i)
	{
		int j = lower_bound(stk + 1, stk + Top, c[i]) - stk;
		f[c[i]] = j; stk[j] = c[i]; if (j == Top) ++Top, stk[Top] = INF;
	}
	for (int i = 1; i <= n; ++i) 
	{
		ans = max(ans, f[i]);
		printf("%d\n", ans);
	}
	
	return 0;
}
