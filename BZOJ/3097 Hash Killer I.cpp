#include <iostream>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <cmath>
#include <fstream>
#include <algorithm>

using namespace std;

const int MAXN = 100000 + 10;

int a[MAXN], n, l;

int main()
{
	n = 1;
	a[1] = 1;
	for (int i = 1; i <= 12; ++i, n *= 2)
		for (int j = 1; j <= n; ++j)
			a[j + n] = (a[j] ^ 1);
	l = n >> 1;
	for (int i = 1; i <= l; ++i) a[++n] = 1;
	a[++n] = 0;
	for (int i = 1; i < l; ++i) a[++n] = 1;
	printf("%d %d\n", n, l);
	for (int i = 1; i <= n; ++i) if (a[i]) putchar('a'); else putchar('b');
	putchar('\n');
	
	return 0;
}
