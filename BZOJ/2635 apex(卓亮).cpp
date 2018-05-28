#include <iostream>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <cmath>
#include <fstream>
#include <algorithm>

using namespace std;

const int MAXN = 2000000 + 10;

int f[MAXN], sum[MAXN], T, opr;
long long x;

int S(long long x)
{
	if (x <= 2000000) return f[x];
	if (x % 2 == 0) return -S(x / 2);
	if (((x + 1) / 2) % 2 == 1) return S((x + 1) / 2);
	else return -S((x + 1) / 2);
}

long long Query(long long x)
{
	if (x <= 2000000) return sum[x];
	if (x % 4 == 0) return 2 * Query(x / 4);
	if (x % 4 == 3) return Query(x - 3) + S(x);
	return Query(x - 1) + S(x);
}

int main()
{
	f[1] = 1;
	for (int i = 2; i <= 2000000; ++i) 
	{
		if (i % 2 == 0) f[i] = - f[i / 2];
		else if (((i + 1) / 2) % 2 == 1) f[i] = f[(i + 1) / 2];
		else f[i] = - f[(i + 1) / 2];
	}
	for (int i = 1; i <= 2000000; ++i) sum[i] = sum[i - 1] + f[i];
	scanf("%d", &T);
	while (T--)
	{
		scanf("%d", &opr);
		scanf("%lld", &x);
		if (opr == 1) printf("%d\n", S(x));
		else if (opr == 3) printf("%lld\n", Query(x));
		else 
		{
			long long tmp = Query(x);
			if (tmp > 0) puts("+");
			else if (tmp == 0) puts("0");
			else puts("-");
		}
	}
	
	return 0;
}
