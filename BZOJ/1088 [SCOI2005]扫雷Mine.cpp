#include <iostream>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <cmath>
#include <algorithm>
#include <fstream>

using namespace std;

const int MAXN = 10000 + 10;

int n, ans;
int s[MAXN];
int a[MAXN];

bool check()
{
	for (int i = 2; i < n; ++i) a[i + 1] = s[i] - a[i] - a[i - 1];
	for (int i = 1; i <= n; ++i) if (a[i] < 0) return false;
	if (s[n] != a[n] + a[n - 1]) return false;
	return true;
}

int main()
{
	scanf("%d", &n);
	for (int i = 1; i <= n; ++i) scanf("%d", &s[i]);
	a[1] = a[2] = 1;
	if (a[1] + a[2] == s[1]) ans += check();
	a[1] = a[2] = 0;
	if (a[1] + a[2] == s[1]) ans += check();
	a[1] = 0; a[2] = 1;
	if (a[1] + a[2] == s[1]) ans += check();
	a[1] = 1; a[2] = 0;
	if (a[1] + a[2] == s[1]) ans += check();
	printf("%d\n", ans);
	
	return 0;
}
