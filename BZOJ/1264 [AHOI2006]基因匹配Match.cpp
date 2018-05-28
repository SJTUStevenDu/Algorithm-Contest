#include <iostream>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <cmath>
#include <fstream>
#include <algorithm>

using namespace std;

const int MAXN = 100000 + 10;

int a[MAXN][6], s[MAXN], n, ans, cnt[MAXN];

inline void checkmax(int &x, int y) {if (x < y) x = y;}
inline int lowbit(int x) {return x & (-x);}

inline void Add(int x, int v)
{
	for (; x <= n; x += lowbit(x)) checkmax(s[x], v);
}

inline int Query(int x)
{
	int ret = 0;
	for (; x; x -= lowbit(x)) checkmax(ret, s[x]);
	return ret;
}

int main()
{
	scanf("%d", &n);
	n *= 5;
	int x, tmp;
	for (int i = 1; i <= n; ++i)
	{
		scanf("%d", &x);
		a[x][++cnt[x]] = i;
	}
	for (int i = 1; i <= n; ++i) 
	{
		scanf("%d", &x);
		for (int j = 5; j; --j)
		{
			tmp = Query(a[x][j] - 1) + 1;
			checkmax(ans, tmp);
			Add(a[x][j], tmp);
		}
	}
	printf("%d\n", ans);
	
	return 0;
}
