#include <iostream>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <cmath>
#include <fstream>
#include <algorithm>

using namespace std;

const int MAXN = 10000 + 10;
const int BASE = 10000;

struct BigNum
{
	int a[MAXN];
	int len;
	BigNum () {memset(a, 0, sizeof(a)); len = 1;}
} f[50];

BigNum Mul(BigNum A, BigNum B)
{
	BigNum res;
	for (int i = 1; i <= A.len; ++i)
		for (int j = 1; j <= B.len; ++j) res.a[i + j - 1] += A.a[i] * B.a[j];
	res.len = A.len + B.len - 1;
	for (int i = 1; i <= res.len; ++i)
	{
		res.a[i + 1] += res.a[i] / BASE;
		res.a[i] %= BASE;
		if (res.a[res.len + 1]) ++res.len;
	}
	return res;
}

BigNum Plus(BigNum A, BigNum B)
{
	BigNum res;
	for (int i = 1; i <= A.len; ++i) res.a[i] = A.a[i] + B.a[i];
	res.len = A.len;
	for (int i = 1; i <= res.len; ++i)
	{
		res.a[i + 1] += res.a[i] / BASE;
		res.a[i] %= BASE;
		if (res.a[res.len + 1]) ++res.len;
	}
	return res;
}

BigNum Minus(BigNum A, BigNum B)
{
	BigNum res;
	for (int i = 1; i <= A.len; ++i) res.a[i] = A.a[i] - B.a[i];
	res.len = A.len;
	for (int i = 1; i <= res.len; ++i) 
		while (res.a[i] < 0) res.a[i] += BASE, res.a[i + 1]--;
	while (res.a[res.len] == 0) --res.len;
	return res;
}

void Print(BigNum A)
{
	printf("%d", A.a[A.len]);
	for (int i = A.len - 1; i; --i) printf("%04d", A.a[i]);
	printf("\n");
}

BigNum QuickMul(BigNum A, int b)
{
	BigNum res;
	res.a[1] = 1;
	while (b)
	{
		if (b & 1) res = Mul(res, A);
		b >>= 1;
		A = Mul(A, A);
	}
	return res;
}

int n, m;

int main()
{
	scanf("%d%d", &m, &n);
	for (int i = 0; i <= n; ++i) f[i].a[1] = 1;
	for (int i = 1; i <= n; ++i)
	{
		f[i] = QuickMul(f[i - 1], m);
		f[i] = Plus(f[i], f[0]);
	}
	Print(Minus(f[n], f[n - 1]));
	
	return 0;
}
