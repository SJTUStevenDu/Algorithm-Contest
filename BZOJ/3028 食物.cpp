#include <iostream>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <cmath>
#include <fstream>
#include <algorithm>

using namespace std;

const int MAXN = 5000 + 10;
const int BASE = 1000;

char S[MAXN];

struct BigNum
{
	int a[MAXN], len;
	BigNum() {memset(a, 0, sizeof(a)); len = 0;}
	void Read()
	{
		scanf("%s", S + 1);
		int L = strlen(S + 1);
		for (int i = L; i > 0; i -= 3)
		{
			++len;
			for (int j = max(i - 2, 1); j <= i; ++j) a[len] = a[len] * 10 + S[j] - '0';
		}
	}
	void Mul(BigNum A)
	{
		BigNum ret;
		for (int i = 1; i <= len; ++i)
			for (int j = 1; j <= A.len; ++j) ret.a[i + j - 1] += a[i] * A.a[j];
		ret.len = A.len + len - 1;
		len = ret.len; memcpy(a, ret.a, sizeof(a));
		for (int i = 1; i <= len; ++i) 
		{
			a[i + 1] += a[i] / BASE;
			a[i] %= BASE;
			if (a[len + 1]) ++len;
		}
	}
	void Div(int b)
	{
		for (int i = len; i; --i)
		{
			a[i - 1] += a[i] % b * BASE;
			a[i] /= b;
		}
		a[0] = 0;
		for (; !a[len] && len > 1; --len);
	}
	void Minus(BigNum A)
	{
		for (int i = 1; i <= len; ++i) a[i] -= A.a[i];
		for (int i = 1; i <= len; ++i)
			if (a[i] < 0) a[i + 1] -= ((-a[i] - 1) / BASE + 1), a[i] += ((-a[i] - 1) / BASE + 1) * BASE;
		for (; !a[len] && len > 1; --len);
	}
	void Plus(int b)
	{
		a[1] += b;
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
		for (int i = len - 1; i; --i) printf("%03d", a[i]);
		putchar('\n');
	}
} n, n1, n2, n10007, tmp;

int main()
{
	n.Read(); n1 = n; n2 = n;
	n1.Plus(1); n2.Plus(2);
	n10007.len = 2; n10007.a[1] = 7; n10007.a[2] = 10;
	n.Mul(n1);
	n.Div(2);
	n.Mul(n2);
	n.Div(3);
	tmp = n;
	tmp.Div(10007);
	tmp.Mul(n10007);
	n.Minus(tmp);
	n.Print();
	
	return 0;
}
