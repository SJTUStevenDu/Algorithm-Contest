#include <cstdio>
#include <cstdlib>
#include <climits>
#include <algorithm>

using namespace std;

const int MAXN = 100000 + 10;
const int MAXM = 19;
const int INF = 0x7FFFFFFF >> 1;

int n, st[MAXM][MAXN], q, x, y, d[MAXN], a[MAXN], ans, logn, Log[MAXN];

int query(int l, int r)
{
	if (l > r) return -INF;
	int len = Log[r - l + 1];
	return max(st[len][l], st[len][r - (1 << len) + 1]);
}

void build()
{
	logn = Log[n];
	for (int i = 0; i <= n; ++i) st[0][i] = a[i];
	for (int i = 1; i <= logn; ++i)
		for (int j = 1; j <= n - (1 << i) + 1; ++j)
			st[i][j] = max(st[i - 1][j], st[i - 1][j + (1 << i - 1)]);
	
}

inline int getpos(int x) {return std::lower_bound(d + 1, d + n + 1, x) - d;}

int main()
{
	for (int i = 2; i < MAXN; ++i) Log[i] = Log[i >> 1] + 1;
	scanf("%d", &n);
	for (int i = 1; i <= n; ++i)
		scanf("%d%d", d + i, a + i);
	scanf("%d", &q);
	build();
	while (q--)
	{
		scanf("%d%d", &x, &y);
		int l = getpos(x), r = getpos(y), m;
		bool lx = l <= n && d[l] == x, rx = r <= n && d[r] == y;
		if (!rx) --r;
		if (lx)
			if (rx)
			{
				m = query(l + 1, r - 1);
				if (a[l] < a[r]) ans = 0;
				else
					if (m < a[r])
						if (r - l == y - x) ans = 1;
						else ans = -1;
					else ans = 0;
			}
			else
			{
				m = query(l + 1, r);
				if (m < a[l]) ans = -1;
				else ans = 0;
			}
		else if (rx)
			{
				m = query(l, r - 1);
				if (m < a[r]) ans = -1;
				else ans = 0;
			}
			else ans = -1;
		if (ans == 1) printf("true\n");
		else if (!ans) printf("false\n");
		else printf("maybe\n");
	}
	return 0;
}
