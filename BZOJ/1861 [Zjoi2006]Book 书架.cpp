#include <iostream>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <algorithm>
#include <cmath>

using namespace std;

const int MAXN = 240000 + 10;

int n, m, f1[MAXN], f2[MAXN], c[MAXN], head, tail;
char opr[20];

inline int lowbit(int x) {return x & (-x);}

inline void Add(int x, int v)
{
	for (int i = x; i <= 2 * m + n; i += lowbit(i)) c[i] += v;
}

inline int Query(int x)
{
	int ret = 0;
	for (int i = x; i > 0; i -= lowbit(i)) ret += c[i];
	return ret;
}

int main()
{
	scanf("%d%d", &n, &m);
	for (int i = 1; i <= n; ++i) scanf("%d", &f1[m + i]), f2[f1[m + i]] = m + i;
	for (int i = 1; i <= n; ++i) Add(f2[i], 1);
	head = m + 1; tail = m + n;
	for (int z = 1; z <= m; ++z) 
	{
		scanf("%s", opr);
		int s, t;
		if (opr[0] == 'T')
		{
			scanf("%d", &s);
			Add(f2[s], -1);
			f1[f2[s]] = 0;
			f2[s] = head - 1;
			f1[head - 1] = s;
			head--;
			Add(f2[s], 1);
		}
		else if (opr[0] == 'B')
		{
			scanf("%d", &s);
			Add(f2[s], -1);
			f1[f2[s]] = 0;
			f2[s] = tail + 1;
			f1[tail + 1] = s;
			++tail;
			Add(f2[s], 1);
		}
		else if (opr[0] == 'I')
		{
			scanf("%d%d", &s, &t);
			if (t == 0) continue;
			t = Query(f2[s]) + t;
			int l = 0, r = 2 * n + m;
			while (l <= r)
			{
				int mid = (l + r) >> 1;
				if (Query(mid) < t) l = mid + 1;
				else r = mid - 1;
			}
			l = f1[l];
			swap(f2[s], f2[l]);
			swap(f1[f2[s]], f1[f2[l]]);
		}
		else if (opr[0] == 'A')
		{
			scanf("%d", &s);
			printf("%d\n", Query(f2[s] - 1));
		}
		else if (opr[0] == 'Q')
		{
			scanf("%d", &s);
			int l = 0, r = 2 * n + m;
			while (l <= r)
			{
				int mid = (l + r) >> 1;
				if (Query(mid) < s) l = mid + 1;
				else r = mid - 1;
			}
			printf("%d\n", f1[l]);
		}
	}
	
	return 0;
}
