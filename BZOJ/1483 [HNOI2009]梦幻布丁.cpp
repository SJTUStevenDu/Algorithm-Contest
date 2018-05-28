#include <iostream>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <cmath>
#include <fstream>
#include <algorithm>

using namespace std;

const int MAXN = 100000 + 10;
const int MAXC = 1000000 + 10;

int nxt[MAXN], c[MAXN], n, Q, h[MAXC], idx[MAXC], sz[MAXC];
int opr, x, y, ans;

int main()
{
	scanf("%d%d", &n, &Q);
	for (int i = 1; i <= n; ++i) scanf("%d", &c[i]);
	for (int i = 1; i <= 1000000; ++i) idx[i] = i;
	for (int i = 1; i <= n; ++i)
	{
		if (c[i] != c[i - 1]) ++ans;
		sz[c[i]]++; nxt[i] = h[c[i]]; h[c[i]] = i;
	}
	while (Q--)
	{
		scanf("%d", &opr);
		if (opr == 2) printf("%d\n", ans);
		else 
		{
			int last = 0;
			scanf("%d%d", &x, &y);
			if (x == y) continue;
			if (sz[idx[x]] > sz[idx[y]]) swap(idx[x], idx[y]);
			x = idx[x]; y = idx[y];
			if (sz[x] == 0) continue;
			for (int i = h[x]; i; i = nxt[i])
			{
				if (c[i] != c[i - 1]) --ans;
				if (i < n && c[i] != c[i + 1]) --ans;
			}
			for (int i = h[x]; i; i = nxt[i]) c[i] = y;
			for (int i = h[x]; i; last = i, i = nxt[i])
			{
				if (c[i] != c[i - 1]) ++ans;
				if (i < n && c[i] != c[i + 1]) ++ans;
			}
			sz[y] += sz[x]; sz[x] = 0; nxt[last] = h[y]; h[y] = h[x]; h[x] = 0;
		}
	}
	
	return 0;
}
