#include <iostream>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <cmath>
#include <algorithm>
#include <fstream>

using namespace std;

const int MAXN = 300 + 10;

int n, k, c[MAXN], ans;

int main()
{
	scanf("%d%d", &n, &k);
	for (int i = 1; i <= k; ++i) scanf("%d", &c[i]);
	sort(c + 1, c + 1 + k);
	for (int i = k; i; --i)
	{
		n -= 2;
		if (n < 0) break;
		ans += c[i] * (n + 1);
	}
	printf("%d\n", ans);
	
	return 0;
}
