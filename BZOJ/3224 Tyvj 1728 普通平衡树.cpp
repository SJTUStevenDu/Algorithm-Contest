#include <iostream>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <algorithm>
#include <cmath>

using namespace std;

const int MAXN = 100000 + 10;
const int INF = 0x7FFFFFFF >> 2;

struct Size_Balanced_Tree
{
	int left, right, size, data;
} tree[MAXN];

int stk[MAXN], Top, ro, sum, n, opr, x;

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
		p = stk[Top--];
		tree[p].left = tree[p].right = 0;
		tree[p].size = 1; tree[p].data = v;
		return;
	}
	tree[p].size++;
	if (v < tree[p].data) Insert(tree[p].left, v);
	else Insert(tree[p].right, v);
	Maintain(p, v >= tree[p].data);
}

int Delete(int &p, int v)
{
	int k = tree[p].data;
	tree[p].size--;
	if (v == k || (v < k && !tree[p].left) || (v > k && !tree[p].right))
	{
		if (!tree[p].left || !tree[p].right)
		{
			stk[++Top] = p;
			p = tree[p].left + tree[p].right;
		}
		else tree[p].data = Delete(tree[p].left, v + 1);
		return k;
	}
	else 
	{
		if (v < k) return Delete(tree[p].left, v);
		else return Delete(tree[p].right, v);
	}
}

int Getpred(int v)
{
	int ret = -INF, p = ro;
	while (p)
	{
		if (tree[p].data < v) ret = max(ret, tree[p].data);
		if (tree[p].data < v) p = tree[p].right;
		else p = tree[p].left;
	}
	return ret;
}

int Getsucc(int v)
{
	int ret = INF, p = ro;
	while (p)
	{
		if (tree[p].data > v) ret = min(ret, tree[p].data);
		if (tree[p].data > v) p = tree[p].left;
		else p = tree[p].right;
	}
	return ret;
}

int Find_Kth(int k)
{
	int p = ro;
	while (p)
	{
		if (tree[tree[p].left].size + 1 == k) return tree[p].data;
		if (tree[tree[p].left].size + 1 > k) p = tree[p].left;
		else k -= tree[tree[p].left].size + 1, p = tree[p].right;
	}
}

void Get_Rank(int p, int v)
{
	if (tree[p].data < v)
	{
		sum += tree[tree[p].left].size + 1;
		if (tree[p].right) Get_Rank(tree[p].right, v);
		return;
	}
	if (tree[p].left) Get_Rank(tree[p].left, v);
}

int Find_Rank(int v)
{
	sum = 0;
	Get_Rank(ro, v);
	return sum + 1;
}

int main()
{
	for (int i = 1; i < MAXN; ++i) stk[++Top] = i;
	scanf("%d", &n);
	while (n--)
	{
		scanf("%d%d", &opr, &x);
		if (opr == 1) Insert(ro, x);
		if (opr == 2) Delete(ro, x);
		if (opr == 3) printf("%d\n", Find_Rank(x));
		if (opr == 4) printf("%d\n", Find_Kth(x));
		if (opr == 5) printf("%d\n", Getpred(x));
		if (opr == 6) printf("%d\n", Getsucc(x));
	}
	
	return 0;
}
