#include <iostream>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <cmath>
#include <fstream>
#include <algorithm>

using namespace std;

const int MAXN = 100000 + 10;

long long a[MAXN], ans1, ans2;
int n;

int main()
{
	scanf("%d", &n);
	for (int i = 1; i <= n; ++i) scanf("%lld", &a[i]);
	for (int i = 2; i <= n; ++i) 
		if (a[i] - a[i - 1] > 0) ans1 += a[i] - a[i - 1]; else ans2 -= a[i] - a[i - 1];
	printf("%lld\n", max(ans1, ans2));
	printf("%lld\n", abs(ans1 - ans2) + 1);
	
	return 0;
}
