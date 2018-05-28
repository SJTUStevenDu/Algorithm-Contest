#include <iostream>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <cmath>
#include <fstream>
#include <algorithm>

using namespace std;

const int MAXN = 1000000 + 10;
const int MOD = 1000000007;

int f[MAXN], n;

int main()
{
	scanf("%d", &n);
	f[0] = 0; f[1] = 1;
	for (int i = 2; i <= n; ++i) f[i] = (2 * f[i - 1] % MOD + f[i - 2] % MOD) % MOD;
	printf("%d\n", f[n]);
	
	return 0;
}
