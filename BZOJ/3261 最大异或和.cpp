#include <iostream>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <cmath>
#include <fstream>
#include <algorithm>

using namespace std;

const int MAXN = 600000 + 10;
const int MAXT = 15000000 + 10;

int root[MAXN], b[MAXN], c[MAXT][2], s[MAXT], tot, n, Q;

void Insert(int x, int &y, int v, int d)
{
	s[y = ++tot] = s[x] + 1;
	if (d < 0) return;
	int p = (v >> d) & 1;
	c[y][p ^ 1] = c[x][p ^ 1];
	Insert(c[x][p], c[y][p], v, d - 1);
}

int Query(int x, int y, int v, int d)
{
	if (d < 0) return 0;
	int p = (v >> d) & 1;
	if (s[c[y][p ^ 1]] - s[c[x][p ^ 1]]) return (1 << d) + Query(c[x][p ^ 1], c[y][p ^ 1], v, d - 1);
	return Query(c[x][p], c[y][p], v, d - 1); 
}

char opr[5];

int main()
{
	scanf("%d%d", &n, &Q);
	++n;
	Insert(root[0], root[1], 0, 24);
	for (int x, i = 2; i <= n; ++i) 
	{
		scanf("%d", &x);
		Insert(root[i - 1], root[i], b[i] = b[i - 1] ^ x, 24);
	}
	while (Q--)
	{
		scanf("%s", opr);
		if (opr[0] == 'A')
		{
			int x;
			scanf("%d", &x);
			++n;
			Insert(root[n - 1], root[n], b[n] = b[n - 1] ^ x, 24);
		}
		else
		{
			int l, r, x;
			scanf("%d%d%d", &l, &r, &x);
			printf("%d\n", Query(root[l - 1], root[r], b[n] ^ x, 24));
		}
	}
	
	return 0;
}
