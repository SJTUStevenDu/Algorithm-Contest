#include <iostream>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <cmath>
#include <fstream>
#include <algorithm>

using namespace std;

const int MAXN = 50000 + 10;

int prm[MAXN], Top, u[MAXN], T;
bool vis[MAXN];
long long l, r, k;

void Prepare()
{
	u[1] = 1;
	for (int i = 2; i <= 50000; ++i)
	{
		if (!vis[i]) prm[++Top] = i, u[i] = -1;
		for (int j = 1; j <= Top && prm[j] * i <= 50000; ++j) 
		{
			vis[i * prm[j]] = 1;
			if (i % prm[j] == 0)
			{
				u[i * prm[j]] = 0;
				break;
			}
			u[i * prm[j]] = -u[i];
		}
	}
}

long long calc(long long x)
{
	long long ret = 0;
	for (long long i = 1; i * i <= x; ++i) ret += u[i] * x / i / i;
	return ret;
}

int main()
{
	Prepare();
	scanf("%d", &T);
	while (T--)
	{
		scanf("%lld", &k);
		l = 0; r = 2 * k;
		while (l <= r)
		{
			long long mid = (l + r) / 2;
			if (calc(mid) >= k) r = mid - 1;
			else l = mid + 1;
		}
		printf("%lld\n", l);
	}
	
	return 0;
}
