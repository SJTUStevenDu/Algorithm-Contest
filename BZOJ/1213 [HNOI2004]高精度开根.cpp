#include <iostream>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <algorithm>
#include <cmath>

using namespace std;

const int MAXN = 30000 + 10;
const int BASE = 1000;

char S[MAXN];
int m;

struct BigNum
{
	int a[MAXN], len;
	BigNum() {memset(a, 0, sizeof(a)); len = 1;}
	void read()
	{
		scanf("%s", S + 1);
		int l = strlen(S + 1);
		len = 0;
		for (int i = l; i > 0; i -= 3)
		{
			++len;
			for (int j = max(1, i - 2); j <= i; ++j) a[len] = a[len] * 10 + S[j] - '0';
		}
	}
	void Print()
	{
		printf("%d", a[len]);
		for (int i = len - 1; i; --i) printf("%03d", a[i]);
		putchar('\n');
	}
} X, L, R, MID;

bool cmp(BigNum A, BigNum B)
{
	if (A.len > B.len) return 1;
	if (A.len < B.len) return 0;
	for (int i = A.len; i; --i)
	{
		if (A.a[i] > B.a[i]) return 1;
		if (A.a[i] < B.a[i]) return 0;
	}
	return 0;
}

BigNum Mul(BigNum A, BigNum B)
{
	BigNum ret;
	for (int i = 1; i <= A.len; ++i) 
		for (int j = 1; j <= B.len; ++j) ret.a[i + j - 1] += A.a[i] * B.a[j];
	ret.len = A.len + B.len - 1;
	for (int i = 1; i <= ret.len; ++i)
	{
		ret.a[i + 1] += ret.a[i] / BASE;
		ret.a[i] %= BASE;
		if (ret.a[ret.len + 1]) ++ret.len;
	}
	return ret;
}

BigNum Plus(BigNum A, BigNum B)
{
	BigNum ret;
	ret.len = max(A.len, B.len);
	for (int i = 1; i <= ret.len; ++i) ret.a[i] = A.a[i] + B.a[i];
	for (int i = 1; i <= ret.len; ++i)
	{
		ret.a[i + 1] += ret.a[i] / BASE;
		ret.a[i] %= BASE;
		if (ret.a[ret.len + 1]) ++ret.len;
	}
	return ret;
}

BigNum Div(BigNum A, int b)
{
	for (int i = A.len; i; --i)
	{
		A.a[i - 1] += (A.a[i] % b) * BASE;
		A.a[i] /= b;
	}
	A.a[0] = 0;
	for (; A.len > 1 && !A.a[A.len]; A.len--);
	return A;
}

BigNum QuickMul(BigNum S, int b)
{
	BigNum ret, A;
	A = S;
	ret.a[1] = 1;
	while (b)
	{
		if (b & 1) ret = Mul(ret, A);
		b >>= 1;
		A = Mul(A, A);
	}
	return ret;
}

int main()
{
	scanf("%d", &m);
	X.read();
	R.len = min(300, X.len / m + 30);
	R.a[R.len] = 1;
	if (!cmp(X, R)) R = X;
	for (; !cmp(L, R);)
	{
		MID = Div(Plus(L, R), 2);
		if (cmp(QuickMul(MID, m), X))
		{
			R = MID;
			R.a[1]--;
			for (int i = 1; i <= R.len; ++i)
			{
				if (R.a[i] >= 0) break;
				R.a[i] += BASE; R.a[i + 1]--;
			}
			if (!R.a[R.len] && R.len > 1) --R.len;
		}
		else 
		{
			L = MID;
			L.a[1]++;
			for (int i = 1; i <= L.len; ++i)
			{
				if (L.a[i] < BASE) break;
				L.a[i] -= BASE; L.a[i + 1]++;
			}
			if (L.a[L.len + 1]) ++L.len;
		}
	}
	R.Print();
	
	return 0;
}
