#include <iostream>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <cmath>
#include <algorithm>
#include <fstream>

using namespace std;

const int MAXN = 100000 + 10;
const int MAXM = 300000 + 10;
const int head = -1;
const int tail = -2;
const int INF = 0x7FFFFFFF >> 2;

bool vis[MAXN], color[MAXN];

struct Edge
{
	int next, to;
} g[MAXN * 2];
int gn, start[MAXN];

inline void AddEdge(int a, int b)
{
	gn++; g[gn].next = start[a]; start[a] = gn; g[gn].to = b;
}

int n, seq[MAXM], pos[MAXN], num, Q, tot;
char opr[10];

void dfs(int p)
{
	vis[p] = 1;
	seq[++tot] = head;
	seq[++tot] = p;
	pos[p] = tot;
	for (int i = start[p]; i; i = g[i].next)
	{
		int v = g[i].to;
		if (!vis[v]) dfs(v);
	}
	seq[++tot] = tail;
}

struct Seg_Tree
{
	int left, right, dist, left_plus, left_minus, right_plus, right_minus;
} seg[MAXM << 2];

void Modify_Point(int p, int x)
{
	if (seq[x] == head) seg[p].left = 1;
	else if (seq[x] == tail) seg[p].right = 1;
	seg[p].dist = -INF;
	seg[p].left_minus = seg[p].left_plus = seg[p].right_minus = seg[p].right_plus = (seq[x] >= 0 && color[seq[x]] == 0) ? 0 : -INF;
}

void Pushup(int p)
{
	seg[p].left = seg[p << 1 | 1].left + max(seg[p << 1].left - seg[p << 1 | 1].right, 0);
	
	seg[p].right = seg[p << 1].right + max(seg[p << 1 | 1].right - seg[p << 1].left, 0);
	
	seg[p].dist = max(max(seg[p << 1].dist, seg[p << 1 | 1].dist), max(seg[p << 1].right_plus + seg[p << 1 | 1].left_minus, seg[p << 1].right_minus + seg[p << 1 | 1].left_plus));

	seg[p].left_plus = max(seg[p << 1].left_plus, max(seg[p << 1 | 1].left_plus + seg[p << 1].right - seg[p << 1].left, seg[p << 1 | 1].left_minus + seg[p << 1].right + seg[p << 1].left));
	
	seg[p].left_minus = max(seg[p << 1].left_minus, seg[p << 1 | 1].left_minus - seg[p << 1].right + seg[p << 1].left);
	
	seg[p].right_plus = max(seg[p << 1 | 1].right_plus, max(seg[p << 1].right_plus - seg[p << 1 | 1].right + seg[p << 1 | 1].left, seg[p << 1].right_minus + seg[p << 1 | 1].right + seg[p << 1 | 1].left));
	
	seg[p].right_minus = max(seg[p << 1 | 1].right_minus, seg[p << 1].right_minus + seg[p << 1 | 1].right - seg[p << 1 | 1].left);
}

void Build(int p, int l, int r)
{
	if (l == r) Modify_Point(p, l);
	else 
	{
		int mid = (l + r) >> 1;
		Build(p << 1, l, mid);
		Build(p << 1 | 1, mid + 1, r);
		Pushup(p);
	}
}

void Update(int p, int l, int r, int x)
{
	if (l == r) Modify_Point(p, x);
	else 
	{
		int mid = (l + r) >> 1;
		if (x <= mid) Update(p << 1, l, mid, x);
		else if (x > mid) Update(p << 1 | 1, mid + 1, r, x);
		Pushup(p);
	}
}

int main()
{
	scanf("%d", &n);
	for (int a, b, i = 1; i < n; ++i) 
	{
		scanf("%d%d", &a, &b);
		AddEdge(a, b);
		AddEdge(b, a);
	}
	dfs(1);
	num = n;
	Build(1, 1, tot);
	scanf("%d", &Q);
	while (Q--)
	{
		scanf("%s", opr);
		if (opr[0] == 'G') 
		{
			if (num == 0) puts("-1");
			else if (num == 1) puts("1");
			else printf("%d\n", seg[1].dist);
		}
		else 
		{
			int x;
			scanf("%d", &x);
			color[x] = 1 - color[x];
			if (color[x]) num--; else ++num;
			Update(1, 1, tot, pos[x]);
		}
	}
	
	return 0;
}
