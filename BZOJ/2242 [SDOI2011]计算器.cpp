#include <iostream>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <cmath>
#include <fstream>
#include <algorithm>
#include <map>

using namespace std;

int x, y, p, T, k;

long long QuickMod(long long a, long long b, int c)
{
	long long res = 1;
	while (b)
	{
		if (b & 1) res = res * a % c;
		b >>= 1;
		a = a * a % c;
	}
	return res;
}

int gcd(int n, int m)
{
	int tmp;
	while (m)
	{
		tmp = n % m;
		n = m;
		m = tmp;
	}
	return n;
}

map <long long, int> HASH;

int main()
{
	scanf("%d%d", &T, &k);
	while (T--)
	{
		scanf("%d%d%d", &x, &y, &p);
		if (k == 1) printf("%lld\n", QuickMod(x, y, p));
		else if (k == 2)
		{
			if (y % gcd(x, p) != 0) puts("Orz, I cannot find x!");
			else 
			{
				long long res = QuickMod(x, p - 2, p);
				res = res * y % p;
				res = (res + p) % p;
				printf("%lld\n", res);
			}
		}
		else 
		{
			y %= p;
			if (y == 1) puts("0");
			else if (x % p == 0) puts("Orz, I cannot find x!");
			else 
			{
				
				int ans = 2000000000;
				HASH.clear();
				int w = (int)sqrt(p) + 1;
				long long now = 1;
				for (int i = 1; i <= w; ++i)
				{
					now = (now * x) % p;
					if (!HASH[now]) HASH[now] = i;
				}
				for (int i = 0; i <= w; ++i)
				{
					now = (y * QuickMod(x, (long long)i * w * (p - 2), p)) % p;
					int s = HASH[now];
					if (s)
					{
						ans = i * w + s;
						break;
					}
					
				}
				if (ans < 2000000000) printf("%d\n", ans);
				else puts("Orz, I cannot find x!");
			}
		}
	}
	
	return 0;
}
