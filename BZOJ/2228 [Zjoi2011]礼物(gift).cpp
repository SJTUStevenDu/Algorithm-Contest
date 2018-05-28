#include <iostream>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <cmath>
#include <fstream>
#include <algorithm>

using namespace std;

const int MAXN = 150 + 10;

bool w[MAXN][MAXN][MAXN], tmp[MAXN][MAXN][MAXN];
int n, m, p, f[MAXN][MAXN][MAXN], ans, q[MAXN][2], r;
char SS[MAXN];

void Work()
{
	memset(f, 0, sizeof(f));
	for (int k = 1; k <= p; ++k)
	{
		for (int i = 1; i <= n; ++i)
			for (int j = 1; j <= m; ++j)
				if (w[i][j][k]) f[i][j][k] = min(min(f[i - 1][j][k], f[i][j - 1][k]), f[i - 1][j - 1][k]) + 1;	
	}
	for (int i = 1; i <= n; ++i)
		for (int j = 1; j <= m; ++j) 
		{
			r = 0;
			for (int k = 1; k <= p + 1; ++k)
			{
				while (r && q[r][1] >= f[i][j][k]) 
				{
					ans = max(ans, q[r][1] * (k - q[r - 1][0] - 1));
					--r;
				}
				++r;
				q[r][0] = k;
				q[r][1] = f[i][j][k];
			}
		}
}

void Rotate()
{
	memset(tmp, 0, sizeof(tmp));
	for (int i = 1; i <= n; ++i)
		for (int j = 1; j <= m; ++j) 
			for (int k = 1; k <= p; ++k) tmp[k][i][j] = w[i][j][k];
	int ttt = p; p = m; m = n; n = ttt;
	memcpy(w, tmp, sizeof(tmp));
}

int main()
{
	scanf("%d%d%d", &n, &m, &p);
	for (int j = 1; j <= m; ++j)
		for (int i = 1; i <= n; ++i)
		{
			scanf("%s", SS + 1);
			for (int k = 1; k <= p; ++k) w[i][j][k] = (SS[k] == 'N');
		}
	Work();
	Rotate();
	Work();
	Rotate();
	Work();
	printf("%d\n", ans * 4);
	
	return 0;
}
