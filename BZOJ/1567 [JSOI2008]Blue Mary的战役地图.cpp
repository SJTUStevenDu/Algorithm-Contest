#include <iostream>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <cmath>
#include <fstream>
#include <algorithm>

using namespace std;

const int MAXN = 50 + 10;
const int seed1 = 10171019;
const int seed2 = 815713;

int a[2][MAXN][MAXN], n;
long long hash[2][MAXN][MAXN][MAXN];

int main()
{
	scanf("%d", &n);
	for (int z = 0; z < 2; ++z) 
		for (int i = 1; i <= n; ++i) 
			for (int j = 1; j <= n; ++j) scanf("%d", &a[z][i][j]);
	for (int z = 0; z < 2; ++z)
		for (int len = n; len; --len)
			for (int x = 1; x <= n - len + 1; ++x)
				for (int y = 1; y <= n - len + 1; ++y)
					for (int i = x; i <= x + len - 1; ++i)
						for (int j = y; j <= y + len - 1; ++j) hash[z][x][y][len] += a[z][i][j] * ((i - x) * seed1 + j - y) * seed2;
	for (int len = n; len; --len)
		for (int x1 = 1; x1 <= n - len + 1; ++x1)	
			for (int y1 = 1; y1 <= n - len + 1; ++y1)
				for (int x2 = 1; x2 <= n - len + 1; ++x2)
					for (int y2 = 1; y2 <= n - len + 1; ++y2)
						if (hash[0][x1][y1][len] == hash[1][x2][y2][len]) 
						{
							printf("%d\n", len);
							return 0;
						}
	
	return 0;
}
