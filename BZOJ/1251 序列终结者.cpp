#include <iostream>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <cmath>
#include <fstream>
#include <algorithm>

using namespace std;

const int MAXN = 50000 + 10;
const int INF = 0x7FFFFFFF >> 2;

struct Splay_Tree
{
	int left, right, size, fa, maxv, add, data;
	bool rev;
} spl[MAXN];

int n, m, pn, ro;

inline void Pushup(int p);
inline void Pushdown(int p);

inline void NewNode(int &p, int f, int d)
{
	p = ++pn;
	spl[p].left = spl[p].right = 0;
	spl[p].size = 1;
	spl[p].fa = f;
	spl[p].data = spl[p].maxv = d;
	spl[p].add = 0;
	spl[p].rev = false;
}

inline void Left_Rotate(int p)
{
	int k = spl[p].right;
	spl[p].right = spl[k].left;
	spl[spl[k].left].fa = p;
	spl[k].left = p;
	if (spl[p].fa) 
	{
		if (spl[spl[p].fa].left == p) spl[spl[p].fa].left = k;
		else spl[spl[p].fa].right = k;
	}
	spl[k].fa = spl[p].fa;
	spl[p].fa = k;
	Pushup(p);
	Pushup(k);
}

inline void Right_Rotate(int p)
{
	int k = spl[p].left;
	spl[p].left = spl[k].right;
	spl[spl[k].right].fa = p;
	spl[k].right = p;
	if (spl[p].fa)
	{
		if (spl[spl[p].fa].left == p) spl[spl[p].fa].left = k;
		else spl[spl[p].fa].right = k;
	}
	spl[k].fa = spl[p].fa;
	spl[p].fa = k;
	Pushup(p);
	Pushup(k);
}

void Splay(int p, int g)
{
	for (Pushdown(p); spl[p].fa != g;)
	{
		Pushdown(spl[p].fa);
		Pushdown(p);
		if (spl[spl[p].fa].fa == g)
		{
			if (spl[spl[p].fa].left == p) Right_Rotate(spl[p].fa);
			else Left_Rotate(spl[p].fa);
		}
		else if ((spl[spl[spl[p].fa].fa].left == spl[p].fa) ^ (spl[spl[p].fa].left == p))
		{
			if (spl[spl[p].fa].left == p) Right_Rotate(spl[p].fa), Left_Rotate(spl[p].fa);
			else Left_Rotate(spl[p].fa), Right_Rotate(spl[p].fa);
		}
		else 
		{
			if (spl[spl[p].fa].left == p) Right_Rotate(spl[spl[p].fa].fa), Right_Rotate(spl[p].fa);
			else Left_Rotate(spl[spl[p].fa].fa), Left_Rotate(spl[p].fa);
		}
	}
	if (!g) ro = p;
}

void Rotate_to(int k, int g)
{
	int p = ro;
	Pushdown(p);
	while (spl[spl[p].left].size != k - 1)
	{
		Pushdown(p);
		if (spl[spl[p].left].size < k - 1) k -= spl[spl[p].left].size + 1, p = spl[p].right;
		else p = spl[p].left;
	}
	Splay(p, g);
}

inline void Reverse(int p)
{
	if (!p) return;
	spl[p].rev ^= 1;
	swap(spl[p].left, spl[p].right);
}

inline void Add(int p,int d)
{
	if (!p) return;
	spl[p].data += d;
	spl[p].add += d;
	spl[p].maxv += d;
}

inline void Pushup(int p)
{
	if (!p) return;
	spl[p].size = spl[spl[p].left].size + spl[spl[p].right].size + 1;
	spl[p].maxv = max(spl[spl[p].left].maxv, max(spl[p].data, spl[spl[p].right].maxv));
}

inline void Pushdown(int p)
{
	if (!p) return;
	if (spl[p].add)
	{
		Add(spl[p].left, spl[p].add);
		Add(spl[p].right, spl[p].add);
		spl[p].add = 0;
	}
	if (spl[p].rev)
	{
		Reverse(spl[p].left);
		Reverse(spl[p].right);
		spl[p].rev = false;
	}
}

void Build(int &p, int l, int r, int f)
{
	int mid = (l + r) >> 1;
	NewNode(p, f, 0);
	if (l < mid) Build(spl[p].left, l, mid - 1, p);
	if (r > mid) Build(spl[p].right, mid + 1, r, p);
	Pushup(p);
}

int main()
{
	spl[0].maxv = -INF;
	NewNode(ro, 0, INF);
	NewNode(spl[ro].right, ro, INF);
	Pushup(ro);
	scanf("%d%d", &n, &m);
	Build(spl[spl[ro].right].left, 1, n, spl[ro].right);
	Splay(spl[spl[ro].right].left, 0);
	while (m--)
	{
		int opr, l, r, d;
		scanf("%d%d%d", &opr, &l, &r);
		Rotate_to(l, 0);
		Rotate_to(r + 2, ro);
		int p = spl[spl[ro].right].left;
		if (opr == 1)
		{
			scanf("%d", &d);
			Add(p, d);
		}
		if (opr == 2) Reverse(p);
		if (opr == 3) printf("%d\n", spl[p].maxv);
		Splay(p, 0);
	}
	
	return 0;
}
