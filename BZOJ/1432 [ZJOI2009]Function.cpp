#include <iostream>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <cmath>
#include <fstream>
#include <algorithm>

using namespace std;

int n, k;

int main()
{
	scanf("%d%d", &n, &k);
	if (n == 1) puts("1");
	else printf("%d\n", 2 * min(k, n - k + 1));
	
	return 0;
}
