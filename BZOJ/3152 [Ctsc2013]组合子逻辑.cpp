#include <iostream>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <cmath>
#include <fstream>
#include <algorithm>
#include <queue>

using namespace std;

const int MAXN = 200000 + 10;

priority_queue <int> Q;

int n, a[MAXN], T;

int work()
{
	if (n == 1) return 0;
	if (a[1] == 1) return -1;
	while (!Q.empty()) Q.pop();
	int now = a[1] - 1, ret = 1;
	for (int i = 2; i <= n; ++i)
	{
		if (now > 0) --now;
		else if (Q.empty() || Q.top() == 1) return -1;
		else 
		{
			now = Q.top() - 2;
			++ret;
			Q.pop();
		}
		Q.push(a[i]);
	}
	return ret;
}

int main()
{
	scanf("%d", &T);
	while (T--)
	{
		scanf("%d", &n);
		for (int i = 1; i <= n; ++i) scanf("%d", &a[i]);
		printf("%d\n", work());
	}
	
	return 0;
}
