#include <iostream>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <cmath>
#include <fstream>
#include <algorithm>

using namespace std;

const int MAXN = 100000 + 10;

struct Size_Balanced_Tree
{
	int left, right, data, size;
} tree[MAXN * 40];

int n, Q, father[MAXN], m, root[MAXN], w[MAXN], pn, bb[MAXN];

inline void Left_Rotate(int &p)
{
	int k = tree[p].right;
	tree[p].right = tree[k].left;
	tree[k].left = p;
	tree[k].size = tree[p].size;
	tree[p].size = tree[tree[p].left].size + tree[tree[p].right].size + 1;
	p = k;
}

inline void Right_Rotate(int &p)
{
	int k = tree[p].left;
	tree[p].left = tree[k].right;
	tree[k].right = p;
	tree[k].size = tree[p].size;
	tree[p].size = tree[tree[p].left].size + tree[tree[p].right].size + 1;
	p = k;
}

void Maintain(int &p, bool flag)
{
	if (!flag)
	{
		if (tree[tree[tree[p].left].left].size > tree[tree[p].right].size) Right_Rotate(p);
		else if (tree[tree[tree[p].left].right].size > tree[tree[p].right].size) Left_Rotate(tree[p].left), Right_Rotate(p);
		else return;
	}
	else 
	{
		if (tree[tree[tree[p].right].right].size > tree[tree[p].left].size) Left_Rotate(p);
		else if (tree[tree[tree[p].right].left].size > tree[tree[p].left].size) Right_Rotate(tree[p].right), Left_Rotate(p);
		else return;
	}
	Maintain(tree[p].left, 0);
	Maintain(tree[p].right, 1);
	Maintain(p, 0);
	Maintain(p, 1);
}

void Insert(int &p, int v)
{
	if (!p)
	{
		p = ++pn;
		tree[p].left = tree[p].right = 0;
		tree[p].size = 1;
		tree[p].data = v;
		return;
	}
	tree[p].size++;
	if (v < tree[p].data) Insert(tree[p].left, v);
	else Insert(tree[p].right, v);
	Maintain(p, v >= tree[p].data);
}

int Find_Kth(int p, int k)
{
	if (tree[p].size < k) return 0;
	while (p)
	{
		if (tree[tree[p].left].size + 1 == k) return tree[p].data;
		if (tree[tree[p].left].size + 1 > k) p = tree[p].left;
		else k -= tree[tree[p].left].size + 1, p = tree[p].right;
	}
}

int getfather(int x)
{
	return father[x] == x ? x : father[x] = getfather(father[x]);
}

void Union(int &p, int q)
{	
	Insert(p, tree[q].data);
	if (tree[q].left) Union(p, tree[q].left);
	if (tree[q].right) Union(p, tree[q].right);
}

int main()
{
	scanf("%d%d", &n, &m);
	for (int i = 1; i <= n; ++i) scanf("%d", &w[i]), father[i] = i, bb[w[i]] = i;
	bb[0] = -1;
	for (int a, b, i = 1; i <= m; ++i)
	{
		scanf("%d%d", &a, &b);
		a = getfather(a); b = getfather(b);
		if (a != b) father[b] = a;
	}
	for (int i = 1; i <= n; ++i) Insert(root[getfather(i)], w[i]);
	scanf("%d", &Q);
	while (Q--)
	{
		char opr[5];
		int x, y;
		scanf("%s%d%d", opr, &x, &y);
		if (opr[0] == 'B')
		{
			x = getfather(x); y = getfather(y);
			if (x == y) continue;
			if (tree[root[x]].size < tree[root[y]].size) swap(x, y);
			father[y] = x;	
			Union(root[x], root[y]);
		}
		else printf("%d\n", bb[Find_Kth(root[getfather(x)], y)]);
	}
	
	return 0;
}
