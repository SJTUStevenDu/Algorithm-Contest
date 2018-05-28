#include <iostream>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <cmath>
#include <algorithm>
#include <fstream>

using namespace std;

const int MAXN = 2000 + 10;

int a[MAXN][MAXN], n, m, s[MAXN][MAXN];
int ans1, ans2, f[MAXN][MAXN], l[MAXN], r[MAXN], stk[MAXN], Top;

void DP(int v0)
{
	for (int i = 1; i <= n; ++i)
		for (int j = 1; j <= m; ++j)
		{
			if (a[i][j] != v0) f[i][j] = 0;
			else f[i][j] = min(f[i - 1][j], min(f[i - 1][j - 1], f[i][j - 1])) + 1;
		}
	for (int i = 1; i <= n; ++i)
		for (int j = 1; j <= m; ++j) ans1 = max(ans1, f[i][j]);
	for (int i = 1; i <= n; ++i)	
		for (int j = 1; j <= m; ++j) 
		{
			if (a[i][j] != v0) s[i][j] = 0;
			else s[i][j] = s[i - 1][j] + 1;
		}
	for (int i = 1; i <= n; ++i)
	{
		memset(l, 0, sizeof(l));
		memset(r, 0, sizeof(r));
		Top = 0;
		for (int j = 1; j <= m; ++j)
		{
			while (Top && s[i][j] < s[i][stk[Top]]) 
			{
				r[stk[Top]] = j - stk[Top];
				Top--;
			}
			if (a[i][j] == v0) stk[++Top] = j;
		}
		while (Top)
		{
			r[stk[Top]] = m - stk[Top] + 1;
			Top--;
		}
		for (int j = m; j; --j)
		{
			while (Top && s[i][j] < s[i][stk[Top]]) 
			{
				l[stk[Top]] = stk[Top] - j;
				Top--;
			}
			if (a[i][j] == v0) stk[++Top] = j;
		}
		while (Top)
		{
			l[stk[Top]] = stk[Top];
			Top--;
		}
		for (int j = 1; j <= m; ++j) if (a[i][j] == v0) ans2 = max(ans2, (l[j] + r[j] - 1) * s[i][j]);	
		
	}
}

int main()
{
	scanf("%d%d", &n, &m);
	for (int i = 1; i <= n; ++i) 
		for (int j = 1; j <= m; ++j) 
		{
			scanf("%d", &a[i][j]);
			if ((i + j) & 1) a[i][j] ^= 1;
		}
	DP(0);
	DP(1);
	printf("%d\n%d\n", ans1 * ans1, ans2);
	
	return 0;
}
