#include <iostream>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <cmath>
#include <fstream>
#include <algorithm>

using namespace std;

const int MAXN = 20;
const int MAXC = 60;
const int MAXM = (1 << 15) + 20;
const int MOD = 1000003;

int n, m, a[MAXN][MAXC], cnt[MAXM], b[MAXC][MAXC], dp[MAXC][MAXM], T, len, ans;
char s[MAXC];

int main()
{
	scanf("%d", &T);
	for (int i = 1; i <= (1 << 15) + 1; ++i) cnt[i] = cnt[i >> 1] + (i & 1);
	while (T--)
	{
		memset(b, 0, sizeof(b));
		memset(dp, 0, sizeof(dp));
		scanf("%d%d", &n, &m);
		for (int i = 1; i <= n; ++i) 
		{
			scanf("%s", s + 1);
			len = strlen(s + 1);
			for (int j = 1; j <= len; ++j) a[i][j] = (s[j] == '?') ? 27 : s[j] - 'a' + 1;
		}
		for (int i = 1; i <= len; ++i)
			for (int j = 1; j <= 26; ++j)
				for (int k = 1; k <= n; ++k)
					if (a[k][i] == 27 || a[k][i] == j) b[i][j] |= (1 << (k - 1));
		dp[0][(1 << n) - 1] = 1;
		for (int i = 0; i < len; ++i)
			for (int j = 0; j < (1 << n); ++j)
			{
				if (!dp[i][j]) continue;
				for (int k = 1; k <= 26; ++k) dp[i + 1][j & b[i + 1][k]] = (dp[i + 1][j & b[i + 1][k]] + dp[i][j]) % MOD;
			}
		ans = 0;
		for (int i = 0; i < (1 << n); ++i) if (cnt[i] == m) ans = (ans + dp[len][i]) % MOD;
		printf("%d\n", ans);
	}
	
	return 0;
}
