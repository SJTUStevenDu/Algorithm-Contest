#include <iostream>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <algorithm>
#include <cmath>

using namespace std;

const int MAXN = 25000 + 10;
const int MAXM = 100000 + 10;
const int BASE = 1000;

char S[MAXN];

struct BigNum
{
	int a[MAXN], len, idx;
	BigNum() {memset(a, 0, sizeof(a)); len = 1;}
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
	void Read()
	{
		scanf("%s", S + 1);
		int L = strlen(S + 1);
		len = 0;
		for (int i = L; i > 0; i -= 3)
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
} n[105], m, ans[105], tmp;

bool operator <= (BigNum &A, BigNum &B)
{
	if (A.len != B.len) return A.len < B.len;
	for (int i = A.len; i; --i) if (A.a[i] != B.a[i]) return A.a[i] < B.a[i];
	return true;
}

int T, prm[MAXM / 10], Top;
bool vis[MAXM]; 

int main()
{
	for (int i = 2; i < 100000; ++i) 
	{
		if (!vis[i]) prm[++Top] = i;
		for (int j = 1; j <= Top && i * prm[j] < 100000; ++j) 
		{
			vis[i * prm[j]] = 1;
			if (i % prm[j] == 0) break;
		}
	}
	scanf("%d", &T);
	for (int i = 1; i <= T; ++i) n[i].Read(), n[i].idx = i;
	for (int i = 1; i < T; ++i) 
		for (int j = i + 1; j <= T; ++j)
		{
			if (n[i] <= n[j]) continue;
			swap(n[i], n[j]);
		}
	
	m.a[1] = 1;
	int now = 1, kk = 1;
	while (now <= T)
	{
		tmp = m;
		tmp.Mul(prm[kk]);
		while (!(tmp <= n[now]) && now <= T) ans[n[now].idx] = m, ++now;
		m = tmp;
		++kk;
	}
	for (int i = 1; i <= T; ++i) ans[i].Print();
	
	return 0;
}
