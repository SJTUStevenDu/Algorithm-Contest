#include <iostream>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <cmath>
#include <algorithm>
#include <set>
#include <fstream>

using namespace std;

const int MAXN = 500000 + 10;

struct Range
{
	int l, r;
} R[MAXN];

int n, m, minx, l, r;
multiset <int> k1;
multiset <int> k2;
char opr[20];

void Checkmin(int x)
{
	if (x >= r) minx = min(minx, x - r);
	if (x <= l) minx = min(minx, l - x);
	else 
	{
		set<int>::iterator i = k2.lower_bound(x);
		minx = min(minx, abs(*i - x));
		--i;
		minx = min(minx, abs(*i - x));
	}
}

int main()
{
	scanf("%d%d", &n, &m);
	for (int i = 1; i <= n; ++i) scanf("%d", &R[i].l), R[i].r = R[i].l;
	l = r = R[1].l;
	k2.insert(R[1].l);
	minx = 0x7FFFFFFF >> 1;
	for (int i = 2; i <= n; ++i)
	{
		k1.insert(abs(R[i].l - R[i - 1].r));
		Checkmin(R[i].l);
		l = min(l, R[i].l);
		r = max(r, R[i].r);
		k2.insert(R[i].l);
	}
	while (m--)
	{
		scanf("%s", opr);
		if (opr[0] == 'I')
		{
			int i, k;
			scanf("%d%d", &i, &k);
			k1.erase(k1.find(abs(R[i + 1].l - R[i].r)));
			k1.insert(abs(R[i].r - k));
			k1.insert(abs(R[i + 1].l - k));
			Checkmin(k);
			l = min(l, k);
			r = max(r, k);
			k2.insert(k);
			R[i].r = k;
			
		}
		else if (opr[4] == 'S') printf("%d\n", minx);
		else printf("%d\n", *k1.begin());
	}
	
	
	return 0;
}
