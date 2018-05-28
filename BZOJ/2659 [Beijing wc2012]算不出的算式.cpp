#include <iostream>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <cmath>
#include <fstream>
#include <algorithm>

using namespace std;

long long ans, n, m;

int main()
{
	scanf("%lld%lld", &n, &m);
	if (n == m) ans = n * n - 1;
	else ans = (n - 1) * (m - 1);
	printf("%lld\n", ans / 4);
	
	return 0;
}
