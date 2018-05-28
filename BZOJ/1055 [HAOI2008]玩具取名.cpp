#include <iostream>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <cmath>
#include <algorithm>
#include <fstream>

using namespace std;

const int MAXN = 200 + 10;

char s[MAXN];
int ss[5][20][5];
int n, a[4];
bool f[MAXN][MAXN][10], v[MAXN][MAXN][10], flag;

int trans(char x)
{
	if (x == 'W') return 1;
	if (x == 'I') return 2;
	if (x == 'N') return 3;
	if (x == 'G') return 4;
}

bool dp(int l, int r, int x)
{
	if (v[l][r][x]) return f[l][r][x];
	v[l][r][x] = 1;
	if (l == r) 
	{
		if (trans(s[l]) == x) return f[l][r][x] = 1;
		else return f[l][r][x] = 0;
	}
	for (int i = l; i < r; ++i)
		for (int j = 1; j <= a[x]; ++j)
			if (dp(l, i, ss[x][j][1]) && dp(i + 1, r, ss[x][j][2])) return f[l][r][x] = 1;
	return f[l][r][0] = 0;
}

int main()
{
	scanf("%d%d%d%d", &a[1], &a[2], &a[3], &a[4]);
	for (int z = 1; z <= 4; ++z)
	{
		for (int j = 1; j <= a[z]; ++j)
		{
			scanf("%s", s + 1);
			for (int i = 1; i <= strlen(s + 1); ++i) ss[z][j][i] = trans(s[i]);
		}
	}
	scanf("%s", s + 1);
	n = strlen(s + 1);
	if (dp(1, n, 1)) putchar('W'), flag = true;
	if (dp(1, n, 2)) putchar('I'), flag = true;
	if (dp(1, n, 3)) putchar('N'), flag = true;
	if (dp(1, n, 4)) putchar('G'), flag = true;
	if (!flag) puts("The name is wrong!");
	else putchar('\n');
	return 0;
}
