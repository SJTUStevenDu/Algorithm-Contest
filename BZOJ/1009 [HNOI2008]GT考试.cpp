#include <iostream>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <cmath>
#include <algorithm>
#include <fstream>

using namespace std;

const int MAXN = 20 + 10;

int n, m, MOD, ans;
char S[MAXN];
int p[MAXN], nxt[MAXN][MAXN], v[MAXN][MAXN], tmp[MAXN][MAXN], w[MAXN];

inline void Add(int &x, int b) {x = (x + b) % MOD;}

int main()
{
	scanf("%d%d%d", &n, &m, &MOD);
	scanf("%s", S + 1);
	for (int i = 2, j = 0; i <= m; ++i)
	{
		for (; j && S[i] != S[j + 1]; j = p[j]);
		p[i] = j += (S[i] == S[j + 1]);
	}
	for (int i = 0; i <= m; ++i) 
		for (int j = 0; j < 10; ++j)
		{
			if (S[i + 1] - '0' == j) nxt[i][j] = i + 1;
			else 
			{
				int x = i;
				while (x && S[x + 1] - '0' != j) x = p[x];
				nxt[i][j] = nxt[x][j];
			}
			if (nxt[i][j] != m) ++v[i][nxt[i][j]];
		}
	w[0] = 1;
	while (n)
	{
		if (n & 1) 
		{
			for (int i = 0; i <= m; ++i) tmp[0][i] = 0;
			for (int i = 0; i <= m; ++i)
				for (int j = 0; j <= m; ++j) Add(tmp[0][i], w[j] * v[j][i]);
			memcpy(w, tmp[0], sizeof(w));
		}
		n >>= 1;
		for (int i = 0; i <= m; ++i)
			for (int j = 0; j <= m; ++j) tmp[i][j] = 0;
		for (int i = 0; i <= m; ++i)
			for (int j = 0; j <= m; ++j)
				for(int k = 0; k <= m; ++k) Add(tmp[i][j], v[i][k] * v[k][j]);
		memcpy(v, tmp, sizeof(tmp));
	}
	for (int i = 0; i < m; ++i) Add(ans, w[i]);
	printf("%d\n", ans);
	
	return 0;
}
