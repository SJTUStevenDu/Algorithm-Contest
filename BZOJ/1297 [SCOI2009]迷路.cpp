#include <iostream>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <cmath>
#include <algorithm>
#include <fstream>

using namespace std;

const int MAXN = 111;
const int MOD = 2009;

struct Matrix
{
	int a[MAXN][MAXN];
	Matrix() {memset(a, 0, sizeof(a));}
} ans;

int n, T, m;
char map[MAXN][MAXN];

inline int f(int i, int j)
{
	return (i - 1) * 10 + j;
}

Matrix Mul(Matrix A, Matrix B)
{
	Matrix res;
	for (int i = 0; i <= m; ++i)
		for (int j = 0; j <= m; ++j)
			for (int k = 0; k <= m; ++k) res.a[i][j] = (res.a[i][j] + A.a[i][k] * B.a[k][j]) % MOD;
	return res;
}

Matrix QuickMul(Matrix A, int b)
{
	Matrix res;
	bool flag = false;
	while (b)
	{
		if (b & 1) 
		{
			if (!flag) flag = true, res = A;
			else res = Mul(res, A);
		}
		b >>= 1;
		A = Mul(A, A);
	}
	return res;
}

int main()
{
	scanf("%d%d", &n, &T);
	for (int i = 1; i <= n; ++i)
	{
		scanf("%s", map[i] + 1);
		for (int j = 1; j <= n; ++j) map[i][j] -= '0';
	}
	m = f(n, 10);
	for (int i = 1; i <= n; ++i)
		for (int j = 0; j < 8; ++j) ans.a[f(i, j)][f(i, j + 1)] = 1;
	for (int i = 1; i <= n; ++i)
		for (int j = 1; j <= n; ++j) if (map[i][j])
			ans.a[f(i, map[i][j] - 1)][f(j, 0)] = 1;
	ans = QuickMul(ans, T);
	printf("%d\n", ans.a[f(1, 0)][f(n, 0)]);
	
	return 0;
}
