#include <iostream>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <cmath>
#include <fstream>
#include <algorithm>

using namespace std;

const int MAXN = 50 + 10;
const int BASE = 10000;

struct BigNum
{
	int a[MAXN], len;
	BigNum() {memset(a, 0, sizeof(a)); len = 1;}
	void Plus(BigNum A)
	{
		len = max(len, A.len);
		for (int i = 1; i <= len; ++i) a[i] += A.a[i];
		for (int i = 1; i <= len; ++i) 
		{
			a[i + 1] += a[i] / BASE;
			a[i] %= BASE;
			if (a[len + 1]) ++len;
		}
	}
	void Mul(int b)
	{
		for (int i = 1; i <= len; ++i) a[i] *= b;
		for (int i = 1; i <= len; ++i) 
		{
			a[i + 1] += a[i] / BASE;
			a[i] %= BASE;
			if (a[len + 1]) ++len;
		}
	}
	void Print()
	{
		printf("%d", a[len]);
		for (int i = len - 1; i; --i) printf("%04d", a[i]);
		putchar('\n');
	}
};

int T, n;
BigNum dp[MAXN][MAXN], ans[MAXN];

int main()
{
	ans[1].a[1] = dp[1][1].a[1] = 1;
	for (int i = 2; i <= 50; ++i)
		for (int j = 1; j <= i; ++j)
		{
			BigNum tmp;
			dp[i][j] = dp[i - 1][j];
			dp[i][j].Plus(dp[i - 1][j - 1]);
			dp[i][j].Mul(j);
			ans[i].Plus(dp[i][j]);
		}
	scanf("%d", &T);
	while (T--)
	{
		scanf("%d", &n);
		ans[n].Print();
	}
	
	return 0;
}
