#include <iostream>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <algorithm>
#include <cmath>

using namespace std;

const int MAXH = 1000000;
const int MAXN = 1000000 + 10;
const int MAXM = 180000 * 2;
const int MOD = 1000000007;

struct Edge
{
	int next, to;
} g[MAXM];
int gn, start[MAXN];
bool mk[MAXM];

inline void AddEdge(int a, int b)
{
	gn++; g[gn].next = start[a]; start[a] = gn; g[gn].to = b;
}

inline long long gcd(long long n, long long m)
{
	long long tmp;
	while (m)
	{
		tmp = n % m;
		n = m; 
		m = tmp;
	}
	return n;
}

inline int getint()
{
	char c; int ret = 0;
	for (c = getchar(); c > '9' || c < '0'; c = getchar());
	for (; c >= '0' && c <= '9'; c = getchar()) ret = ret * 10 + c - '0';
	return ret;
}

int n, cnt[MAXN], a[MAXN], pw2[MAXN], e[500][3], bs, cs[MAXN];
long long ans, ret, dp[MAXN][2];
bool vis[MAXN];

void dfs(int p, int fa)
{
	vis[p] = 1;
	for (int i = start[p]; i; i = g[i].next) if (!mk[i])
	{
		int v = g[i].to;
		if (!cnt[v]) continue;
		if (!vis[v]) dfs(v, p);
		else if (v != fa)
		{
			e[++bs][0] = i; e[bs][1] = p; e[bs][2] = v;
			mk[i ^ 1] = mk[i] = 1;
		}
	}
}

//dp[i][1] -> i contain

void Tree_Dp(int p, int fa)
{
	dp[p][0] = 1; dp[p][1] = pw2[cnt[p]] - 1;
	if (cs[p] == 1) dp[p][0] = 0;
	if (cs[p] == 2) dp[p][1] = 0;
	for (int i = start[p]; i; i = g[i].next) if (!mk[i])
	{
		int v = g[i].to;
		if (!cnt[v] || v == fa) continue;
		Tree_Dp(v, p);
		dp[p][0] = dp[p][0] * (dp[v][0] + dp[v][1]) % MOD;
		dp[p][1] = dp[p][1] * dp[v][0] % MOD;
	}
}

void dfs2(int dep, int st)
{
	if (dep > bs)
	{
		Tree_Dp(st, 0);
		ret = (ret + dp[st][0]) % MOD;
		ret = (ret + dp[st][1]) % MOD;
		return;
	}
	int x = e[dep][1], y = e[dep][2];
	int nx = cs[x], ny = cs[y];
	//cs[x] = 1 -> contain
	if (nx != 2 && ny != 1)
	{
		cs[x] = 1; cs[y] = 2;
		dfs2(dep + 1, st);
		cs[x] = nx; cs[y] = ny;
	}
	if (nx != 1)
	{
		cs[x] = 2;
		dfs2(dep + 1, st);
		cs[x] = nx; 
	}
}

void solve(int x)
{
	ret = 0;
	bs = 0;
	dfs(x, 0);
	dfs2(1, x);
	for (int i = 1; i <= bs; ++i) mk[e[i][0]] = mk[e[i][0] ^ 1] = 0;
}

int main()
{
	gn = 1;
	for (long long i = 2; i * 2 <= MAXH; ++i)
		for (long long j = 1; i * j * 2 <= MAXH && j < i; ++j) 
			if ((i & 1) != (j & 1) && gcd(i, j) == 1LL && i * i - j * j <= MAXH) 
			{
				int aa = i * i - j * j; int bb = 2 * i * j;
				AddEdge(aa, bb); AddEdge(bb, aa);
			}
	n = getint();
	for (int i = 1; i <= n; ++i) 
	{
		int x = getint();
		cnt[x]++;
	}
	pw2[0] = 1;
	for (int i = 1; i <= n; ++i) pw2[i] = pw2[i - 1] * 2 % MOD;
	ans = 1;
	for (int i = 1; i <= MAXH; ++i) if (cnt[i] && !vis[i]) 
	{
		solve(i);
		ans = ans * ret % MOD;
	}
	cout << (ans - 1 + MOD) % MOD << endl;
	
	return 0;
}
