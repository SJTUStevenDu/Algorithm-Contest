#include <iostream>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <cmath>
#include <fstream>
#include <algorithm>

using namespace std;

const int MAXN = 5000 + 10;

struct BigNum
{
	int a[MAXN];
	int len;
	BigNum() {memset(a, 0, sizeof(a)); len = 0;}
} ans;

BigNum Mul(BigNum A, int c)
{
	BigNum res;
	res.len = A.len;
	for (int i = 1; i <= A.len; ++i) res.a[i] = A.a[i];
	for (int i = 1; i <= res.len; ++i) res.a[i] = res.a[i] * c;
	for (int i = 1; i <= res.len; ++i)
	{
		res.a[i + 1] += res.a[i] / 10;
		res.a[i] %= 10;
		if (res.a[res.len + 1]) ++res.len;
	}
	return res;
}

void Print()
{
	printf("%d\n", ans.len);
	int eee = max(0, ans.len - 100);
	for (int i = ans.len; i > eee; --i) printf("%d", ans.a[i]);
	putchar('\n');
}

int n;

int main()
{
	scanf("%d", &n);
	ans.a[1] = ans.len = 1;
	if (n % 3 == 1)
	{
		for (int i = 1; i < n / 3; ++i) ans = Mul(ans, 3);
		ans = Mul(ans, 2); ans = Mul(ans, 2);
	}
	else 
	{
		for (int i = 1; i <= n / 3; ++i) ans = Mul(ans, 3);
		if (n % 3 == 2) ans = Mul(ans, 2); 
	}
	Print();
	
	return 0;
}
