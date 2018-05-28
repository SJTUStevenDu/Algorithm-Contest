#include <iostream>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <cmath>
#include <algorithm>
#include <fstream>

using namespace std;

const int MAXN = 100 + 10;

int dp[MAXN][MAXN];
char S[MAXN];

bool check(int p, int len, int k)
{
	if (len % k) return false;
	for (int i = 0; i < len; ++i) if (S[p + i] != S[p + i % k]) return false;
	return true;
}

int GetNum(int x)
{
	int num = 0;
	while (x)
	{
		++num;
		x /= 10;
	}
	return num;
}

int dfs(int l, int r)
{
	if (dp[l][r]) return dp[l][r];
	int len = r - l + 1, &res = dp[l][r];
	res = len;
	for (int i = l; i < r; ++i) res = min(res, dfs(l, i) + dfs(i + 1, r));
	for (int i = 1; i < len; ++i) if (check(l, len, i)) res = min(res, dfs(l, l + i - 1) + 2 + GetNum(len / i));
	return res;
}

int main()
{
	scanf("%s", S + 1);
	printf("%d\n", dfs(1, strlen(S + 1)));
	
	return 0;
}
