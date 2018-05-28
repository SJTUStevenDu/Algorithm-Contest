#include <iostream>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <cmath>
#include <fstream>
#include <algorithm>

using namespace std;

const int MAXN = (1 << 13) + 10;


int n, m, s[MAXN], zc, u, a[MAXN], ss;
char z[MAXN];

int main()
{
	scanf("%d", &n);
	m = 1 << (n - 1);
	for (int i = 0; i < m; i++) a[i] = 0;
	s[ss++] = ss = 0;
	zc = n + m * 2;
	while (ss)
	{
		u = s[--ss];
		z[--zc] = u % 2 + '0';
		u /= 2;
		for (int w; a[u] < 2;)
		{
			w = 2 * u + a[u];
			a[u]++;
			s[ss++]=w;
			u=w%m;
		}
	}
	while (zc) z[--zc] = '0';
	z[m * 2]=0;
	printf("%d %s\n", 1 << n, z);
	
	return 0;
}
