#include <iostream>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <cmath>
#include <fstream>
#include <algorithm>

using namespace std;

const double eps = 1e-8;

struct Point 
{
	double x, y;
} A, B, C, D;

double p, q, m;

inline double dist(Point A, Point B)
{
	return sqrt((A.x - B.x) * (A.x - B.x) + (A.y - B.y) * (A.y - B.y));
}

inline double calc(Point S)
{
	Point l, r, mid1, mid2;
	double x, y;
	l = A; r = B;
	while (dist(l, r) > eps)
	{
		double dx = (r.x - l.x) / 3, dy = (r.y - l.y) / 3;
		mid1.x = l.x + dx; mid1.y = l.y + dy;
		mid2.x = r.x - dx; mid2.y = r.y - dy;
		x = dist(A, mid1) / p + dist(mid1, S) / m;
		y = dist(A, mid2) / p + dist(mid2, S) / m;
		if (x < y) r = mid2; else l = mid1;
	}
	if (dist(A, B) < eps) return dist(A, S) / m;
	else return x;
}

int main()
{
	scanf("%lf%lf%lf%lf%lf%lf%lf%lf", &A.x, &A.y, &B.x, &B.y, &C.x, &C.y, &D.x, &D.y);
	scanf("%lf%lf%lf", &p, &q, &m);
	Point l, r, mid1, mid2;
	double x, y;
	l = C; r = D;
	while (dist(l, r) > eps)
	{
		double dx = (r.x - l.x) / 3, dy = (r.y - l.y) / 3;
		mid1.x = l.x + dx; mid1.y = l.y + dy;
		mid2.x = r.x - dx; mid2.y = r.y - dy;
		x = calc(mid1) + dist(mid1, D) / q;
		y = calc(mid2) + dist(mid2, D) / q;
		if (x < y) r = mid2; else l = mid1;
	}
	if (dist(C, D) < eps) x = calc(C);
	printf("%.2lf\n", x);
	
	return 0;
}
