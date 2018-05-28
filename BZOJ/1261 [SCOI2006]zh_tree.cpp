#include <iostream>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <algorithm>
#include <cmath>

using namespace std;

const int MAXN = 30 + 10;
const double INF = 1e20;

double f[MAXN][MAXN][MAXN];
double a[MAXN];
int n;
double k, c, s;
bool v[MAXN][MAXN][MAXN];

double calc(int l, int r, int dep)
{
	if (l > r) return 0;
	if (v[l][r][dep]) return f[l][r][dep];
	double h = k * dep + c;
	v[l][r][dep] = 1;
	if (l == r)
	{
		f[l][r][dep] = h * a[l];
		return f[l][r][dep];
	}
	double res = INF;
	for (int i = l; i <= r; ++i) res = min(res, calc(l, i - 1, dep + 1) + calc(i + 1, r, dep + 1) + h * a[i]);
	return f[l][r][dep] = res;
}

int main()
{
	scanf("%d%lf%lf", &n, &k, &c);
	for (int i = 1; i <= n; ++i) scanf("%lf", &a[i]), s += a[i];
	for (int i = 1; i <= n; ++i) a[i] = a[i] / s;
	printf("%.3lf\n", calc(1, n, 1));
	
	return 0;
}
