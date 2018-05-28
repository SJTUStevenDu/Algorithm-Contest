#include <iostream>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <algorithm>
#include <cmath>

using namespace std;

const int MAXN = 300000 + 10;

double len, ans;
char s[MAXN];
int n;

int main()
{
	scanf("%d", &n);
	scanf("%s", s);
	for (int i = 0; i < n; ++i)
	{
		if (s[i] == 'o') ans += 2 * len + 1, len++;
		if (s[i] == 'x') len = 0;
		if (s[i] == '?') ans += len + 0.5, len = (len + 1) / 2;
	}
	printf("%.4lf\n", ans);
	
	return 0;
}
