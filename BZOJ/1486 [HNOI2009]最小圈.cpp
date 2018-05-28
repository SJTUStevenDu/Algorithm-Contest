#include <iostream>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <algorithm>
#include <cmath>

using namespace std;

const int MAXN = 3000 + 10;
const int MAXM = 10000 + 10;
const double eps = 1e-9;

struct Edge
{
	int next, to;
	double w;
} g[MAXM];
int gn, start[MAXN];

inline void AddEdge(int a, int b, double c)
{
	gn++; g[gn].next = start[a]; start[a] = gn; g[gn].to = b; g[gn].w = c;
}

double dist[MAXN], c;
int n, m, a, b, q[MAXN], head, tail;
bool vis[MAXN];

bool check(double x)
{
	int T = 0;
	memset(vis, 0, sizeof(vis));
	for (int i = 1; i <= n; ++i) dist[i] = 1e20;
	dist[1] = 0; vis[1] = 1; q[head = 0] = 1; tail = 1;
	while (head != tail)
	{
		int p = q[head++];
		if (head == MAXN) head = 0;
		vis[p] = 0;
		for (int i = start[p]; i; i = g[i].next)
		{
			int v = g[i].to;
			if (dist[v] > dist[p] + g[i].w - x)
			{
				dist[v] = dist[p] + g[i].w - x;
				if (!vis[v])
				{
					vis[v] = 1;
					++T;
					if (T > 100000) return true;
					if (dist[q[head]] < dist[v])
					{
						q[tail++] = v;
						if (tail == MAXN) tail = 0;
					}
					else 
					{
						--head; if (head == -1) head += MAXN;
						q[head] = v;
					}
				}
			}
		}
	}
	return false;
}

int main()
{
	scanf("%d%d", &n, &m);
	for (int i = 1; i <= m; ++i)
	{
		scanf("%d%d%lf", &a, &b, &c);
		AddEdge(a, b, c);
	}
	double l = -1e7, r = 1e7;
	while (r - l > eps)
	{
		double mid = (l + r) / 2;
		if (check(mid)) r = mid;
		else l = mid;
	}
	printf("%.8lf\n", l);
	
	return 0;
}
