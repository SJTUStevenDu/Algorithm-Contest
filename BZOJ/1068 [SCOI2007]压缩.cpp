#include <iostream>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <cmath>
#include <fstream>
#include <algorithm>

using namespace std;

const int MAXN = 100 + 10;

int f[MAXN][MAXN][2], n;
char s[MAXN];

bool check(int p, int len, int k)
{
	if (len % k) return false;
	for (int i = 0; i < len; ++i) if (s[p + i] != s[p + i % k]) return false;
	return true;
}

int dfs(int l, int r, int t)
{
	if (~f[l][r][t]) return f[l][r][t];
	int &res = f[l][r][t];
	int len = r - l + 1;
	res = len;
	if (len == 1) return res;
	if (t) for (int i = l; i < r; ++i) res = min(res, dfs(l, i, 1) + dfs(i + 1, r, 1) + 1);
	for (int i = l; i < r; ++i) res = min(res, dfs(l, i, t) + r - i);
	if (len % 2 == 0 && check(l, len, len / 2)) res = min(res, dfs(l, l + len / 2 - 1, 0) + 1);
	return res;
}

int main()
{
	scanf("%s", s + 1);
	n = strlen(s + 1);
	memset(f, -1, sizeof(f));
	printf("%d\n", dfs(1, n, 1));
	
	return 0;
}
