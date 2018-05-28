#include <iostream>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <algorithm>
#include <ctime>

using namespace std;

const int BASE = 100000000;

int T;
char S[20000];

struct BigNum
{
	int a[10000];
	void read()
	{
		scanf("%s", S+1);
		int len = strlen(S + 1);
		a[0] = (len - 1) / 8 + 1;
		for (int i = 1; i <= a[0]; ++i)
		{
			int lim = max(1, len - 8 * i + 1);
			for (int j = lim; j <= len - (i - 1) * 8; ++j) a[i] = a[i] * 10 + S[j] - '0';
		}
	}
	void print()
	{
		int len = a[0];
		printf("%d", a[len]);
		for (int i = len - 1; i; --i) printf("%08d", a[i]);
		putchar('\n');
	}
	void Mul2()
	{
		int len = a[0];
		for (int i = 1; i <= len; ++i) a[i]*=2;
		for (int i = 1; i <= len; ++i) a[i + 1] += a[i] / BASE, a[i] %= BASE;
		if (a[len + 1]) len++;
		a[0] = len;
	}
	void Div2()
	{
		int len = a[0];
		int x = 0;
		for (int i = len; i; --i) x = x * BASE + a[i], a[i] = x / 2, x %= 2;
		while (!a[len] && len > 1) --len;
		a[0] = len;
	}
	void Minus(const BigNum &A)
	{
		int len = A.a[0];
		for (int i = 1; i <= len; ++i) a[i] -= A.a[i];
		for (int i = 1; i <= len; ++i) if (a[i] < 0) a[i] += BASE, a[i + 1]--;
		len = a[0];
		while (!a[len] && len > 1) --len;
		a[0] = len;
	}
	int Cmp(const BigNum &A)
	{
		if (a[0] > A.a[0]) return 1;
		if (a[0] < A.a[0]) return -1;
		int len = a[0];
		for (int i = len; i; --i)
		{
			if (a[i] > A.a[i]) return 1;
			if (a[i] < A.a[i]) return -1;
		}
		return 0;
	}
	bool Odd()
	{
		if (a[1] % 2 == 1) return true;
		return false;
	}
}n, m;

int main()
{
	n.read(); m.read();
	while (!n.Odd() && !m.Odd()) T++, n.Div2(), m.Div2();
	for (;;)
	{
		int k = n.Cmp(m);
		if (!k) break;
		if (k == 1) n.Minus(m);
		else m.Minus(n);
		while (!n.Odd()) n.Div2();
		while (!m.Odd()) m.Div2();
	}
	while (T--) n.Mul2();
	n.print();
	
	return 0;
}
