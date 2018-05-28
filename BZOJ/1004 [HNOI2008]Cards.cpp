#include <iostream>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <cmath>
#include <algorithm>
#include <fstream>

using namespace std;

const int MAXN = 100 + 10;

int sr, sg, sb, m, p, n, ans;
int a[MAXN][MAXN], f[MAXN][MAXN][MAXN];
int d[MAXN], tot;
bool vis[MAXN];

inline void Add(int &x, int b) {x = (x + b) % p;}

int dp(int x)
{
	memset(f, 0, sizeof(f));
	memset(d, 0, sizeof(d));
	memset(vis, 0, sizeof(vis));
	tot = 0;
	for (int i = 1; i <= n; ++i) if (!vis[i]) 
	{
		vis[i] = 1;
		d[++tot] = 1;
		for (int p = a[x][i]; !vis[p]; p = a[x][p]) vis[p] = 1, d[tot]++;
	}
	f[0][0][0] = 1;
	for (int p = 1; p <= tot; ++p)
		for (int i = sr; i >= 0; --i)
			for (int j = sb; j >= 0; --j) 
				for(int k = sg; k >= 0; --k) 
				{
					if (i >= d[p]) Add(f[i][j][k], f[i - d[p]][j][k]);
					if (j >= d[p]) Add(f[i][j][k], f[i][j - d[p]][k]);
					if (k >= d[p]) Add(f[i][j][k], f[i][j][k - d[p]]);
				}
	return f[sr][sb][sg];
}

int QuickMul(int a, int b, int c)
{
	int res = 1;
	while (b)
	{
		if (b & 1) res = res * a % c;
		b >>= 1;
		a = a * a % c;
	}
	return res;
}

int main()
{
	scanf("%d%d%d", &sr, &sb, &sg);
	scanf("%d%d", &m, &p);
	n = sr + sb + sg;
	for (int i = 1; i <= m; ++i) 
		for(int j = 1; j <= n; ++j) scanf("%d", &a[i][j]);
	++m;
	for (int i = 1; i <= n; ++i) a[m][i] = i;
	for (int i = 1; i <= m; ++i) ans = (ans + dp(i)) % p;
	ans = ans * QuickMul(m, p - 2, p);
	printf("%d\n", ans % p);
	
	return 0;
}
