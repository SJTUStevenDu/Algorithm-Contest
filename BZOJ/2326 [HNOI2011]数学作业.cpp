#include <iostream>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <cmath>
#include <algorithm>
#include <fstream>

using namespace std;

struct Matrix
{
	int n, m;
	long long a[5][5];
	Matrix (int _n = 0, int _m = 0) {n = _n; m = _m; memset(a, 0, sizeof(a));}
} ans(1, 3), t(3, 3);

long long S;
int MOD;

Matrix Mul(Matrix A, Matrix B)
{
	Matrix res(A.n, B.m);
	for (int i = 1; i <= res.n; ++i)
		for (int j = 1; j <= res.m; ++j)
			for (int k = 1; k <= A.m; ++k) res.a[i][j] += A.a[i][k] * B.a[k][j], res.a[i][j] %= MOD;
	return res;
}

int main()
{
	scanf("%lld", &S);
	scanf("%d", &MOD);
	ans.a[1][3] = 1;
	for (long long ten = 1; ten <= S;)
	{
		ten *= 10;
		memset(t.a, 0, sizeof(t.a));
		t.a[1][1] = ten % MOD;
		t.a[2][1] = t.a[3][1] = t.a[2][2] = t.a[3][2] = t.a[3][3] = 1;
		long long k = min(ten - 1, S) - ten / 10 + 1;
		while (k)
		{
			if (k & 1) ans = Mul(ans, t);
			k >>= 1;
			t = Mul(t, t);
		}
	}
	printf("%lld\n", ans.a[1][1]);
	
	return 0;
}
