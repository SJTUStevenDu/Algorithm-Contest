#include <iostream>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <cmath>
#include <fstream>
#include <algorithm>

using namespace std;

const int MAXN = 1000000 + 10;

struct Node
{
	int pos, color;
} a[MAXN];

int vis[MAXN];
int n, k, tot, p, x, l = 1, now, ans = 0x7FFFFFFF;

bool cmp(Node A, Node B)
{
	return A.pos < B.pos;
}

int main()
{
	scanf("%d%d", &n, &k);
	for (int i = 1; i <= k; ++i)
	{
		scanf("%d", &p);
		while (p--) scanf("%d", &x), a[++tot].pos = x, a[tot].color = i;
	}
	sort(a + 1, a + 1 + n, cmp);
	for (int i = 1; i <= n; ++i)
	{
		if (!vis[a[i].color]) now++;
		vis[a[i].color]++;
		while (vis[a[l].color] > 1) vis[a[l].color]--, ++l;
		if (now == k) ans = min(ans, a[i].pos - a[l].pos);
	}
	printf("%d\n", ans);
	
	return 0;
}
