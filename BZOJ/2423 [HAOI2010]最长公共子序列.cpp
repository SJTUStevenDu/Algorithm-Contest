#include <iostream>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <algorithm>

using namespace std;

const int MAXN = 5000 + 10;
const int MOD = 100000000;

int f[2][MAXN], n, m, g[2][MAXN], now, pre;
char s1[MAXN], s2[MAXN];

int main()
{
	scanf("%s", s1 + 1);
	scanf("%s", s2 + 1);
	n = strlen(s1 + 1) - 1; m = strlen(s2 + 1) - 1;
	now = 0; pre = 1;
	for (int i = 0; i <= m; ++i) g[now][i] = 1;
	for (int i = 1; i <= n; ++i)
	{
		now = now ^ 1; pre = pre ^ 1;
		memset(f[now], 0, sizeof(f[now]));
		g[now][0] = 1;
		for (int j = 1; j <= m; ++j) 
		{
			f[now][j] = max(f[pre][j], f[now][j - 1]);
			if (s1[i] == s2[j]) f[now][j] = max(f[now][j], f[pre][j - 1] + 1);
			if (s1[i] == s2[j])
			{
				g[now][j] = g[pre][j - 1];
				if (f[now][j] == f[pre][j]) g[now][j] = (g[now][j] + g[pre][j]) % MOD;
				if (f[now][j] == f[now][j - 1]) g[now][j] = (g[now][j] + g[now][j - 1]) % MOD;
			}
			else 
			{
				g[now][j] = 0;
				if (f[now][j] == f[pre][j]) g[now][j] = (g[now][j] + g[pre][j]) %  MOD;
				if (f[now][j] == f[now][j - 1]) g[now][j] = (g[now][j] + g[now][j - 1]) % MOD;
				if (f[now][j] == f[pre][j - 1]) g[now][j] = (g[now][j] + MOD - g[pre][j - 1]) % MOD;
			}
		}
	}
	printf("%d\n", f[now][m]);
	printf("%d\n", g[now][m]);
    
    return 0;
}
