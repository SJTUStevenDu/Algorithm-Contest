#include <iostream>
#include <cstdio>
#include <cstring>

using namespace std;

const int MAXN = 10000000 + 10;
const int MAXM = 1000000 + 10;

int n;
bool vis[MAXN];
long long phi[MAXN], ans;
int prime[MAXM], cnt;

int main()
{
    scanf("%d", &n);
    phi[1] = 1;
    for (int i = 2; i <= n; ++i)
    {
		if (!vis[i]) prime[++cnt] = i, phi[i] = i - 1;
		for (int j = 1; j <= cnt && prime[j] * i <= n; ++j)
		{
			vis[i * prime[j]] = 1;
			if (i % prime[j] == 0)
			{
				phi[i * prime[j]] = phi[i] * prime[j];
				break;
			}
			else phi[i * prime[j]] = phi[i] * (prime[j] - 1);
		}
	}
	for (int i = 2; i <= n; ++i) phi[i] += phi[i - 1];
	for (int i = 1; i <= cnt; ++i) ans += phi[n / prime[i]] * 2 - 1;
	printf("%lld\n", ans);
    
    return 0;
}
