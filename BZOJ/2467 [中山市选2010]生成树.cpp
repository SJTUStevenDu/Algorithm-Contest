#include <iostream>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <cmath>
#include <algorithm>
#include <fstream>

using namespace std;

const int MOD = 2007;

int T;
int n, ans;

int main()
{
	scanf("%d", &T);
	while (T--)
	{
		scanf("%d", &n);
		ans = 4 * n;
		for (int i = 1; i < n; ++i) ans = ans * 5 % MOD;
		printf("%d\n", ans);
	}
	
	return 0;
}
