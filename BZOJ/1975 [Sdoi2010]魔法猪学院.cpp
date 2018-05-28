#include <iostream>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <cmath>
#include <fstream>
#include <algorithm>

using namespace std;

const int MAXN = 5000 + 10;
const int MAXM = 200000 + 10;
const double INF = 1e50;

struct Edge
{
	int next, to;
	double w;
} g[MAXM];
int gn, start[MAXN];

inline void AddEdge(int a, int b, double c)
{
	gn++; g[gn].next = start[a]; start[a] = gn; g[gn].w = c; g[gn].to = b;
}

struct Map
{
	int a, b; double c;
} e[MAXM];

int n, m, ans;
double dist[MAXN];
double Limit;

struct Node {int pos; double w;};

struct Heapp
{
	Node a[MAXM * 10];
	int tot;
	void Up(int x)
	{
		while (x > 1 && a[x].w < a[x / 2].w) swap(a[x], a[x / 2]), x /= 2;
	}
	void Down(int x)
	{
		while (x * 2 <= tot)
		{
			int tmp = x * 2;
			if (tmp + 1 <= tot && a[tmp].w > a[tmp + 1].w) tmp++;
			if (a[tmp].w < a[x].w) swap(a[x], a[tmp]), x = tmp;
			else break;
		}
	}
	void Insert(double x, int p)
	{
		if (x > Limit) return;
		++tot; a[tot].w = x; a[tot].pos = p; Up(tot);
	}
	void Delete(int p)
	{
		swap(a[p], a[tot]);
		--tot;
		Up(p); Down(p);
	}
} Heap;

int q[MAXN], head, tail;
bool vis[MAXN];

void SPFA()
{
	for (int i = 1; i <= n; ++i) dist[i] = INF;
	head = 0; q[head] = n; dist[n] = 0; tail = 1; vis[n] = 1;
	while (head != tail)
	{
		int p = q[head++];
		if (head == MAXN) head = 0;
		vis[p] = 0;
		for (int i = start[p]; i; i = g[i].next)
		{
			int v = g[i].to;
			if (dist[v] > dist[p] + g[i].w)
			{
				dist[v] = dist[p] + g[i].w;
				if (!vis[v])
				{
					vis[v] = 1;
					if (dist[v] > dist[q[head]])
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
}

int main()
{
	scanf("%d%d%lf", &n, &m, &Limit);
	for (int i = 1; i <= m; ++i) scanf("%d%d%lf", &e[i].a, &e[i].b, &e[i].c);
	for (int i = 1; i <= m; ++i) AddEdge(e[i].b, e[i].a, e[i].c);
	SPFA();
	memset(start, 0, sizeof(start));
	gn = 0;
	for (int i = 1; i <= m; ++i) AddEdge(e[i].a, e[i].b, e[i].c);
	Heap.tot = 0;
	Heap.Insert(dist[1], 1);
	Node T;
	while (Heap.tot && Heap.a[1].w <= Limit)
	{
		T = Heap.a[1];
		Heap.Delete(1);
		if (T.pos == n)
		{
			++ans;
			Limit -= T.w;
		}
		else for (int i = start[T.pos]; i; i = g[i].next) Heap.Insert(T.w + g[i].w - dist[T.pos] + dist[g[i].to], g[i].to);
	}
	printf("%d\n", ans);
	
	return 0;
}
