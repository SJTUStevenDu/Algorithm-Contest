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
} g[MAXN];
int gn, start[MAXN];

inline void Add(int a, int b)
{
	gn++; g[gn].next = start[a]; start[a] = gn; g[gn].to = b;
}

int n, dp[MAXN], cnt[MAXN];

int main()
{
	scanf("%d", &n);
	for (int l, r, i = 1; i <= n; ++i)
	{
		scanf("%d%d", &l, &r);
		++l; r = n - r;
		if (l > r) continue;
		Add(l, r);
	}
	for (int i = 1; i <= n; ++i) 
	{
		dp[i] = max(dp[i], dp[i - 1]);
		for (int j = start[i]; j; j = g[j].next) cnt[g[j].to]++;
		for (int j = start[i]; j; j = g[j].next) dp[g[j].to] = max(dp[g[j].to], dp[i - 1] + min(g[j].to - i + 1, cnt[g[j].to]));
		for (int j = start[i]; j; j = g[j].next) cnt[g[j].to]--;
	}
	printf("%d\n", n - dp[n]);
	
	return 0;
}
