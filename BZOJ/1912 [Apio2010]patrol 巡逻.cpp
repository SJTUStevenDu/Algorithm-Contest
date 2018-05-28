#include <iostream>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <cmath>
#include <fstream>
#include <algorithm>

using namespace std;

const int MAXN = 100000 + 10;

struct Edge
{
	int next, to;
} g[MAXN * 2];
int gn, start[MAXN];

inline void AddEdge(int a, int b)
{
	gn++; g[gn].next = start[a]; start[a] = gn; g[gn].to = b;
}

int dp[MAXN][3][2], n, k, tmp[3][2];

void dfs(int p, int fa)
{
	dp[p][0][0] = dp[p][0][1] = 0;
	for (int i = start[p]; i; i = g[i].next)
	{
		int v = g[i].to;
		if (v == fa) continue;
		dfs(v, p);
		memcpy(tmp, dp[p], sizeof(tmp));
		for (int j = k; j >= 0; --j)
			for (int l = j; l >= 0; --l)
			{
				dp[p][j][0] = max(dp[p][j][0], dp[v][l][0] + tmp[j - l][0]);
				if (j - l) dp[p][j][0] = max(dp[p][j][0], dp[v][l][1] + tmp[j - l - 1][1] + 1);
				dp[p][j][1] = max(dp[p][j][1], dp[v][l][1] + tmp[j - l][0] + 1);
				dp[p][j][1] = max(dp[p][j][1], dp[v][l][0] + tmp[j - l][1]);
			}
	}
}

int main()
{
	scanf("%d%d", &n, &k);
	for (int a, b, i = 1; i < n; ++i)
	{
		scanf("%d%d", &a, &b);
		AddEdge(a, b); AddEdge(b, a);
	}
	dfs(1, 0);
	printf("%d\n", 2 * (n - 1) - max(dp[1][1][0], max(dp[1][k][0], dp[1][k - 1][1])) + k);
	
	return 0;
}
