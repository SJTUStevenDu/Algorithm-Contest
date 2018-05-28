#include <iostream>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <cmath>
#include <algorithm>
#include <fstream>

using namespace std;

const int MAXN = 50 + 10;
const int MOD = 10000;

struct Matrix 
{
	int a[MAXN][MAXN];
	int n, m;
	Matrix () {memset(a, 0, sizeof(a)); n = 0; m = 0;}
} ans;

Matrix Mul(Matrix A, Matrix B)
{
	Matrix C;
	C.n = A.n; C.m = B.m;
	for (int i = 1; i <= C.n; ++i) 
		for (int j = 1; j <= C.m; ++j)
			for (int k = 1; k <= A.m; ++k) C.a[i][j] = (C.a[i][j] + A.a[i][k] * B.a[k][j]) % MOD;
	return C;
}

Matrix QuickPow(Matrix A, int b)
{
	Matrix res;
	res.n = res.m = A.n;
	for (int i = 1; i <= res.n; ++i) res.a[i][i] = 1;
	while (b)
	{
		if (b & 1)  res = Mul(res, A);
		b >>= 1;
		A = Mul(A, A);
	}
	return res;
}

int n, m, k, S, T, fish[MAXN][MAXN], nfish;
Matrix fac[15], tmp[15], tmp2;
bool map[MAXN][MAXN];

bool check(int t, int p)
{
	t = t % 12 + 1;
	for (int i = 1; i <= nfish; ++i) if (fish[t][i] == p) return false;
	return true;
}

int main()
{
	scanf("%d%d%d%d%d", &n, &m, &S, &T, &k);
	++S; ++T;
	for (int a, b, i = 1; i <= m; ++i)
	{
		scanf("%d%d", &a, &b);
		++a; ++b;
		map[a][b] = map[b][a] = 1;
	}
	scanf("%d", &nfish);
	for (int i = 1; i <= nfish; ++i)
	{
		int p;
		scanf("%d", &p);
		for (int j = 1; j <= p; ++j) scanf("%d", &fish[j][i]), ++fish[j][i];
		for (int j = p + 1; j <= 12; ++j) fish[j][i] = fish[j - p][i];
	}
	for (int t = 1; t <= 12; ++t)
	{
		tmp[t].n = tmp[t].m = n;
		for (int i = 1; i <= n; ++i)	
			for (int j = 1; j <= n; ++j)
				if (map[i][j] && check(t, j)) tmp[t].a[i][j] = 1;
	}
	for (int i = 1; i <= n; ++i) fac[0].a[i][i] = 1;
	fac[0].n = fac[0].m = n;
	for (int t = 1; t <= 12; ++t) fac[t] = Mul(fac[t - 1], tmp[t]);
	ans = QuickPow(fac[12], k / 12);
	tmp2.n = 1; tmp2.m = n; tmp2.a[1][S] = 1;
	ans = Mul(tmp2, ans);
	ans = Mul(ans, fac[k % 12]);
	printf("%d\n", ans.a[1][T]);
	
	return 0;
}
