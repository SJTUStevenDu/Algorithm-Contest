#include <iostream>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <cmath>
#include <fstream>
#include <algorithm>

using namespace std;

const int MAXN = 200000 + 10;
const int MAXM = 1000 + 10;
const int INF = 0x7FFFFFFF >> 2;

struct Node
{
	int x, y, w;
} a[MAXN];

bool cmp(Node A, Node B)
{
	return A.x < B.x || (A.x == B.x && A.y < B.y);
}

int n, m; 
int last[MAXM], dp[MAXN];

inline int Getdist(int x1, int y1, int x2, int y2)
{
	return (x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2);
}

int main()
{
	scanf("%d%d", &n, &m);
	for (int i = 1; i <= n; ++i) scanf("%d%d%d", &a[i].x, &a[i].y, &a[i].w);
	sort(a + 1, a + 1 + n, cmp);
	dp[1] = a[1].w; last[1] = 1;
	for (int i = 2; i <= n; ++i)
	{
		dp[i] = -INF;
		for (int j = 1; j <= a[i].y; ++j)
		{
			if (!last[j]) continue;
			dp[i] = max(dp[i], dp[last[j]] + a[i].w - Getdist(a[i].x, a[i].y, a[last[j]].x, a[last[j]].y));
		}
		last[a[i].y] = i;
	}
	printf("%d\n", dp[n]);
	return 0;
}
