#include <iostream>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <cmath>
#include <algorithm>
#include <fstream>

using namespace std;

const int MAXN = 400 + 10;

int T;
int n, s, t;
int cnt[MAXN];

int main()
{
	scanf("%d", &T);
	while (T--)
	{
		scanf("%d", &n);
		memset(cnt, 0, sizeof(cnt));
		for (int i = 1; i <= n; ++i) 
		{
			scanf("%d%d", &s, &t);
			if (s > t) swap(s, t);
			s -= (!(s & 1));
			t += (t & 1);
			for (int j = s; j <= t; ++j) cnt[j]++;
		}
		int ans = 0;
		for (int i = 1; i <= 400; ++i) ans = max(ans, cnt[i]);
		printf("%d\n", ans * 10);
	}
	
	return 0;
}
