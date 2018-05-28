#include <iostream>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <cmath>
#include <algorithm>
#include <fstream>
#include <vector> 

using namespace std;

const int MAXN = 1000000 + 10;

struct Edge
{
	int next, to;
	bool vv;
} g[MAXN * 2];
int gn = 1, start[MAXN];

inline void AddEdge(int a, int b)
{
	gn++; g[gn].next = start[a]; start[a] = gn; g[gn].to = b;
}

int n, stk[MAXN], Top, tot, cnt, cirr[MAXN];
long long dp[MAXN][2], f[MAXN][2], ans[MAXN], w[MAXN], Ans;
bool vis[MAXN];
vector <int> cir[MAXN];

void dfs1(int p)
{
	vis[p] = 1;
	stk[++Top] = p;
	for (int i = start[p]; i; i = g[i].next) if (!g[i].vv)
	{
		int v = g[i].to;
		g[i].vv = g[i ^ 1].vv = 1;
		if (vis[v])
		{
			int ss = Top;
			while (stk[ss] != v)
			{
				cir[tot].push_back(stk[ss]);
				ss--;
			}
			cir[tot].push_back(v);
			continue;
		}
		dfs1(v);
	}
	--Top;
}

void dfs2(int p)
{
	dp[p][0] = 0;
	dp[p][1] = w[p];
	vis[p] = 1;
	for (int i = start[p]; i; i = g[i].next)
	{
		int v = g[i].to;
		if (vis[v]) continue;
		dfs2(v);
		dp[p][0] += max(dp[v][0], dp[v][1]);
		dp[p][1] += dp[v][0]; 
	}
}

vector <int> :: iterator it;

void Work(int x)
{
	memset(vis, 0, sizeof(vis));
	cnt = 0;
	for (it = cir[x].begin(); it != cir[x].end(); ++it) cirr[++cnt] = *it;
	for (int i = 1; i <= cnt; ++i) vis[cirr[i]] = 1;
	for (int i = 1; i <= cnt; ++i) dfs2(cirr[i]);
	memset(f, 0, sizeof(f));
	f[2][0] = dp[cirr[2]][0];
	for (int i = 3; i < cnt; ++i) 
	{
		f[i][0] = dp[cirr[i]][0];
		f[i][1] = dp[cirr[i]][1];
		f[i][0] += max(f[i - 1][0], f[i - 1][1]);
		f[i][1] += f[i - 1][0];
	}
	f[cnt][0] = dp[cirr[cnt]][0] + max(f[cnt - 1][0], f[cnt - 1][1]);
	ans[x] = dp[cirr[1]][1] + f[cnt][0];
	memset(f, 0, sizeof(f));
	for (int i = 2; i <= cnt; ++i) 
	{
		f[i][0] = dp[cirr[i]][0];
		f[i][1] = dp[cirr[i]][1];
		f[i][0] += max(f[i - 1][0], f[i - 1][1]);
		f[i][1] += f[i - 1][0];
	}
	ans[x] = max(ans[x], dp[cirr[1]][0] + max(f[cnt][0], f[cnt][1]));
}

int main()
{
	scanf("%d", &n);
	for (int a, i = 1; i <= n; ++i)
	{
		scanf("%lld", &w[i]);
		scanf("%d", &a);
		AddEdge(a, i);
		AddEdge(i, a);
	}
	for (int i = 1; i <= n; ++i)
		if (!vis[i]) ++tot, dfs1(i);
	for (int i = 1; i <= tot; ++i) Work(i);
	for (int i = 1; i <= tot; ++i) Ans += ans[i];
	printf("%lld\n", Ans);
	
	return 0;
}
