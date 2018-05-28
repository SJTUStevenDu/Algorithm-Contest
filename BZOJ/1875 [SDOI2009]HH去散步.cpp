#include <iostream>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <cmath>
#include <fstream>
#include <algorithm>

using namespace std;

const int MAXN = 150 + 10;
const int MOD = 45989;

struct Matrix
{
	int a[MAXN][MAXN];
	Matrix () {memset(a, 0, sizeof(a));}
};

Matrix ans, map;
int n, m, T, A, B, Edge[MAXN][2], Ans;

Matrix Mul(Matrix A, Matrix B)
{
	Matrix res;
	for (int i = 1; i <= n; ++i)
		for (int j = 1; j <= n; ++j)
			for (int k = 1; k <= n; ++k) res.a[i][j] = (res.a[i][j] + A.a[i][k] * B.a[k][j]) % MOD;
	return res;
}

int main()
{
	scanf("%d%d%d%d%d", &n, &m, &T, &A, &B);
	if (T == 0) 
	{
		puts("1");
		return 0;
	}
	--T;
	for (int i = 1; i <= m; ++i) scanf("%d%d", &Edge[i][0], &Edge[i][1]);
	n = 2 * m;
	for (int i = 1; i <= m; ++i)
		for (int j = 1; j <= m; ++j) if (i != j)
		{
			if (Edge[i][1] == Edge[j][0]) map.a[i][j] = 1;
			if (Edge[i][0] == Edge[j][0]) map.a[i + m][j] = 1;
			if (Edge[i][1] == Edge[j][1]) map.a[i][j + m] = 1;
			if (Edge[i][0] == Edge[j][1]) map.a[i + m][j + m] = 1;
		}
	for (int i = 1; i <= n; ++i) ans.a[i][i] = 1;
	while (T)
	{
		if (T & 1) ans = Mul(ans, map);
		T >>= 1;
		map = Mul(map, map);
	}
	for (int i = 1; i <= m; ++i)
	{
		int k;
		if (Edge[i][0] == B) k = i + m;
		else if (Edge[i][1] == B) k = i;
		else continue;
		for (int j = 1; j <= m; ++j)
		{
			if (Edge[j][0] == A) Ans = (Ans + ans.a[j][k]) % MOD;
			if (Edge[j][1] == A) Ans = (Ans + ans.a[j + m][k]) % MOD;
		}
	}
	printf("%d\n", Ans);
	
	return 0;
}
