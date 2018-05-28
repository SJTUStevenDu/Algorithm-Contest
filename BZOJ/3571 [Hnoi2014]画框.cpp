#include <iostream>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <cmath>
#include <algorithm>

using namespace std;

const int MAXN = 200 + 10;
const int MAXM = 20000 + 10;
const int INF = 0x7FFFFFFF >> 2;

struct Edge
{
	int next, to, w, cost;
} g[MAXM];
int gn, start[MAXN];

inline void AddEdge(int a, int b, int c, int d)
{
	gn++; g[gn].next = start[a]; start[a] = gn; g[gn].to = b; g[gn].w = c; g[gn].cost = d;
	gn++; g[gn].next = start[b]; start[b] = gn; g[gn].to = a; g[gn].w = 0; g[gn].cost = -d;
}

struct Point
{
	int x, y;
	Point (int _x = 0, int _y = 0) : x(_x), y(_y) {}
	Point operator -(const Point &t) const{
		return Point(x - t.x, y - t.y);
	}
};

int n, m, S, T, c[MAXN][MAXN], a[MAXN][MAXN], b[MAXN][MAXN], tst, sa, sb, ans;
int dist[MAXN], q[MAXN], head, tail, path[MAXN];
bool vis[MAXN];

bool SPFA()
{
	memset(dist, 63, sizeof(dist));
	memset(vis, 0, sizeof(vis));
	q[head = 0] = S; tail = 1; vis[S] = 1; dist[S] = 0;
	while (head != tail)
	{
		int p = q[head++];
		if (head == MAXN) head = 0;
		vis[p] = 0;
		for (int i = start[p]; i; i = g[i].next) if(g[i].w > 0)
		{
			int v = g[i].to;
			if (dist[v] > dist[p] + g[i].cost)
			{
				dist[v] = dist[p] + g[i].cost;
				path[v] = i;
				if (!vis[v])
				{
					vis[v] = 1;
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
	return dist[T] < INF;
}

void Aug()
{
	int now = T;
	while (now != S)
	{
		int i = path[now];
		g[i].w--; g[i ^ 1].w++;
		now = g[i ^ 1].to;
	}
}

int mcmf()
{
	int ret = sa = sb = 0;
	memset(start, 0, sizeof(start));
	gn = 1;
	for (int i = 1; i <= n; ++i) AddEdge(S, i, 1, 0);
	for (int i = 1; i <= n; ++i) AddEdge(i + n, T, 1, 0);
	for (int i = 1; i <= n; ++i)
		for (int j = 1; j <= n; ++j) AddEdge(i, j + n, 1, c[i][j]);
	while (SPFA()) ret += dist[T], Aug();
	for (int i = 1; i <= n; ++i)
		for (int j = start[i]; j; j = g[j].next)
			if (g[j].w == 0 && g[j].to != S)
			{
				sa += a[i][g[j].to - n];
				sb += b[i][g[j].to - n];
			}
	ans = min(ans, sa * sb);
	return ret;
}

void calc(Point A, Point B)
{
	Point T = A - B;
	for (int i = 1; i <= n; ++i)
		for (int j = 1; j <= n; ++j) 
			c[i][j] = T.y * a[i][j] - T.x * b[i][j];
	if (mcmf() - B.x * T.y + B.y * T.x == 0) return;
	Point C = Point(sa, sb);
	calc(A, C);
	calc(C, B);
}

int main()
{
	scanf("%d", &tst);
	while (tst--)
	{
		scanf("%d", &n);
		S = 2 * n + 1; T = S + 1;
		for (int i = 1; i <= n; ++i) 
			for (int j = 1; j <= n; ++j) scanf("%d", &a[i][j]);
		for (int i = 1; i <= n; ++i)
			for (int j = 1; j <= n; ++j) scanf("%d", &b[i][j]);
		ans = INF;
		for (int i = 1; i <= n; ++i) 
			for (int j = 1; j <= n; ++j) c[i][j] = a[i][j];
		mcmf();
		Point A = Point(sa, sb);
		for (int i = 1; i <= n; ++i)
			for (int j = 1; j <= n; ++j) c[i][j] = b[i][j];
		mcmf();
		Point B = Point(sa, sb);
		calc(A, B);
		printf("%d\n", ans);
	}
	
	return 0;
}
