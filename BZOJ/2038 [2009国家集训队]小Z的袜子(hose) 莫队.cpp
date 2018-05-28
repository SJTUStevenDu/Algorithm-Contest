#include <iostream>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <cmath>
#include <fstream>
#include <algorithm>

using namespace std;

const int MAXN = 50000 + 10;

struct Node 
{
	int l, r, idx;
	long long ans1, ans2;
} q[MAXN];

int c[MAXN], n, m;
long long s[MAXN];

bool cmp(Node A, Node B)
{
	int lim = (int)sqrt(n + 0.5);
	int xa = (A.l - 1) / lim + 1, xb = (B.l - 1) / lim + 1;
	return xa < xb || (xa == xb && A.r < B.r);
}

bool cmp_idx(Node A, Node B) {return A.idx < B.idx;}

long long gcd(long long n, long long m)
{
	long long tmp;
	while (m)
	{
		tmp = n % m;
		n = m;
		m = tmp;
	}
	return n;
}

long long cur;

void Modify(int p, int v)
{
	cur -= s[c[p]] * s[c[p]];
	s[c[p]] += v;
	cur += s[c[p]] * s[c[p]];
}

void solve()
{
	cur = 0;
	int head = 1, tail = 0;
	for (int i = 1; i <= m; ++i)
	{
		if (tail < q[i].r)
		{
			for (tail = tail + 1; tail <= q[i].r; ++tail) Modify(tail, 1);
			--tail;
		}
		if (tail > q[i].r)
		{
			for (; tail > q[i].r; --tail) Modify(tail, -1);
		}
		if (head < q[i].l)
		{
			for (; head < q[i].l; ++head) Modify(head, -1);
		}
		else if (head > q[i].l)
		{
			for (head = head - 1; head >= q[i].l; --head) Modify(head, 1);
			++head;
		}
		if (q[i].l == q[i].r)
		{
			q[i].ans1 = 0; q[i].ans2 = 1;
		}
		else 
		{
			q[i].ans1 = cur - (long long)(q[i].r - q[i].l + 1);
			q[i].ans2 = (long long)(q[i].r - q[i].l + 1) * (q[i].r - q[i].l);
		}
	}
}

int main()
{
	scanf("%d%d", &n, &m);
	for (int i = 1; i <= n; ++i) scanf("%d", &c[i]);
	for (int i = 1; i <= m; ++i) scanf("%d%d", &q[i].l, &q[i].r), q[i].idx = i;
	sort(q + 1, q + 1 + m, cmp);
	solve();
	sort(q + 1, q + 1 + m, cmp_idx);
	for (int i = 1; i <= m; ++i)
	{
		long long gg = gcd(q[i].ans1, q[i].ans2);
		printf("%lld/%lld\n", q[i].ans1 / gg, q[i].ans2 / gg);
	}
	
	return 0;
}
