#include <iostream>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <algorithm>
#include <cmath>
#include <set>
#include <string>

using namespace std;

const int MAXL = 30;
const int MAXN = 110;
const int MAXS = (1 << 10) + 10;

int son[MAXN][26], Fail[MAXN], ma[MAXN];
int n, l, tot, q[MAXN], head, tail;
long long ans, dp[MAXL][MAXN][MAXS];
char str[MAXN];
string now, vs;
set <string> S;

int Find(int no, int x)
{
	for (int i = 0; i < 26; ++i) if (son[no][i] == x) return i;
	return -1;
}

void dfs(int i, int j, int k)
{
    if (dp[i][j][k] == 0) return;
    if (i == 0)
    {
		vs.clear();
		for (int i = 0; i <= l - 1; i++)
			vs.push_back(now[l - 1 - i]);
        S.insert(vs);
        return;
    }
    for (int last = 0; last <= tot; last++)
    {
        int x = Find(last, j);
        if (x == -1) continue;
        now.push_back(x + 'a');
        dfs(i - 1, last, k);
        dfs(i - 1, last, k ^ ma[j]);
        now.erase(--now.end());
    }
}

bool cmp(int a[], int b[])
{
	for (int i = 1; i <= l; ++i) if (a[i] != b[i]) return a[i] < b[i];
	return true;
}

int main()
{
	scanf("%d%d", &l, &n);
	for (int z = 0; z < n; ++z)
	{
		scanf("%s", str);
		int p = 0;
		for (int i = 0; str[i]; ++i)
		{
			if (!son[p][str[i] - 'a']) son[p][str[i] - 'a'] = ++tot;
			p = son[p][str[i] - 'a'];
		}
		ma[p] |= (1 << z);
	}
	for (int i = 0; i < 26; ++i) if (son[0][i]) q[tail++] = son[0][i];
	while (head != tail)
	{
		int p = q[head++];
		ma[p] |= ma[Fail[p]];
		for (int i = 0; i < 26; ++i) if (son[p][i])
		{
			int k = Fail[p];
			Fail[son[p][i]] = son[k][i];
			q[tail++] = son[p][i];
		}
		else son[p][i] = son[Fail[p]][i];
	}
	dp[0][0][0] = 1;
	for (int i = 0; i < l; ++i)
		for (int j = 0; j <= tot; ++j)
			for (int k = 0; k < (1 << n); ++k) 
			{
				if (dp[i][j][k] == 0) continue;
				for (int p = 0; p < 26; ++p) 
				{
					int now = son[j][p];
					dp[i + 1][now][k | ma[now]] += dp[i][j][k];
				}
			}
	for (int i = 0; i <= tot; ++i) ans += dp[l][i][(1 << n) - 1];
	printf("%lld\n", ans);
	if (ans <= 42)
	{
		for (int i = 0; i <= tot; ++i) 	dfs(l, i, (1 << n) - 1);
		set<string> :: iterator it;	
		for (it = S.begin(); it != S.end(); it++) cout<<*it<<endl;
	}
	
	return 0;
}
