#include <iostream>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <cmath>
#include <algorithm>
#include <fstream>

using namespace std;

const int MAXN = 1000 + 50;

int f[MAXN][MAXN];
int n, p, T, ans, fac[15];
char S[15];

int calc(int s, int m)
{
	if (s == 0) return m == 0;
	if (~f[s][m]) return f[s][m];
	int ret = 0;
	for (int i = 1; i <= n; ++i)
		if (s & (1 << (i - 1)))
			ret += calc(s ^ (1 << (i - 1)), (m * 10 + S[i] - '0') % p);
	return f[s][m] = ret; 
}

int main()
{
	scanf("%d", &T);
	fac[0] = 1;
	for (int i = 1; i <= 10; ++i) fac[i] = fac[i - 1] * i;
	while (T--)
	{
		memset(f, -1, sizeof(f));
		scanf("%s", S + 1);
		scanf("%d", &p);
		n = strlen(S + 1);
		ans = calc((1 << n) - 1, 0);
		sort(S + 1, S + 1 + n);
		for (int i = 1; i <= n;)
		{
			int cnt = 1;
			while (S[i] == S[i + 1] && i <= n) ++cnt, ++i;
			ans /= fac[cnt];
			++i;
		}
		printf("%d\n", ans);
	}
	
	return 0;
}
