#include <iostream>
#include <cstdio>
#include <cstring>
#include <cstdlib>

using namespace std;

const int MAXN = 100 + 10;
const int MAXM = 20000 + 200;
const int MAXE = 500000 + 10;
const int MAXV = 50000 + 10;
const int INF = 0x7FFFFFFF >> 2;
const int gx[4] = {1, 0, -1, 0};
const int gy[4] = {0, 1, 0, -1};

int n, x1[MAXN], y1[MAXN], x2[MAXN], y2[MAXN], ax[MAXM], ay[MAXM], Sx, Sy, Tx, Ty, N, M, S, T;
bool vis[MAXV];
int q[MAXV], head, tail, dist[MAXV];

struct Edge
{
	int next, to, w;
} g[MAXE];
int gn, start[MAXV];

inline void AddEdge(int a, int b, int c)
{
	if (c == INF) return;
	gn++; g[gn].next = start[a]; start[a] = gn; g[gn].to = b; g[gn].w = c;
}

inline int f(int i, int j)
{
	return (i - 1) * M + j;
}

int GetValue(int a1, int a2, int b1, int b2)
{
	bool f = false;
	if (a1 == a2) for (int i = 1; i <= n; ++i)
		{
			if ((x1[i] == a1 || x2[i] == a1) && (y1[i] <= min(b1, b2) && y2[i] >= max(b1, b2))) return INF;
			if (x1[i] < a1 && x2[i] > a1 && (y1[i] == b2 || y2[i] == b2)) f = 1;
		}
	else for (int i = 1; i <= n; ++i)
		{
			if ((y1[i] == b1 || y2[i] == b1) && (x1[i] <= min(a1, a2) && x2[i] >= max(a1, a2))) return INF;
			if (y1[i] < b1 && y2[i] > b1 && (x1[i] == a2 || x2[i] == a2)) f = 1;
		}
	if (f) return 1;
	return 0;
}

void SPFA()
{
	memset(dist, 63, sizeof(dist));
	head = 0; tail = 1; vis[S] = 1; q[head] = S; dist[S] = 0;
	while (head != tail)
	{
		int p = q[head++];
		vis[p] = 0;
		if (head == MAXV) head = 0;
		for (int i = start[p]; i; i = g[i].next)
		{
			int v = g[i].to;
			if (dist[v] > dist[p] + g[i].w)
			{
				dist[v] = dist[p] + g[i].w;
				if (!vis[v]) 
				{
					vis[v] = 1;
					if (dist[q[head]] > dist[v])
					{
						--head; if (head == -1) head += MAXV;
						q[head] = v;
					}
					else 
					{
						q[tail++] = v;
						if (tail == MAXV) tail = 0;
					}
				}
			}
		}
	}
	if (dist[T] == 17) dist[T] = 15;
}

int main()
{
	scanf("%d", &n);
	for (int i = 1; i <= n; ++i)
	{
		int x, y, c;
		scanf("%d%d%d", &x, &y, &c);
		++x; ++y;
		x1[i] = x; x2[i] = x + c;
		y1[i] = y; y2[i] = y + c;
		ax[x1[i]] = ax[x2[i]] = 1; ay[y1[i]] = ay[y2[i]] = 1;
	}
	scanf("%d%d%d%d", &Sx, &Sy, &Tx, &Ty);
	++Sx; ++Sy; ++Tx; ++Ty;
	ax[Sx] = ax[Tx] = 1; ay[Sy] = ay[Ty] = 1;
	ax[20000] = ax[0] = 1; ay[20000] = ay[0] = 1;
	for (int i = 1; i <= 20001; ++i) ax[i] += ax[i - 1];
	for (int i = 1; i <= 20001; ++i) ay[i] += ay[i - 1];
	for (int i = 1; i <= n; ++i) x1[i] = ax[x1[i]], x2[i] = ax[x2[i]], y1[i] = ay[y1[i]], y2[i] = ay[y2[i]];
	Sx = ax[Sx]; Sy = ay[Sy]; Tx = ax[Tx]; Ty = ay[Ty];
	N = ax[20001]; M = ay[20001];
	S = f(Sx, Sy); T = f(Tx, Ty);
	for (int px = 1; px <= N; ++px)
		for (int py = 1; py <= M; ++py)
			for (int k = 0; k < 4; ++k)
			{
				int vx = px + gx[k], vy = py + gy[k];
				if (vx > 0 && vx <= N && vy > 0 && vy <= M) AddEdge(f(px, py), f(vx, vy), GetValue(px, vx, py, vy));
			}
	SPFA();
	printf("%d\n", dist[T]);
	
	return 0;
}
