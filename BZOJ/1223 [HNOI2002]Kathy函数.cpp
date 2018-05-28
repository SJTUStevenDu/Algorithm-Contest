#include <iostream>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <cmath>
#include <fstream>
#include <algorithm>

using namespace std;

const int MAXN = 400 + 10;

char s[MAXN];

struct BigNum
{
	int a[MAXN], len;
	BigNum() {memset(a, 0, sizeof(a)); len = 1;}
	void Read()
	{
		scanf("%s", s + 1);
		len = strlen(s + 1);
		for (int i = 1; i <= len; ++i) a[i] = s[len - i + 1] - '0';
	}
	void Div2()
	{
		for (int i = len; i; --i)
		{
			a[i - 1] += (a[i] & 1) * 10;
			a[i] /= 2;
		}
		a[0] = 0;
		for (; len > 1 && !a[len]; --len);
	}
	void Mul(int b)
	{
		for (int i = 1; i <= len; ++i) a[i] *= b;
		for (int i = 1; i <= len; ++i)
		{
			a[i + 1] += a[i] / 10;
			a[i] %= 10;
			if (a[len + 1]) ++len;
		}
	}
	void Plus(BigNum A)
	{
		len = max(len, A.len);
		for (int i = 1; i <= len; ++i) a[i] += A.a[i];
		for (int i = 1; i <= len; ++i)
		{
			a[i + 1] += a[i] / 10;
			a[i] %= 10;
			if (a[len + 1]) ++len;
		}
	}
	void Print()
	{
		for (int i = len; i; --i) printf("%d", a[i]);
		putchar('\n');
	}
} n, t, ans, pw[MAXN], m, one, xx, yy;

bool cmp(BigNum A, BigNum B)
{
	for (int i = 1; i <= A.len; ++i) if (A.a[i] != B.a[i]) return A.a[i] < B.a[i];
	return 1;
}

int main()
{
	one.a[1] = 1;
	n.Read();
	t.len = 0;
	for (;; n.Div2())
	{
		if (n.len == 1 && n.a[1] == 0) break;
		t.a[++t.len] = n.a[1] % 2;
	}
	for (int i = 1; i <= t.len / 2; ++i) swap(t.a[i], t.a[t.len - i + 1]);
	pw[0].a[1] = 1;
	for (int i = 1; i <= t.len; ++i)
	{
		pw[i] = pw[i - 1];
		pw[i].Mul(2);
	}
	m.len = t.len;
	m.a[1] = m.a[m.len] = 1;
	for (int i = 2; i * 2 - 1 <= t.len; ++i) 
	{
		int p = t.a[i];
		if (p == 1) ans.Plus(pw[(t.len - i * 2 + 1) / 2]);
		m.a[i] = m.a[m.len - i + 1] = p;
	}
	if (cmp(m, t)) ans.Plus(one);
	for (int i = 1; i < t.len; ++i) ans.Plus(pw[(i - 1) / 2]);
	ans.Print();
	
	return 0;
}
