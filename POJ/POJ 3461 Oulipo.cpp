#include <iostream>
#include <cstdio>
#include <cstring>
#include <cstdlib>

using namespace std;

const int MAXN = 1000000 + 10;
const int MAXM = 10000 + 10;

char S[MAXN], T[MAXM];
int n, m, tst, ans, p[MAXN];

int main()
{
	scanf("%d", &tst);
	while (tst--)
	{
		scanf("%s", T + 1);
		scanf("%s", S + 1);
		m = strlen(T + 1); n = strlen(S + 1); ans = 0;
		for (int i = 2, j = 0; i <= m; ++i)
		{
			while (j && T[i] != T[j + 1]) j = p[j];
			j += (T[i] == T[j + 1]);
			p[i] = j;
		}
		for (int i = 1, j = 0; i <= n; ++i)
		{
			while (j && S[i] != T[j + 1]) j = p[j];
			j += (S[i] == T[j + 1]);
			if (j == m) ++ans;
		}
		printf("%d\n", ans);
	}
	
	return 0;
}
