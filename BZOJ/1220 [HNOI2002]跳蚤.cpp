#include <iostream>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <algorithm>
#include <cmath>

using namespace std;

const int MAXN = 10000 + 10;
const int BASE = 1000;

struct BigNum
{
	int a[MAXN], len;
	BigNum() {memset(a, 0, sizeof(a)); len = 1;}
	void Print()
	{
		printf("%d", a[len]);
		for (int i = len - 1; i; --i) printf("%03d", a[i]);
		putchar('\n');
	}
	void Mul(BigNum A)
	{
		BigNum ret;
		for (int i = 1; i <= len; ++i)
			for (int j = 1; j <= A.len;++j) ret.a[i + j - 1] += a[i] * A.a[j];
		memcpy(a, ret.a, sizeof(a));
		len = len + A.len - 1;
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
	void Minus1()
	{
		--a[1];
		for (int i = 1; i <= len; ++i)
		{
			if (a[i] >= 0) break;
			a[i] += BASE;
			a[i + 1]--;
		}
		for (; len > 1 && !a[len]; --len);
	}
} ans, p, q;

int n, m;

int main()
{
	scanf("%d%d", &n, &m);
	int k = 2;
	ans.a[1] = 1;
	while (m > 1)
	{
		if (m % k == 0)
		{
			memset(p.a, 0, sizeof(p.a));
			p.a[1] = 1;
			p.len = 1;
			for (int i = 1; i <= n; ++i) p.Mul(k);
			q = p;
			q.Minus1();
			ans.Mul(q);
			m /= k;
			while (m % k == 0) 
			{
				ans.Mul(p);
				m /= k;
			}
		}
		if (k * k < m) ++k; else k = m;
	}
	ans.Print();
	
	return 0;
}
