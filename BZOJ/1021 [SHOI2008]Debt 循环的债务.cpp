#include <iostream>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <cmath>
#include <algorithm>
#include <fstream>
#include <queue>

using namespace std;

const int MAXN = 1000 + 10;
const int Money[7] = {0, 1, 5, 10, 20, 50, 100};
const int INF =  0x7FFFFFFF >> 2;

int v3, v1, v2;
int dp[8][MAXN][MAXN];
int Amount[4][8], vNow[4], vExt[4];
int vSrc[4], vTar[4], ans = INF, sum;

struct Info
{
	int vA, vB;
};

queue <Info> Q[8];

int main()
{
	scanf("%d%d%d", &v1, &v2, &v3);
	for (int i = 1; i <= 3; ++i)
		for (int j = 6; j; --j)
		{
			scanf("%d", &Amount[i][j]);
			sum += Amount[i][j] * Money[j];
			vSrc[i] += Amount[i][j] * Money[j];
		}
	vTar[1] = vSrc[1] - v1 + v3;
	vTar[2] = vSrc[2] - v2 + v1;
	vTar[3] = vSrc[3] - v3 + v2;
	for (int i = 0; i < 7; ++i)
		for (int j = 0; j < MAXN; ++j)
			for (int k = 0; k < MAXN; ++k) dp[i][j][k] = INF;
	Q[0].push((Info){vSrc[1], vSrc[2]});
	dp[0][vSrc[1]][vSrc[2]] = 0;
	for (int i = 0; i < 7; ++i)
	{
		for (; !Q[i].empty(); Q[i].pop())
		{
			vNow[1] = Q[i].front().vA; vNow[2] = Q[i].front().vB; vNow[3] = sum - vNow[1] - vNow[2];
			if (vNow[1] == vTar[1] && vNow[2] == vTar[2]) ans = min(ans, dp[i][vNow[1]][vNow[2]]);
			if (i == 6) continue;
			for (int pNow = 1; pNow <= 3; ++pNow)
			{
				int prev = (pNow == 1) ? 3 : pNow - 1;
				int nxt = (pNow == 3) ? 1 : pNow + 1;
				for (int g1 = 0; g1 <= Amount[pNow][i + 1]; ++g1)
					for (int g2 = 0; g2 <= Amount[pNow][i + 1] - g1; ++g2)
					{
						vExt[pNow] = vNow[pNow] - Money[i + 1] * (g1 + g2);
						vExt[prev] = vNow[prev] + Money[i + 1] * g1;
						vExt[nxt] = vNow[nxt] + Money[i + 1] * g2;
						if (dp[i + 1][vExt[1]][vExt[2]] > dp[i][vNow[1]][vNow[2]] + g1 + g2) 
						{
							dp[i + 1][vExt[1]][vExt[2]] = dp[i][vNow[1]][vNow[2]] + g1 + g2;
							Q[i + 1].push((Info){vExt[1], vExt[2]});
						}
					}
				for (int g1 = 0; g1 <= Amount[prev][i + 1]; ++g1)
					for (int g2 = 0; g2 <= Amount[nxt][i + 1] - g1; ++g2)
					{
						vExt[pNow] = vNow[pNow] + Money[i + 1] * (g1 + g2);
						vExt[prev] = vNow[prev] - Money[i + 1] * g1;
						vExt[nxt] = vNow[nxt] - Money[i + 1] * g2;
						if (dp[i + 1][vExt[1]][vExt[2]] > dp[i][vNow[1]][vNow[2]] + g1 + g2) 
						{
							dp[i + 1][vExt[1]][vExt[2]] = dp[i][vNow[1]][vNow[2]] + g1 + g2;
							Q[i + 1].push((Info){vExt[1], vExt[2]});
						}
					}
			}
		}
	}
	if (ans == INF) puts("impossible");
	else printf("%d\n", ans);
	
	return 0;
}
