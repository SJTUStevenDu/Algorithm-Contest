#include <iostream>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <cmath>
#include <fstream>
#include <algorithm>

using namespace std;

const int MAXN = 100000 + 10;
const int seed = 131;
typedef unsigned long long int64;

int T, n;
int64 po[MAXN];

inline int lowbit(int x) {return x & (-x);}

struct BIT
{
	int64 c[MAXN];
	inline void Clear() {memset(c, 0, sizeof(c));}
	inline void Update(int x, int64 v) {for (; x <= n; x += lowbit(x)) c[x] += v;}
	inline int64 Query(int x) {int64 res = 0; for (; x; x -= lowbit(x)) res += c[x]; return res;}
} C1, C2;

int main()
{
	scanf("%d", &T);
	po[0] = 1;
	for (int i = 1; i <= 10000; ++i) po[i] = po[i - 1] * seed;
	while (T--)
	{
		C1.Clear(); C2.Clear();
		scanf("%d", &n);
		bool ans = false;
		for (int x, len, i = 1; i <= n; ++i)
		{
			scanf("%d", &x);
			if (ans) continue;
			len = min(x - 1, n - x);
			int64 h1 = (C1.Query(x - 1) - C1.Query(x - len - 1)) * po[n - x + 1];
			int64 h2 = (C2.Query(n - x) - C2.Query(n - x - len)) * po[x];
			if (h1 != h2) ans = true;
			C1.Update(x, po[x]);
			C2.Update(n - x + 1, po[n - x + 1]);
		}
		if (ans) puts("Y"); else puts("N");
	}
	
	return 0;
}
