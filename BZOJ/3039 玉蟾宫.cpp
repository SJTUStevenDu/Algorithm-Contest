#include <iostream>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <algorithm>
#include <cmath>

using namespace std;

const int MAXN = 1000 + 10;

int n, m, d[MAXN][MAXN], stk[MAXN], ans, Top, t[MAXN];
char s[20];

int main()
{
	scanf("%d%d", &n, &m);
	for (int i = 1; i <= n; ++i)
		for (int j = 1; j <= m; ++j)
		{
			scanf("%s", s);
			if (s[0] == 'F') d[i][j] = d[i - 1][j] + 1;
		}
	for (int w, h, i = 1; i <= n; ++i)
	{
		stk[Top = 0] = -1;
		for (int j = 1; j <= m; ++j)
		{
			w = 0, h = d[i][j];
			while (stk[Top] > h) 
			{
				w += t[Top];
				if (w * stk[Top] > ans) ans = w * stk[Top];
				Top--;
			}
			stk[++Top] = h;
			t[Top] = w + 1;
		}
		w = 0;
		while (Top) 
		{
			w += t[Top];
			if (w * stk[Top] > ans) ans = w * stk[Top];
			Top--;
		}
	}
	printf("%d\n", 3 * ans);
	
	return 0;
}
