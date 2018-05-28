#include <iostream>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <cmath>
#include <fstream>
#include <algorithm>

using namespace std;

const int MAXN = 1000000 + 10;

long long a[MAXN], sum1, sum2, rem[MAXN];
int n, cnt, head, tail;
int pre[MAXN], nxt[MAXN];
bool v[MAXN];

void Delete(int p)
{
	v[p] = 0;
	if (p == head) head = nxt[p];
	if (p == tail) tail = pre[p];
	pre[nxt[p]] = pre[p]; nxt[pre[p]] = nxt[p];
}

int main()
{
	scanf("%d", &n);
	for (int i = 1; i <= n; ++i)
	{
		scanf("%lld", &a[i]);
		if (a[i] != 0) v[i] = 1, ++cnt;
		pre[i] = i - 1; nxt[i] = i + 1;
		sum1 += a[i]; 
	}
	head = 1; tail = n;
	for (;;)
	{
		bool got_change = false;
		while (v[head] && v[nxt[head]] && a[head] >= a[nxt[head]])
		{
			sum2 += (a[head] - a[nxt[head]]) * ((cnt & 1) ? 1 : - 1);
			got_change = true; Delete(head); Delete(head);
		}
		while (v[tail] && v[pre[tail]] && a[tail] >= a[pre[tail]])
		{
			sum2 += (a[tail] - a[pre[tail]]) * (cnt & 1 ? 1 : - 1);
			got_change = true; Delete(tail); Delete(tail);
		}
		for (int i = nxt[head]; i < tail; i = nxt[i])
			if (v[i] && v[pre[i]] && v[nxt[i]] && a[i] >= a[pre[i]] && a[i] >= a[nxt[i]])
			{
				got_change = true;
				a[i] = a[pre[i]] + a[nxt[i]] - a[i];
				Delete(pre[i]); Delete(nxt[i]);
			}
		if (!got_change) break;
	}
	cnt = 0;
	for (int i = 1; i <= n; ++i) if (v[i]) rem[++cnt] = a[i];
	sort(rem + 1, rem + 1 + cnt);
	reverse(rem + 1, rem + 1 + cnt);
	for (int i = 1; i <= cnt; ++i) sum2 += rem[i] * (i & 1 ? 1 : -1);
	printf("%lld %lld\n", (sum1 + sum2) / 2, (sum1 - sum2) / 2);
	
	return 0;
}
