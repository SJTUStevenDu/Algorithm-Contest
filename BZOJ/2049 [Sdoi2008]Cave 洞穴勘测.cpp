#include <iostream>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <cmath>
#include <fstream>
#include <algorithm>

using namespace std;

const int MAXN = 10000 + 10;

int father[MAXN], n, Q, x, y;
char opr[10];

int getfather(int x)
{
	return (father[x] == x) ? x : getfather(father[x]);
}

void dfs(int p)
{
	if (father[p] == p) return;
	dfs(father[p]);
	father[father[p]] = p;
	return;
}

int main()
{
	scanf("%d%d", &n, &Q);
	for (int i = 1; i <= n; ++i) father[i] = i;
	while (Q--)
	{
		scanf("%s", opr);
		scanf("%d%d", &x, &y);
		if (opr[0] == 'C')
		{
			dfs(x); dfs(y);
			father[y] = y;
			father[x] = y;
		}
		else if (opr[0] == 'D') 
		{
			if (father[x] == y) father[x] = x;
			else father[y] = y;
		}
		else 
		{
			int fx = getfather(x), fy = getfather(y);
			if (fx == fy) puts("Yes"); else puts("No");
		}
	}
	
	return 0;
}
