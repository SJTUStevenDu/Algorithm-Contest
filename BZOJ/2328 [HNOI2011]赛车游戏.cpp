#include <iostream>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <algorithm>
#include <cmath>

using namespace std;

const int MAXN = 10000 + 10;
const double eps = 1e-13;

struct Node
{
	double speed, dist, k;
} l[MAXN];

bool cmp(Node A, Node B)
{
	return A.speed < B.speed;
}

int checkdouble(double x)
{
	if (fabs(x) < eps) return 0;
	else if (x > eps) return 1;
	else return -1;
}

double a, b, vmax, o;
int T, n;
bool upp;

void work()
{
	sort(l + 1, l + 1 + n, cmp);
	double nowd = l[1].dist, nowv = l[1].speed;
	for (int i = 2; i <= n; ++i)
	{
		double dd = (l[i].speed - nowv) * a * nowd;
		if (checkdouble (o - dd) <= 0)
		{
			nowv += o / a / nowd;
			double ans = nowd / nowv;
			for (int j = i; j <= n; ++j) ans += l[j].dist / l[j].speed;
			printf("%.5lf\n", ans);
			return;
		}
		o -= dd; nowv = l[i].speed; nowd += l[i].dist;
	}
	nowv = min(vmax, nowv + o / a / nowd);
	printf("%.5lf\n", nowd / nowv);
}

int main()
{
	scanf("%d", &T);
	while (T--)
	{
		scanf("%lf%lf%lf%lf", &a, &b, &vmax, &o);
		scanf("%d", &n);
		upp = false;
		for (int i = 1; i <= n; ++i) 
		{
			double dx, dy;
			scanf("%lf%lf", &dx, &dy);
			dx /= 1000; dy /= 1000;
			l[i].dist = sqrt(dx * dx + dy * dy);
			l[i].k = dy / dx;
			if (checkdouble(l[i].k) >= 0) l[i].speed = 0, upp = true;
			else l[i].speed = min(-l[i].k * b / a, vmax);
		}
		for (int i = 1; i <= n; ++i) o -= max(a * l[i].speed + b * l[i].k, 0.0) * l[i].dist;
		if (checkdouble(o) < 0 || (checkdouble(o) == 0 && upp)) puts("IMPOSSIBLE");
		else work();
	}
	
	return 0;
}
