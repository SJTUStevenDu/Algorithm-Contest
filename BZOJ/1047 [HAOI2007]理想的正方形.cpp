#include <iostream>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <cmath>
#include <algorithm>
#include <fstream>

using namespace std;

const int MAXN = 1000 + 10;
const int INF = 1000000001;

int a[MAXN][MAXN], n, m, l;
int q[MAXN], head, tail, ans = INF;
int lmax[MAXN][MAXN], lmin[MAXN][MAXN], hmax[MAXN][MAXN], hmin[MAXN][MAXN];

int main()
{
	scanf("%d%d%d", &n, &m, &l);
	for (int i = 1; i <= n; ++i) 
		for (int j = 1; j <= m; ++j) scanf("%d", &a[i][j]);
	for (int i = 1; i <= n; ++i)
	{
		head = 1; tail = 0;
		for (int j = 1; j <= m; ++j) 
		{
			while (head <= tail && q[head] + l <= j) ++head;
			while (head <= tail && a[i][q[tail]] <= a[i][j]) --tail;
			q[++tail] = j;
			if (j >= l) lmax[i][j - l + 1] = a[i][q[head]];
		}
		head = 1; tail = 0;
		for (int j = 1; j <= m; ++j) 
		{
			while (head <= tail && q[head] + l <= j) ++head;
			while (head <= tail && a[i][q[tail]] >= a[i][j]) --tail;
			q[++tail] = j;
			if (j >= l) lmin[i][j - l + 1] = a[i][q[head]];
		}
	}
	for (int i = 1; i <= m; ++i)
	{
		head = 1; tail = 0;
		for (int j = 1; j <= n; ++j) 
		{
			while (head <= tail && q[head] + l <= j) ++head;
			while (head <= tail && lmax[q[tail]][i] <= lmax[j][i]) --tail;
			q[++tail] = j;
			if (j >= l) hmax[j - l + 1][i] = lmax[q[head]][i];
		}
		head = 1; tail = 0;
		for (int j = 1; j <= n; ++j) 
		{
			while (head <= tail && q[head] + l <= j) ++head;
			while (head <= tail && lmin[q[tail]][i] >= lmin[j][i]) --tail;
			q[++tail] = j;
			if (j >= l) hmin[j - l + 1][i] = lmin[q[head]][i];
		}
	}
	for (int i = 1; i <= n - l + 1; ++i) 
		for (int j = 1; j <= m - l + 1; ++j) ans = min(ans, hmax[i][j] - hmin[i][j]);
	printf("%d\n", ans);
	
	return 0;
}
