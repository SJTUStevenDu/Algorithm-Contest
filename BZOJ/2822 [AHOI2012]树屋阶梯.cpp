#include <iostream>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <cmath>
#include <algorithm>
#include <fstream>

using namespace std;

const int MOD = 10000;

struct BigNum
{
	int a[505];
	int len;
	BigNum() {memset(a, 0, sizeof(a)); len = 1;}
} ans;

int n;

BigNum Mul(BigNum A, int x)
{
	BigNum res;
	res.len = A.len;
	for (int i = 1; i <= A.len; ++i) res.a[i] = A.a[i];
	for (int i = 1; i <= A.len; ++i) res.a[i] *= x;
	for (int i = 1; i <= res.len; ++i)
	{
		res.a[i + 1] += res.a[i] / MOD;
		res.a[i] %= MOD;
		if (res.a[res.len + 1]) res.len++;
	}
	return res;
}

BigNum Div(BigNum A, int x)
{
	BigNum res;
	res.len = A.len;
	for (int i = 1; i <= A.len; ++i) res.a[i] = A.a[i];
	for (int i = res.len; i; --i)
	{
		res.a[i - 1] += res.a[i] % x * MOD;
		res.a[i] /= x;
		if (!res.a[res.len]) res.len--;
	}
	return res;
}

void Print(BigNum A)
{
	printf("%d", A.a[A.len]);
	for (int i = A.len - 1; i; --i) printf("%04d", A.a[i]);
	printf("\n");
}

int main()
{
	scanf("%d", &n);
	ans.a[1] = ans.len = 1;
	for (int i = n + 2; i <= 2 * n; ++i) ans = Mul(ans, i);
	for (int i = 2; i <= n; ++i) ans = Div(ans, i);
	Print(ans);
	
	return 0;
}
