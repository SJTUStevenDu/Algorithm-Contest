#include <iostream>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <cmath>
#include <algorithm>
#include <fstream>

using namespace std;

const int MAXC = (1 << 21) + 10;
const int MAXN = 30;

int n, cc[MAXN], d[MAXN], cur, f[MAXC], tst, ans[MAXN];

bool dfs(int s, int x)
{
	
	int now = s;
	now -= d[x];
	
	for (int i = 2; i + x <= 20; ++i) if (!(now & d[i])) 
		if (now & d[i + x]) now -= d[i + x];
	if (~f[now]) return f[now];
	for (int i = 2; i <= 20; ++i) if (now & d[i])
		if (!dfs(now, i)) return f[now] = 1;
	return f[now] = 0;
}

int main()
{
	for (int i = 1; i <= 20; ++i) d[i] = (1 << (i - 1));
	memset(f, -1, sizeof(f));
	while(~scanf("%d", &n))
	{
		if (!n) break;
		printf("Test Case #%d\n", ++tst);
		memset(ans, 0, sizeof(ans));
		cur = 0;
		for (int i = 1; i <= n; ++i) scanf("%d", &cc[i]), cur += d[cc[i]];
		for (int i = 2; i <= 20; ++i) if (cur & d[i]) 
		{
			if (!dfs(cur, i)) ans[++ans[0]] = i;
		}
		if (ans[0] == 0) 
		{
			puts("There's no winning move.");
			f[cur] = 0;
		}
		else 
		{
			printf("The winning moves are:");
			for (int i = 1; i <= ans[0]; ++i) printf(" %d", ans[i]);
			putchar('\n');
			f[cur] = 1;
		}
		putchar('\n');
	}
	
	return 0;
}
