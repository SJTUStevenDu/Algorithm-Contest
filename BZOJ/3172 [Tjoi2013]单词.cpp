#include <iostream>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <cmath>
#include <fstream>
#include <algorithm>

using namespace std;

const int MAXN = 1000000 + 10;

int n, pn;
int nxt[MAXN][26], Fail[MAXN], v[MAXN], idx[205], q[MAXN], head, tail;
char s[MAXN];

int main()
{
	scanf("%d", &n);
	for (int i = 1; i <= n; ++i) 
	{
		scanf("%s", s + 1);
		int len = strlen(s + 1);
		int x = 0;
		for (int j = 1; j <= len; ++j)
		{
			int y = s[j] - 'a';
			if (!nxt[x][y]) nxt[x][y] = ++pn;
			x = nxt[x][y];
			++v[x];
		}
		idx[i] = x;
	}
	for (int i = 0; i < 26; ++i) if (nxt[0][i]) q[tail++] = nxt[0][i];
	while (head < tail)
	{
		int p = q[head++];
		int k;
		for (int i = 0; i < 26; ++i) if (nxt[p][i])
		{
			for (k = Fail[p]; k && !nxt[k][i]; k = Fail[k]);
			Fail[nxt[p][i]] = nxt[k][i];
			q[tail++] = nxt[p][i];
		}
	}
	for (int i = tail - 1; i >= 0; --i) v[Fail[q[i]]] += v[q[i]];
	for (int i = 1; i <= n; ++i) printf("%d\n", v[idx[i]]);
	
	return 0;
}
