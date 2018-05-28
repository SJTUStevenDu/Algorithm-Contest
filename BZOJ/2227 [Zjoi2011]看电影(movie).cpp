#include <iostream>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <algorithm>
#include <cmath>

using namespace std;

const int MOD = 1000;

struct BigNum
{
	int a[MOD], len;
	BigNum() {memset(a, 0, sizeof(a)); len = 0;}
	void Mul(int b)
	{
		for (int i = 1; i <= len; ++i) a[i] *= b;
		for (int i = 1; i <= len; ++i)
		{
			a[i + 1] += a[i] / MOD;
			a[i] %= MOD;
			if (a[len + 1]) ++len;
		}
	}
	void Print()
	{
		printf("%d", a[len]);
		for (int i = len - 1; i; --i) printf("%03d", a[i]);
	}
} A, B;

int gcd(int n, int m)
{
	while (m)
	{
		int tmp = n % m;
		n = m;
		m = tmp;
	}
	return n;
}

int T, n, k;

int main()
{
	scanf("%d", &T);
	while (T--)
	{
		scanf("%d%d", &n, &k);
		memset(A.a, 0, sizeof(A.a)); memset(B.a, 0, sizeof(B.a));
		A.len = A.a[1] = B.len = B.a[1] = 1;
		if (n > k) printf("0 1\n");
		else
		{
			for (int i = 1; i < n; ++i) A.Mul(k + 1);
			int tmp = k - n + 1, kk = n;
			while (1)
			{
				int gg = gcd(tmp, k);
				if (gg == 1) break;
				tmp /= gg; B.Mul(k / gg); kk--;
				if (kk == 0) break;
			}
			for (int i = 1; i <= kk; ++i) B.Mul(k);
			A.Mul(tmp);
			A.Print(); putchar(' ');
			B.Print(); putchar('\n');
		}
	}
	
	return 0;
}
