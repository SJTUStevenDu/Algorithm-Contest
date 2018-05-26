#include <iostream>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <cmath>
#include <fstream>
#include <algorithm>

using namespace std;

const int MAXN = 100000 + 10;

int V, n;
int num[MAXN], p[MAXN];
bool f[MAXN];

int main()
{
	while (~scanf("%d", &V))
	{
		scanf("%d", &n);
		for (int i = 1; i <= n; ++i) scanf("%d%d", &num[i], &p[i]);
		memset(f, 0, sizeof(f));
		f[0] = 1;
		for (int i = 1; i <= n; ++i)
		{
			for (int j = 1; j <= num[i]; j *= 2)
			{
				num[i] -= j;
				for (int k = V; k >= p[i] * j; --k) f[k] = (f[k] || f[k - p[i] * j]);
			}
			for (int k = V; k >= p[i] * num[i]; --k) f[k] = (f[k] || f[k - p[i] * num[i]]);
		}
		for (; !f[V]; --V);
		printf("%d\n", V);
	}
	
	return 0;
}
