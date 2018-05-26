#include <iostream>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <algorithm>
#include <cmath>

using namespace std;

const int MAXN = 400000 + 10;

char s[MAXN];
int n, ans[MAXN], p[MAXN];

int main()
{
	while (~scanf("%s", s + 1))
	{
		n = strlen(s + 1);
		for (int i = 2, j = 0; i <= n; ++i) 
		{
			while (j && s[i] != s[j + 1]) j = p[j];
			j += (s[i] == s[j + 1]);
			p[i] = j;
		}
		ans[0] = 0;
		for (int i = n; i; i = p[i]) ans[++ans[0]] = i;
		for (int i = ans[0]; i > 1; --i) printf("%d ", ans[i]);
		printf("%d\n", ans[1]);
	}
	
	return 0;
}
