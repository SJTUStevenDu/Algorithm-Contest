#include <iostream>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <cmath>
#include <algorithm>
#include <fstream>

using namespace std;

const int MAXN = 10000 + 10;
const int INF = 0x7FFFFFFF >> 2;

int stk[MAXN], Top, a[MAXN], f[MAXN];
int n, Q, L, last;

int main()
{
	scanf("%d", &n);
	for (int i = 1; i <= n; ++i) scanf("%d", &a[i]);
	stk[Top] = INF;
	for (int i = n; i; --i)
	{
		if (stk[Top] > a[i]) stk[++Top] = a[i], f[i] = Top;
		else 
		{
			int l = 1, r = Top;
			while (l <= r)
			{
				int mid = (l + r) / 2;
				if (stk[mid] > a[i]) l = mid + 1;
				else r = mid - 1;
			}
			stk[l] = a[i];
			f[i] = l;
		}
	}
	scanf("%d", &Q);
	while (Q--)
	{
		scanf("%d", &L);
		last = -INF;
		for (int i = 1; i <= n; ++i) if (L && f[i] >= L && a[i] > last)
		{
			if (L == 1) printf("%d\n", a[i]), --L;
			else printf("%d ",a[i]), --L, last = a[i];
		}
		if (L) puts("Impossible");
	}
	
	return 0;
}
